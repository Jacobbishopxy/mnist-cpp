#! /bin/bash

if [[ -z $MNIST_ML_ROOT ]]; then
  echo "Please define MNIST_ML_ROOT"
  exit 1
fi

dir=$(echo "$@" | tr a-z A-Z) # makes input all uppercase
modle_name_lower=$(echo "$@" | tr A-Z a-z)

mkdir -p $MNIST_ML_ROOT/$dir/include $MNIST_ML_ROOT/$dir/src
touch $MNIST_ML_ROOT/$dir/Makefile
touch $MNIST_ML_ROOT/$dir/include/"$modle_name_lower.hpp"
touch $MNIST_ML_ROOT/$dir/src/"$modle_name_lower.cc"
