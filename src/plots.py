import numpy as np
import matplotlib.pyplot as plt
from matplotlib.pylab import *

from scipy.stats.stats import pearsonr

# ---------
# LOAD DATA
# ---------
print "Loading data from files into arrays..."

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-0_max-fitness.txt", "r")
FD_trial_0_max_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-0_max-distance.txt", "r")
FD_trial_0_max_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-0_max-stability.txt", "r")
FD_trial_0_max_stability = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-0_mean-fitness.txt", "r")
FD_trial_0_mean_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-0_mean-distance.txt", "r")
FD_trial_0_mean_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-0_mean-stability.txt", "r")
FD_trial_0_mean_stability = map(lambda x: float(x), text_file.read().split(', '))




text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-1_max-fitness.txt", "r")
FD_trial_1_max_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-1_max-distance.txt", "r")
FD_trial_1_max_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-1_max-stability.txt", "r")
FD_trial_1_max_stability = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-1_mean-fitness.txt", "r")
FD_trial_1_mean_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-1_mean-distance.txt", "r")
FD_trial_1_mean_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-1_mean-stability.txt", "r")
FD_trial_1_mean_stability = map(lambda x: float(x), text_file.read().split(', '))



text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-2_max-fitness.txt", "r")
FD_trial_2_max_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-2_max-distance.txt", "r")
FD_trial_2_max_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-2_max-stability.txt", "r")
FD_trial_2_max_stability = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-2_mean-fitness.txt", "r")
FD_trial_2_mean_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-2_mean-distance.txt", "r")
FD_trial_2_mean_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-2_mean-stability.txt", "r")
FD_trial_2_mean_stability = map(lambda x: float(x), text_file.read().split(', '))



text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-3_max-fitness.txt", "r")
FD_trial_3_max_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-3_max-distance.txt", "r")
FD_trial_3_max_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-3_max-stability.txt", "r")
FD_trial_3_max_stability = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-3_mean-fitness.txt", "r")
FD_trial_3_mean_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-3_mean-distance.txt", "r")
FD_trial_3_mean_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-3_mean-stability.txt", "r")
FD_trial_3_mean_stability = map(lambda x: float(x), text_file.read().split(', '))



text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-4_max-fitness.txt", "r")
FD_trial_4_max_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-4_max-distance.txt", "r")
FD_trial_4_max_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-4_max-stability.txt", "r")
FD_trial_4_max_stability = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-4_mean-fitness.txt", "r")
FD_trial_4_mean_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-4_mean-distance.txt", "r")
FD_trial_4_mean_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FD_trial-4_mean-stability.txt", "r")
FD_trial_4_mean_stability = map(lambda x: float(x), text_file.read().split(', '))












text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-0_max-fitness.txt", "r")
FG_trial_0_max_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-0_max-distance.txt", "r")
FG_trial_0_max_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-0_max-stability.txt", "r")
FG_trial_0_max_stability = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-0_mean-fitness.txt", "r")
FG_trial_0_mean_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-0_mean-distance.txt", "r")
FG_trial_0_mean_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-0_mean-stability.txt", "r")
FG_trial_0_mean_stability = map(lambda x: float(x), text_file.read().split(', '))




text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-1_max-fitness.txt", "r")
FG_trial_1_max_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-1_max-distance.txt", "r")
FG_trial_1_max_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-1_max-stability.txt", "r")
FG_trial_1_max_stability = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-1_mean-fitness.txt", "r")
FG_trial_1_mean_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-1_mean-distance.txt", "r")
FG_trial_1_mean_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-1_mean-stability.txt", "r")
FG_trial_1_mean_stability = map(lambda x: float(x), text_file.read().split(', '))



text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-2_max-fitness.txt", "r")
FG_trial_2_max_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-2_max-distance.txt", "r")
FG_trial_2_max_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-2_max-stability.txt", "r")
FG_trial_2_max_stability = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-2_mean-fitness.txt", "r")
FG_trial_2_mean_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-2_mean-distance.txt", "r")
FG_trial_2_mean_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-2_mean-stability.txt", "r")
FG_trial_2_mean_stability = map(lambda x: float(x), text_file.read().split(', '))



text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-3_max-fitness.txt", "r")
FG_trial_3_max_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-3_max-distance.txt", "r")
FG_trial_3_max_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-3_max-stability.txt", "r")
FG_trial_3_max_stability = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-3_mean-fitness.txt", "r")
FG_trial_3_mean_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-3_mean-distance.txt", "r")
FG_trial_3_mean_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-3_mean-stability.txt", "r")
FG_trial_3_mean_stability = map(lambda x: float(x), text_file.read().split(', '))



