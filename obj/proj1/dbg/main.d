../obj/proj1/dbg/main.o: main.cpp error.h string.h rand.h matrix.h supervised.h baseline.h \
 vec.h layer.h layerlinear.h neuralnet.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -g -D_DEBUG -c main.cpp -o ../obj/proj1/dbg/main.o
