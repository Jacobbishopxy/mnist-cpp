#if !defined(__INPUT_LAYER_HPP)
#define __INPUT_LAYER_HPP

#include "Data.hpp"
#include "Layer.hpp"

class InputLayer : public Layer
{
  public:
  InputLayer(int prev, int current) : Layer{prev, current} {};
  ~InputLayer();

  void set_layer_outputs(Data* d);
};

#endif // __INPUT_LAYER_HPP
