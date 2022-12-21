#if !defined(__NETWORK_HPP)
#define __NETWORK_HPP

#include "Common.hpp"
#include "Data.hpp"
#include "HiddenLayer.hpp"
#include "InputLayer.hpp"
#include "Layer.hpp"
#include "Neuron.hpp"
#include "OutputLayer.hpp"

class Network : public CommonData
{
  private:
  InputLayer* input_layer;
  OutputLayer* output_layer;
  std::vector<HiddenLayer*> hidden_layer;
  double eta; // learning rate

  public:
  Network(std::vector<int> hidden_layer_spec, int, int);
  ~Network();

  void fprop(Data* data);
  void bprop(Data* data);
  void update_weights();
  void train();
  void test();
  void validate();
};

#endif // __NETWORK_HPP
