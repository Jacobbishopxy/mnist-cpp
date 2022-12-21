#if !defined(__NEURON_HPP)
#define __NEURON_HPP

#include <cmath>
#include <vector>

class Neuron
{
  std::vector<double> weights;
  double pre_activation;
  double activated_output;
  double output_derivative;
  double error;
  double alpha; // used in activation functions

  public:
  Neuron(int, int);
  ~Neuron();

  void initialize_weights(int previous_layer_size, int current_layer_size);
  void set_error(double);
  void set_weight(double, int);
  double calculate_pre_activation(std::vector<double>);
  double activate();
  double calculate_output_derivate();
  double sigmoid();
  double relu();
  double leaky_relu();
  double inverse_sqrt_relu();
  double get_output();
  double get_output_derivative();
  double get_error();
  std::vector<double> get_weights();
};

#endif // __NEURON_HPP
