/**
*
* Note:
* Code for the genetic algorithm is based on an example from
* http://www.generation5.org/content/2003/gahelloworld.asp
*
**/

#include <iostream>					// for cout etc.
#include <fstream>					// for printing results
#include <sstream>					
#include <vector>					// for vector class
#include <string>					// for string class
#include <algorithm>				// for sort algorithm
#include <time.h>					// for random seed
#include <math.h>					// for abs()
#include <random>					// for genome creation

#include <ode/ode.h>
#include <drawstuff/drawstuff.h>

#include "Quadruped.h"

#define GA_POPSIZE		50		// ga population size
#define GA_MAXITER		100		// maximum iterations
#define GA_ELITRATE		0.10f		// elitism rate
#define GA_MUTATIONRATE	0.05f		// mutation rate
#define GA_MUTATION		RAND_MAX * GA_MUTATIONRATE

static const double pi = 3.1415926535897;
#define DEG_TO_RAD 		pi/360.0

using namespace std;				// polluting global namespace, but hey...

random_device rd;
mt19937 e2(rd());


/*********************
*
* SETUP THE ODE STUFF
*
**********************/

dWorldID    world;       // A dynamic world
dSpaceID    space;
dGeomID    ground;
dJointGroupID contact_group;
dsFunctions fn;

vector<Quadruped*> robots;

static void nearCallback(void *data, dGeomID o1, dGeomID o2) {
  dBodyID b1 = dGeomGetBody(o1), b2 = dGeomGetBody(o2);
  if (b1 && b2 && dAreConnectedExcluding(b1,b2,dJointTypeContact)) return;
  // if ((o1 != ground) && (o2 != ground)) return;

  static const int N = 20;
  dContact contact[N];
  int n = dCollide(o1,o2,N,&contact[0].geom,sizeof(dContact));
  if (n > 0) {
    for (int i=0; i<n; i++) {
      contact[i].surface.mode = dContactSoftERP | dContactSoftCFM;
      contact[i].surface.mu   = 0.2; //dInfinity; //2.0;
      contact[i].surface.soft_erp = 0.9;
      contact[i].surface.soft_cfm = 1e-5;
      dJointID c = dJointCreateContact(world,contact_group,&contact[i]);
      dJointAttach(c,b1,b2);
    }
  }
}

void start()
{

  static float xyz[3] = {1.9405,-1.3615,0.7300}; //{   1.5, 1.8, 1.0};
  static float hpr[3] = {119.5000,-5.5000,0.0000}; //{-129.0, -15.0, 0.0};
  dsSetViewpoint(xyz, hpr);
}

void simLoop(int pause) {
	dSpaceCollide(space,0,&nearCallback);

	dWorldStep(world, 0.02);

	// dsSetColor(1.0, 1.0, 1.0); // white robot

	for (Quadruped* robot : robots)
	{
		robot->update();
	  	// robot->draw();
	}
	dJointGroupEmpty(contact_group);
}






vector<double>* noDrawSimLoop(int pause) {
	dSpaceCollide(space,0,&nearCallback);

	dWorldStep(world, 0.02);

	// dsSetColor(1.0, 1.0, 1.0); // white robot

	vector<double>* xyz = new vector<double>;

	for (Quadruped* robot : robots)
	{
		robot->update();
		xyz->push_back(robot->getX());
		xyz->push_back(robot->getY());
		xyz->push_back(robot->getZ());
	  	// robot->draw();
	}
	dJointGroupEmpty(contact_group);

	return xyz;
}



void  setDrawStuff()
{
  fn.version = DS_VERSION;
  fn.start   = &start;
  fn.step    = &simLoop;
  fn.command = NULL;
  fn.stop    = NULL;
  fn.path_to_textures = "../textures";
}

/************************
*
* GENETIC ALGORITHM STUFF
*
*************************/

static const double MIN_MAX_GENE[4][2] = {
	{0.0, 1.0},
	{-60*DEG_TO_RAD, 15*DEG_TO_RAD},
	{-1*DEG_TO_RAD, 120*DEG_TO_RAD},
	{-90*DEG_TO_RAD, 30*DEG_TO_RAD}
};

