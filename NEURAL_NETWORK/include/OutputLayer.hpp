#if !defined(__OUTPUT_LAYER_HPP)
#define __OUTPUT_LAYER_HPP

#include "Data.hpp"
#include "Layer.hpp"

class OutputLayer : public Layer
{
  public:
  OutputLayer(int prev, int curr) : Layer{prev, curr} {};
  ~OutputLayer();

  void feed_forward(Layer);
  void back_prop(Data* data);
  void update_weights(double, Layer*);
};

#endif // __OUTPUT_LAYER_HPP
