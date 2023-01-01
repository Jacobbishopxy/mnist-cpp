#if !defined(__LAYER_HPP)
#define __LAYER_HPP

#include "Neuron.hpp"
#include <vector>

class Layer
{
  public:
  int current_layer_size;
  std::vector<Neuron*> neurons;
  std::vector<double> layer_output;

  Layer(int, int);
};

#endif // __LAYER_HPP
