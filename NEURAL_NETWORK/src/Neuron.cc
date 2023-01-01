#include "Neuron.hpp"
#include <random>

double generate_random_number(double min, double max)
{
  double random = (double)rand() / RAND_MAX;
  return min + random * (max - min);
}

Neuron::Neuron(int previous_layer_size, int current_layer_size)
{
  initialize_weights(previous_layer_size);
}

void Neuron::initialize_weights(int previous_layer_size)
{
  std::default_random_engine generator;
  std::normal_distribution<double> distribution{0.0, 1.0};
  for (int i = 0; i < previous_layer_size + 1; i++)
  {
    weights.push_back(generate_random_number(-1.0, 1.0));
  }
}
