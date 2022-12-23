CC=g++
SRC := $(MNIST_ML_ROOT)/KMEANS/src
CFLAGS := -std=c++2a -DEUCLID
INCLUDE_DIR := $(PWD)/include/

all : main

main : $(SRC)/KMeans.cc
	$(CC) $(CFLAGS) $(SRC)/KMeans.cc -o main \
	-L$(MNIST_ML_ROOT)/lib/ -I$(INCLUDE_DIR) -I$(MNIST_ML_ROOT)/include -ldata

clean :
	rm main
