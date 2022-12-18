CC=g++
INCLUDE_DIR := $(MNIST_ML_ROOT)/include
SRC := $(MNIST_ML_ROOT)/src
CFLAGS := -std=c++2a -g
LIB_DATA := libdata.so

all : $(LIB_DATA)

$(LIB_DATA) : libdir objdir obj/DataHandler.o obj/Data.o
	$(CC) $(CFLAGS) -o $(MNIST_ML_ROOT)/lib/$(LIB_DATA) obj/*.o
	rm -r $(MNIST_ML_ROOT)/obj

libdir :
	mkdir -p $(MNIST_ML_ROOT)/lib

objdir :
	mkdir -p $(MNIST_ML_ROOT)/obj

obj/DataHandler.o : $(SRC)/DataHandler.cc
	$(CC) -fPIC $(CFLAGS) -o obj/DataHandler.o -I$(INCLUDE_DIR) -c $(SRC)/DataHandler.cc

obj/Data.o : $(SRC)/Data.cc
	$(CC) -fPIC $(CFLAGS) -o obj/Data.o -I$(INCLUDE_DIR) -c $(SRC)/Data.cc

clean:
	rm -r $(MNIST_ML_ROOT)/lib
	rm -r $(MNIST_ML_ROOT)/obj
