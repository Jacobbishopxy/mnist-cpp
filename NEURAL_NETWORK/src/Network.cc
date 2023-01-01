#include "Network.hpp"
#include "DataHandler.hpp"
#include "Layer.hpp"
#include <numeric>

Network::Network(std::vector<int> spec, int input_size, int num_classes, double learning_rate)
{
  for (int i = 0; i < spec.size(); i++)
  {
    if (i == 0)
      layers.push_back(new Layer{input_size, spec.at(i)});
    else
      layers.push_back(new Layer{(int)layers.at(i - 1)->neurons.size(), spec.at(i)});
  }
  layers.push_back(new Layer{(int)layers.at(layers.size() - 1)->neurons.size(), num_classes});
  this->learning_rate = learning_rate;
}

Network::~Network() {}

double Network::activate(std::vector<double> weights, std::vector<double> inputs)
{
  double activation = weights.back(); // bias term
  for (int i = 0; i < weights.size() - 1; i++)
  {
    activation += weights[i] * inputs[i];
  }
  return activation;
}

double Network::transfer(double activation)
{
  return 1.0 / (1.0 + exp(-activation));
}

double Network::transfer_derivative(double output)
{
  return output * (1 - output);
}

std::vector<double> Network::fprop(Data* data)
{
  std::vector<double> inputs = *data->get_normalized_feature_vector();
  for (int i = 0; i < layers.size(); i++)
  {
    Layer* layer = layers.at(i);
    std::vector<double> new_inputs;
    for (Neuron* n : layer->neurons)
    {
      double activation = this->activate(n->weights, inputs);
      n->output = this->transfer(activation);
      new_inputs.push_back(n->output);
    }
    inputs = new_inputs;
  }
  return inputs; // ouput layer outputs
}

void Network::bprop(Data* data)
{
  for (int i = layers.size() - 1; i >= 0; i--)
  {
    Layer* layer = layers.at(i);
    std::vector<double> errors;
    if (i != layers.size() - 1)
    {
      for (int j = 0; j < layer->neurons.size(); j++)
      {
        double error{0};
        for (Neuron* n : layers.at(i + 1)->neurons)
        {
          error += n->weights.at(j) * n->delta;
        }
        errors.push_back(error);
      }
    }
    else
    {
      for (int j = 0; j < layer->neurons.size(); j++)
      {
        Neuron* n = layer->neurons.at(j);
        errors.push_back((double)data->get_class_vector()->at(j) - n->output); // expected - actual
      }
    }

    for (int j = 0; j < layer->neurons.size(); j++)
    {
      Neuron* n = layer->neurons.at(j);
      n->delta = errors.at(j) * this->transfer_derivative(n->output); // gradient / derivative part of back prop.
    }
  }
}

void Network::update_weights(Data* data)
{
  std::vector<double> inputs = *data->get_normalized_feature_vector();
  for (int i = 0; i < layers.size(); i++)
  {
    if (i != 0)
    {
      for (Neuron* n : layers.at(i - 1)->neurons)
      {
        inputs.push_back(n->output);
      }
    }
    for (Neuron* n : layers.at(i)->neurons)
    {
      for (int j = 0; j < inputs.size(); j++)
      {
        n->weights.at(j) += this->learning_rate * n->delta * inputs.at(j);
      }
      n->weights.back() += this->learning_rate * n->delta;
    }
    inputs.clear();
  }
}

int Network::predict(Data* data)
{
  std::vector<double> outputs = fprop(data);
  return std::distance(outputs.begin(), std::max_element(outputs.begin(), outputs.end()));
}

void Network::train(int num_epochs)
{
  for (int i = 0; i < num_epochs; i++)
  {
    double sum_error{0};
    for (Data* data : *this->training_data)
    {
      std::vector<double> outputs = fprop(data);
      std::vector<int> expected = *data->get_class_vector();
      double temp_error_sum{0};
      for (int j = 0; j < outputs.size(); j++)
      {
        temp_error_sum += pow((double)expected.at(j) - outputs.at(j), 2);
      }
      sum_error += temp_error_sum;
      bprop(data);
      update_weights(data);
    }
    printf("Iteration: %d \t Error=%.4f", i, sum_error);
  }
}

double Network::test()
{
  double num_correct{0};
  double count{0};
  for (Data* data : *this->test_data)
  {
    count++;
    int index = predict(data);
    if (data->get_class_vector()->at(index) == 1)
      num_correct++;
  }

  test_performance = num_correct / count;
  return test_performance;
}

void Network::validate()
{
  double num_correct{0};
  double count{0};
  for (Data* data : *this->validation_data)
  {
    count++;
    int index = predict(data);
    if (data->get_class_vector()->at(index) == 1)
      num_correct++;
  }
  printf("Validation performance: %.4f\n", num_correct / count);
}

int main()
{
  DataHandler* dh{new DataHandler()};

#ifdef MNIST
  dh->read_feature_vector("../data/train-images-idx3-ubyte");
  dh->read_feature_labels("../data/train-labels-idx1-ubyte");
  dh->count_classes();
  printf("read mnist\n");
#else
  dh->read_csv("../data/iris.data", ",");
  printf("read iris\n");
#endif

  dh->split_data();
  std::vector<int> hidden_layers{10};
  auto lambda = [&]()
  {
    int input_size{(int)dh->get_training_data()->at(0)->get_normalized_feature_vector()->size()};
    int num_classes{dh->get_class_counts()};

    Network* nw = new Network(
        hidden_layers,
        input_size,
        num_classes,
        0.25);

    nw->set_training_data(dh->get_training_data());
    nw->set_test_data(dh->get_test_data());
    nw->set_validation_data(dh->get_validation_data());
    nw->train(15);
    nw->validate();

    printf("Test performance: %.3f\n", nw->test());
  };

  lambda();

  return 0;
}
