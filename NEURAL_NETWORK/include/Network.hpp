#if !defined(__NETWORK_HPP)
#define __NETWORK_HPP

#include "Common.hpp"
#include "Data.hpp"
#include "Layer.hpp"
#include "Neuron.hpp"

class Network : public CommonData
{
  public:
  std::vector<Layer*> layers;
  double learning_rate;
  double test_performance;

  Network(std::vector<int> spec, int, int, double);
  ~Network();

  /**
   * return last layer output
   */
  std::vector<double> fprop(Data* data);
  /**
   * the weight vector of neuron
   * the input vector of the previous layer, or the input itself
   *
   * dot product of these two
   */
  double activate(std::vector<double>, std::vector<double>);
  /**
   * put it through an activation function
   */
  double transfer(double);
  /**
   * take the derivative of the transfer function
   *
   * used for back propagation
   */
  double transfer_derivative(double);

  void bprop(Data* data);
  void update_weights(Data* data);
  /**
   * return the index of the maximum value in the output array
   */
  int predict(Data* data);
  /**
   * num iterations
   */
  void train(int);
  double test();
  void validate();
};

#endif // __NETWORK_HPP
