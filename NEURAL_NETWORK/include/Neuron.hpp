#if !defined(__NEURON_HPP)
#define __NEURON_HPP

#include <cmath>
#include <vector>

class Neuron
{
  public:
  double output;
  double delta;
  std::vector<double> weights;

  Neuron(int, int);

  void initialize_weights(int previous_layer_size);
};

#endif // __NEURON_HPP