text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-4_max-fitness.txt", "r")
FG_trial_4_max_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-4_max-distance.txt", "r")
FG_trial_4_max_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-4_max-stability.txt", "r")
FG_trial_4_max_stability = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-4_mean-fitness.txt", "r")
FG_trial_4_mean_fitness = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-4_mean-distance.txt", "r")
FG_trial_4_mean_distance = map(lambda x: float(x), text_file.read().split(', '))

text_file = open("/Users/stephanielaflamme/Dropbox/COMP 417/Project/results/FG_trial-4_mean-stability.txt", "r")
FG_trial_4_mean_stability = map(lambda x: float(x), text_file.read().split(', '))




# # ------------
# # PREPARE DATA
# # ------------

print "Getting the max fitness data from each..."

FD_trial_0_argmax = np.argmax(FD_trial_0_max_fitness)
FD_trial_1_argmax = np.argmax(FD_trial_1_max_fitness)
FD_trial_2_argmax = np.argmax(FD_trial_2_max_fitness)
FD_trial_3_argmax = np.argmax(FD_trial_3_max_fitness)
FD_trial_4_argmax = np.argmax(FD_trial_4_max_fitness)

FD_max_fitnesses = []
FD_max_fitnesses.append(FD_trial_0_max_fitness[FD_trial_0_argmax])
FD_max_fitnesses.append(FD_trial_1_max_fitness[FD_trial_1_argmax])
FD_max_fitnesses.append(FD_trial_2_max_fitness[FD_trial_2_argmax])
FD_max_fitnesses.append(FD_trial_3_max_fitness[FD_trial_3_argmax])
FD_max_fitnesses.append(FD_trial_4_max_fitness[FD_trial_4_argmax])

FD_max_stabilities = []
FD_max_stabilities.append(FD_trial_0_max_stability[FD_trial_0_argmax])
FD_max_stabilities.append(FD_trial_1_max_stability[FD_trial_1_argmax])
FD_max_stabilities.append(FD_trial_2_max_stability[FD_trial_2_argmax])
FD_max_stabilities.append(FD_trial_3_max_stability[FD_trial_3_argmax])
FD_max_stabilities.append(FD_trial_4_max_stability[FD_trial_4_argmax])

FD_max_distances = []
FD_max_distances.append(FD_trial_0_max_distance[FD_trial_0_argmax])
FD_max_distances.append(FD_trial_1_max_distance[FD_trial_1_argmax])
FD_max_distances.append(FD_trial_2_max_distance[FD_trial_2_argmax])
FD_max_distances.append(FD_trial_3_max_distance[FD_trial_3_argmax])
FD_max_distances.append(FD_trial_4_max_distance[FD_trial_4_argmax])





FG_trial_0_argmax = np.argmax(FG_trial_0_max_fitness)
FG_trial_1_argmax = np.argmax(FG_trial_1_max_fitness)
FG_trial_2_argmax = np.argmax(FG_trial_2_max_fitness)
FG_trial_3_argmax = np.argmax(FG_trial_3_max_fitness)
FG_trial_4_argmax = np.argmax(FG_trial_4_max_fitness)

FG_max_fitnesses = []
FG_max_fitnesses.append(FG_trial_0_max_fitness[FG_trial_0_argmax])
FG_max_fitnesses.append(FG_trial_1_max_fitness[FG_trial_1_argmax])
FG_max_fitnesses.append(FG_trial_2_max_fitness[FG_trial_2_argmax])
FG_max_fitnesses.append(FG_trial_3_max_fitness[FG_trial_3_argmax])
FG_max_fitnesses.append(FG_trial_4_max_fitness[FG_trial_4_argmax])

FG_max_stabilities = []
FG_max_stabilities.append(FG_trial_0_max_stability[FG_trial_0_argmax])
FG_max_stabilities.append(FG_trial_1_max_stability[FG_trial_1_argmax])
FG_max_stabilities.append(FG_trial_2_max_stability[FG_trial_2_argmax])
FG_max_stabilities.append(FG_trial_3_max_stability[FG_trial_3_argmax])
FG_max_stabilities.append(FG_trial_4_max_stability[FG_trial_4_argmax])

FG_max_distances = []
FG_max_distances.append(FG_trial_0_max_distance[FG_trial_0_argmax])
FG_max_distances.append(FG_trial_1_max_distance[FG_trial_1_argmax])
FG_max_distances.append(FG_trial_2_max_distance[FG_trial_2_argmax])
FG_max_distances.append(FG_trial_3_max_distance[FG_trial_3_argmax])
FG_max_distances.append(FG_trial_4_max_distance[FG_trial_4_argmax])


# ----------------
# Print statistics
# ----------------



print "For FD fitness: "
print "Fitness mean = " + str(np.mean(FD_max_fitnesses))
print "Fitness std = " +  str(np.std(FD_max_fitnesses))

print "For FD distance: "
print "Distance mean = " + str(np.mean(FD_max_distances))
print "Distance std = " +  str(np.std(FD_max_distances))

