#ifndef QUADRUPED_H
#define QUADRUPED_H

#include <vector>

#include <ode/ode.h>
#include <drawstuff/drawstuff.h>

using namespace std;

typedef struct {
  dJointID joint;
  double tx;
  double ty;
  double tz;
} MyJoint;

typedef struct {
	dBodyID body; 
	dGeomID geom;
	double lx;
	double ly;
	double lz;
} MyBody;

class Quadruped {

public:
	Quadruped();
	Quadruped(dWorldID, dSpaceID, int, double*, vector<double>);
	void update();
	void draw();
	const double getX();
	const double getY();
	const double getZ();
	int getState();


private:
	// attributes
	dWorldID world;
	dSpaceID space;
	int density;
	double* offset;

	vector<MyJoint> joints;
	vector<MyBody> bodies;
	vector<double> genome;

	int state;

	// private methods
	MyBody addBody(double, double, double, const double*);
	void addHingeJoint(dBodyID, dBodyID, const double*, const double*);
};

#endif