struct ga_struct 
{
	vector<double> genome;					// the genotype
	double fitness;							// its fitness
	double distance;						// how far it went
	double stability;						// how stable it is
};

typedef vector<ga_struct> ga_vector;		// for brevity

/**
*
* Start a population of 50 genotypes.
*
**/
void init_population(ga_vector &population,
					 ga_vector &buffer ) 
{

	for (int i=0; i<GA_POPSIZE; i++) {
		ga_struct citizen;
		
		citizen.fitness = 0;
		citizen.genome.resize(28);

		// ensure your genes are within the joint restrictions
		for (int j=0; j<28; j++)
			if (j < 4) 
			{
				// relative velocity
				uniform_real_distribution<double> dist(MIN_MAX_GENE[0][0], MIN_MAX_GENE[0][1]);
				citizen.genome[j] = dist(e2);
			}
			else if (j < 12)
			{
				// hip joints
				uniform_real_distribution<double> dist(MIN_MAX_GENE[1][0], MIN_MAX_GENE[1][1]);
				citizen.genome[j] = dist(e2);
			}
			else if (j < 20)
			{
				// knee joints
				uniform_real_distribution<double> dist(MIN_MAX_GENE[2][0], MIN_MAX_GENE[2][1]);
				citizen.genome[j] = dist(e2);
			}
			else
			{
				// ankle joints
				uniform_real_distribution<double> dist(MIN_MAX_GENE[3][0], MIN_MAX_GENE[3][1]);
				citizen.genome[j] = dist(e2);
			}
		population.push_back(citizen);
	}

	buffer.resize(GA_POPSIZE);
}

/**
*
* Run actual simulation for 60 seconds to calculate fitness of population members.
*
**/
void calc_fitness(ga_vector &population)
{
	setDrawStuff();
	dInitODE();
	world = dWorldCreate();
	// dWorldSetERP(world, 0.4);
	// dWorldSetCFM(world, 1e-5);
	dWorldSetGravity(world, 0, 0, -9.8);
	space = dHashSpaceCreate(0);
	contact_group = dJointGroupCreate(0);
	ground = dCreatePlane(space, 0, 0, 1, 0);


	robots.clear();
	for (int i = 0; i < GA_POPSIZE; i ++)
	{

		double offset[3] = {0.0, 0.0 + 10*i, 0.0};
		robots.push_back(new Quadruped(world, space, 1, offset, population[i].genome));

	}

	time_t start, end;
	time(&start);
	time(&end);

	int iter = 0;
	// keep track of each robot's measures
	vector<double> total_xyz(GA_POPSIZE*3, 0.0);
	vector<double> single_xyz;

	while(difftime(time(&end), start) < 60) 
	{
		iter += 1;
		vector<double>* step_xyz = noDrawSimLoop(0); // run through the loop
		for (int i = 0; i < total_xyz.size(); i++)
		{
			total_xyz[i] += (*step_xyz)[i]; // increment each stability value
			single_xyz.push_back((*step_xyz)[i]); // add it to our memory
		}
	}

	vector<double> mean_x;
	vector<double> mean_y;
	vector<double> mean_z;

	for (int i = 0; i < total_xyz.size(); i+=3)
	{
		mean_x.push_back(total_xyz[i] / iter);
		mean_y.push_back(total_xyz[i+1] / iter);
		mean_z.push_back(total_xyz[i+2] / iter);
	}

	// calculate the stability of each robot
	vector<double> robot_stabilities;
	// for each robot
	for (int i = 0; i < GA_POPSIZE; i++)
	{
		double var_x = 0;
		double var_y = 0;
		double var_z = 0;
		// calculate the sum of squared differences throughout each iteration
		for (int j = 0; j < single_xyz.size(); j+=3*GA_POPSIZE)
		{
			var_x += pow(mean_x[i] - single_xyz[j+i], 2.0);
			var_y += pow(mean_y[i] - single_xyz[j+i+1], 2.0);
			var_z += pow(mean_z[i] - single_xyz[j+i+2], 2.0);
		}
		// stability of this robot
		robot_stabilities.push_back( sqrt((var_x + var_y + var_z)/iter) );
	}


	// dsSimulationLoop(NULL,NULL,640,480,&fn);

	// make a note of the distance, stability, and fitness of the robot
	// CHOOSE BETWEEN FD AND FG FITNESS FUNCTIONS
	for (int i = 0; i < robots.size(); i++)
	{
		population[i].distance = robots[i]->getX();
		population[i].stability = robot_stabilities[i];
		population[i].fitness = population[i].distance/(1 + population[i].stability);
		// population[i].fitness = population[i].distance;
	}

	dWorldDestroy(world);
	dCloseODE();
}

