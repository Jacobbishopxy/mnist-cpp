#if !defined(__LAYER_HPP)
#define __LAYER_HPP

#include "Neuron.hpp"
#include <vector>

class Layer
{

  int current_layer_size;
  std::vector<Neuron*> neurons;
  std::vector<double> layer_output;

  public:
  Layer(int, int);
  ~Layer();

  std::vector<double> get_layer_outputs();
  int get_size();
};

#endif // __LAYER_HPP
