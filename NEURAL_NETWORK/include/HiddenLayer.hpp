#if !defined(__HIDDEN_LAYER_HPP)
#define __HIDDEN_LAYER_HPP

#include "Layer.hpp"

class HiddenLayer : public Layer
{
  private:
  /* data */
  public:
  HiddenLayer(int prev, int curr) : Layer{prev, curr} {};
  ~HiddenLayer();

  void feed_forward(Layer prev);
  void back_prop(Layer next);
  void update_weights(double, Layer*);
};

#endif // __HIDDEN_LAYER_HPP