print "For FD stability: "
print "Stability mean = " + str(np.mean(FD_max_stabilities))
print "Stability std = " + str(np.std(FD_max_stabilities))


print "For FG fitness: "
print "Fitness mean = " + str(np.mean(FG_max_fitnesses))
print "Fitness std = " +  str(np.std(FG_max_fitnesses))

print "For FG distance: "
print "Distance mean = " + str(np.mean(FG_max_distances))
print "Distance std = " +  str(np.std(FG_max_distances))

print "For FG stability: "
print "Stability mean = " + str(np.mean(FG_max_stabilities))
print "Stability std = " + str(np.std(FG_max_stabilities))


# ------------------
# Plotting functions
# ------------------

def make_boxplots():
	'''
	Make the boxplot infographics
	'''
	data1 = [FD_max_distances, FG_max_distances]
	data2 = [FD_max_stabilities, FG_max_stabilities]
	labels = ['FD', 'FG']

	fig = plt.figure()
	ax = fig.add_subplot(1,1,1)
	ax.boxplot(data1, labels=labels, showmeans=True)
	ax.set_ylabel('Distance')
	plt.savefig('/Users/stephanielaflamme/Dropbox/COMP 417/Project/report/boxplot_distances.pdf')
	plt.savefig('/Users/stephanielaflamme/Dropbox/COMP 417/Project/report/boxplot_distances.png')
	
	fig, axes = plt.subplots(nrows=1, ncols=2)
	axes[0].boxplot([FD_max_stabilities], labels=['FD'], showmeans=True)
	axes[0].set_ylabel('Instability')
	axes[1].boxplot([FG_max_stabilities], labels=['FG'], showmeans=True)
	plt.savefig('/Users/stephanielaflamme/Dropbox/COMP 417/Project/report/boxplot_stabilities.pdf')
	plt.savefig('/Users/stephanielaflamme/Dropbox/COMP 417/Project/report/boxplot_stabilities.png')



def scatter_dist_stab():
	'''
	Make a scatter plot showing distance vs stability
	'''
	fig = plt.figure()
	ax = fig.add_subplot(1,1,1)

	distances = FD_max_distances + FG_max_distances
	stabilities = FD_max_stabilities + FG_max_stabilities

	s = [160 for _ in distances]

	ax.scatter(distances, stabilities, alpha=0.5, s=s)

	ax.set_ylabel('Instability')
	ax.set_xlabel('Distance')
	plt.savefig('/Users/stephanielaflamme/Dropbox/COMP 417/Project/report/distancevsstability.pdf')
	plt.savefig('/Users/stephanielaflamme/Dropbox/COMP 417/Project/report/distancevsstability.png')

	print pearsonr(distances, stabilities)



def show_learning():
	'''
	Make a graph of fitness over time.
	Shows both maximum and mean fitness at each epoch.
	'''
	fig = plt.figure()
	ax = fig.add_subplot(1,1,1)

	best = FD_trial_2_max_fitness
	mean = FD_trial_2_mean_fitness

	generations = range(len(best))
	
	c1, = ax.plot(generations, best, marker='x', color='green', label='Best')
	c2, = ax.plot(generations, mean, marker='x', color='purple', label='Mean')

	handles, labels = ax.get_legend_handles_labels()
	ax.legend(handles, labels, loc=0)

	ax.yaxis.grid(b=True, which='both', color='black', linestyle='--')
	# labels
	ax.set_xlabel('Generation')
	ax.set_ylabel('Fitness')

	plt.savefig('/Users/stephanielaflamme/Dropbox/COMP 417/Project/report/Dlearningvstime.pdf')
	plt.savefig('/Users/stephanielaflamme/Dropbox/COMP 417/Project/report/Dlearningvstime.png')


	fig = plt.figure()
	ax = fig.add_subplot(1,1,1)

	best = FG_trial_1_max_fitness
	mean = FG_trial_1_mean_fitness

	generations = range(len(best))
	
	c1, = ax.plot(generations, best, marker='x', color='green', label='Best')
	c2, = ax.plot(generations, mean, marker='x', color='purple', label='Mean')

	handles, labels = ax.get_legend_handles_labels()
	ax.legend(handles, labels, loc=0)

	ax.yaxis.grid(b=True, which='both', color='black', linestyle='--')
	# labels
	ax.set_xlabel('Generation')
	ax.set_ylabel('Fitness')

	plt.savefig('/Users/stephanielaflamme/Dropbox/COMP 417/Project/report/Glearningvstime.pdf')
	plt.savefig('/Users/stephanielaflamme/Dropbox/COMP 417/Project/report/Glearningvstime.png')


def all_plots():
	make_boxplots()
	show_learning()
	scatter_dist_stab()


all_plots()
