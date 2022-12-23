CC=g++
SRC := $(MNIST_ML_ROOT)/KNN/src
CFLAGS := -std=c++2a -DEUCLID
# INCLUDE_DIR := $(MNIST_ML_ROOT)/KNN/include/*
INCLUDE_DIR := $(PWD)/include/

all : main

main : $(SRC)/KNN.cc
	$(CC) $(CFLAGS) $(SRC)/KNN.cc -o main \
	-L$(MNIST_ML_ROOT)/lib/ -I$(INCLUDE_DIR) -I$(MNIST_ML_ROOT)/include -ldata

clean :
	rm main
