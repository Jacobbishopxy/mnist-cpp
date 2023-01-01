CC=g++
SRC := $(PWD)/src
CFLAGS := -std=c++2a -g
INCLUDE_DIR := $(PWD)/include/

all: main

main: obj $(SRC)/Network.cc obj/Layer.o obj/Neuron.o
	$(CC) $(CFLAGS) $(SRC)/Network.cc -o main -L$(MNIST_ML_ROOT)/lib/ -I$(INCLUDE_DIR) \
	-I$(MNIST_ML_ROOT)/include -ldata ./obj/*.o

obj:
	if [ ! -d "./obj" ]; then mkdir obj; fi

obj/Layer.o: $(SRC)/Layer.cc
	$(CC) -c $(CFLAGS) $(SRC)/Layer.cc -o obj/Layer.o -I$(INCLUDE_DIR) \
	-I$(MNIST_ML_ROOT)/include

obj/Neuron.o: $(SRC)/Neuron.cc
	$(CC) -c $(CFLAGS) $(SRC)/Neuron.cc -o obj/Neuron.o -I$(INCLUDE_DIR) \
	-I$(MNIST_ML_ROOT)/include

clean:
	rm -r main obj