bool fitness_sort(ga_struct x, ga_struct y) 
{ return (x.fitness > y.fitness); }

inline void sort_by_fitness(ga_vector &population)
{ sort(population.begin(), population.end(), fitness_sort); }

/**
*
* Allow the fittest individuals to survive.
*
**/
void elitism(ga_vector &population, 
				ga_vector &buffer, int esize )
{
	for (int i=0; i<esize; i++) {
		buffer[i].genome = population[i].genome;
		buffer[i].fitness = population[i].fitness;
	}
}

/**
*
* Change a random gene's value.
*
**/
void mutate(ga_struct &member)
{
	// pick a random gene to mutate
	int ipos = rand() % 28;				
	
	// find new value for it, making sure you stay within allowable limits
	if (ipos < 4) 
	{
		// relative velocity
		uniform_real_distribution<double> dist(MIN_MAX_GENE[0][0], MIN_MAX_GENE[0][1]);
		member.genome[ipos] = dist(e2);
	}
	else if (ipos < 12)
	{
		// hip joints, front and back
		uniform_real_distribution<double> dist(MIN_MAX_GENE[1][0], MIN_MAX_GENE[1][1]);
		member.genome[ipos] = dist(e2);
	}
	else if (ipos < 20)
	{
		// knee joints
		uniform_real_distribution<double> dist(MIN_MAX_GENE[2][0], MIN_MAX_GENE[2][1]);
		member.genome[ipos] = dist(e2);
	}
	else
	{
		// ankle joints
		uniform_real_distribution<double> dist(MIN_MAX_GENE[3][0], MIN_MAX_GENE[3][1]);
		member.genome[ipos] = dist(e2);
	}
}

/**
*
* Sexy times.
*
**/
void mate(ga_vector &population, ga_vector &buffer)
{
	int esize = GA_POPSIZE * GA_ELITRATE;
	int tsize = 28, spos, i1, i2;


	// let the best survive
	elitism(population, buffer, esize);


	// mate the rest
	for (int i=esize; i<GA_POPSIZE; i++) {

		// select two individuals randomly
		i1 = rand() % (GA_POPSIZE / 2);
		i2 = rand() % (GA_POPSIZE / 2);

		// select crossover point
		spos = rand() % tsize;

		// give the new genome the correct bits of each parent's genome
		buffer[i].genome.erase(buffer[i].genome.begin(), buffer[i].genome.end());
		for (int j = 0; j < spos; j++)
		{
			buffer[i].genome.push_back(population[i1].genome[j]);
		}
		for (int j = spos; j < 28; j++)
		{
			buffer[i].genome.push_back(population[i2].genome[j]);
		}
		// mutate one of the child's genes with small probability
		if (rand() < GA_MUTATION) mutate(buffer[i]);
	}
}

