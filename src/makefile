CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lode -ldrawstuff -DdDOUBLE -framework GLUT -framework OpenGL


simulation : ga.o quadruped.o
	${CC} ${CFLAGS} quadruped.o ga.o ${LDFLAGS} -o simulation

ga.o : ga.cpp quadruped.h
	${CC} ${CFLAGS} -c ga.cpp 

quadruped.o : quadruped.cpp quadruped.h
	${CC} ${CFLAGS} -c quadruped.cpp 

clean :
	rm simulation
	rm ga.o
	rm quadruped.o