/**
*
* Keep a record of your best per generation.
*
**/
inline void print_stats(ga_vector &gav, int gen, int trial)
{ 
	// print stuff to terminal so that we can see
	cout << "GENERATION " << gen << endl;

	cout << "Best fitness: " << gav[0].fitness << endl;

	cout << "Best distance: " << gav[0].distance << endl;

	cout << "Best stability: " << gav[0].stability << endl;

	double mean_fitness = 0.0;
	double mean_distance = 0.0;
	double mean_stability = 0.0;
	for (int i = 0; i < GA_POPSIZE; i++)
	{
		mean_fitness += gav[i].fitness;
		mean_distance += gav[i].distance;
		mean_stability += gav[i].stability;
	}
	mean_fitness = mean_fitness/GA_POPSIZE;
	mean_distance = mean_distance/GA_POPSIZE;
	mean_stability = mean_stability/GA_POPSIZE;


	cout << "Mean fitness: " << mean_fitness << endl;

	cout << "Mean distance: " << mean_distance << endl;

	cout << "Mean stability: " << mean_stability << endl;

	cout << "Best genome: {";

	for (int i = 0; i < 28; i ++)
	{
		cout << gav[0].genome[i] << ", " ;
	}
	cout << "}" << endl;

	// now save to appropriate files
	stringstream sstm;
	sstm << trial;
	string str_trial = sstm.str();

	// the maxfitness
	ofstream myfile ("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-" + str_trial + "_max-fitness.txt", ios::app);
	if (myfile.is_open())
	{
		if (gen < 99) {myfile << gav[0].fitness << ", ";}
		else {myfile << gav[0].fitness; }
		myfile.close();
	}
	else cout << "Unable to open file";

	// the max distance 
	myfile.open ("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-" + str_trial + "_max-distance.txt", ios::app);
	if (myfile.is_open())
	{
		if (gen < 99) {myfile << gav[0].distance << ", ";}
		else {myfile << gav[0].distance; }
		myfile.close();
	}
	else cout << "Unable to open file";

	// the max stability
	myfile.open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-" + str_trial + "_max-stability.txt", ios::app);
	if (myfile.is_open())
	{
		if (gen < 99) {myfile << gav[0].stability << ", ";}
		else {myfile << gav[0].stability; }
		myfile.close();
	}
	else cout << "Unable to open file";

	// the mean fitness
	myfile.open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-" + str_trial + "_mean-fitness.txt", ios::app);
	if (myfile.is_open())
	{
		if (gen < 99) {myfile << mean_fitness << ", ";}
		else {myfile << mean_fitness; }
		myfile.close();
	}
	else cout << "Unable to open file";

	// the mean distance
	myfile.open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-" + str_trial + "_mean-distance.txt", ios::app);
	if (myfile.is_open())
	{
		if (gen < 99) { myfile << mean_distance << ", "; }
		else { myfile << mean_distance; }
		myfile.close();
	}
	else cout << "Unable to open file";

	// the mean stability
	myfile.open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-" + str_trial + "_mean-stability.txt", ios::app);
	if (myfile.is_open())
	{
		if (gen < 99) {myfile << mean_stability << ", ";}
		else {myfile << mean_stability; }
		myfile.close();
	}
	else cout << "Unable to open file";

	// and finally, the best genome at this time
	// the mean distance
	myfile.open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-" + str_trial + "_best-genomes.txt", ios::app);
	if (myfile.is_open())
	{
		myfile << "[";
		for (int i = 0; i < 28; i ++)
		{
			if (i < 27) { myfile << gav[0].genome[i] << ", " ; }
			else { myfile << gav[0].genome[i]; } 
			
		}
		myfile << "], ";
		myfile.close();
	}
	else cout << "Unable to open file";
}

inline void swap(ga_vector *&population,
				 ga_vector *&buffer)
{ ga_vector *temp = population; population = buffer; buffer = temp; }


/**
*
* Run the actual GA 
* 
**/
int main()
{

	// do 5 trials
	for (int j = 0; j < 5; j++)
	{
		// new seed for each one
		srand(unsigned(time(NULL)));

		ga_vector pop_alpha, pop_beta;
		ga_vector *population, *buffer;

		init_population(pop_alpha, pop_beta);
		population = &pop_alpha;
		buffer = &pop_beta;

		// for each iteration of this trial
		for (int i=0; i<GA_MAXITER; i++) {

			calc_fitness(*population);		// calculate fitness
			sort_by_fitness(*population);	// sort them
			print_stats(*population, i, j);		// print the best one


			if ((*population)[0].fitness == 0) break;

			mate(*population, *buffer);		// mate the population together
			swap(population, buffer);		// swap buffers
		}
	}

	return 0;
}