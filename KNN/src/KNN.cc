#include "KNN.hpp"
#include "DataHandler.hpp"
#include "stdint.h"
#include <cmath>
#include <limits>
#include <map>

KNN::KNN(int val)
{
  k = val;
}
KNN::KNN()
{
  // NOTING TO DO
}
KNN::~KNN()
{
  // NOTING TO DO
}

// O(N^2) if K ~ N
// if K = 2 then O(~N)
// O(NlogN)

void KNN::find_knearest(Data* query_point)
{
  neighbors = new std::vector<Data*>;
  double min = std::numeric_limits<double>::max();
  double previous_min = min;
  int index = 0;
  for (int i = 0; i < k; i++)
  {
    if (i == 0)
    {
      for (int j = 0; j < training_data->size(); j++)
      {
        double distance = calculate_distance(query_point, training_data->at(j));
        training_data->at(j)->set_distance(distance);
        if (distance < min)
        {
          min = distance;
          index = j;
        }
      }
      neighbors->push_back(training_data->at(index));
      previous_min = min;
      min = std::numeric_limits<double>::max();
    }
    else
    {
      for (int j = 0; j < training_data->size(); j++)
      {
        double distance = training_data->at(j)->get_distance();
        if (distance > previous_min && distance < min)
        {
          min = distance;
          index = j;
        }
      }
      neighbors->push_back(training_data->at(index));
      previous_min = min;
      min = std::numeric_limits<double>::max();
    }
  }
}
void KNN::set_k(int val)
{
  k = val;
}

int KNN::predict()
{
  std::map<uint8_t, int> class_freq;
  for (int i = 0; i < neighbors->size(); i++)
  {
    if (class_freq.find(neighbors->at(i)->get_label()) == class_freq.end())
    {
      class_freq[neighbors->at(i)->get_label()] = 1;
    }
    else
    {
      class_freq[neighbors->at(i)->get_label()]++;
    }
  }

  int best = 0;
  int max = 0;
  for (auto kv : class_freq)
  {
    if (kv.second > max)
    {
      max = kv.second;
      best = kv.first;
    }
  }
  // delete neighbors;
  neighbors->clear();

  return best;
}
double KNN::calculate_distance(Data* query_point, Data* input)
{
  double distance = 0;
  if (query_point->get_feature_vector_size() != input->get_feature_vector_size())
  {
    printf("Error vector size mismatch.\n");
    exit(1);
  }
#ifdef EUCLID
  for (unsigned i = 0; i < query_point->get_feature_vector_size(); i++)
  {
    distance += pow(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i), 2);
  }
  return sqrt(distance);
#elif defined MANHATTAN
  // PUT MANHATTAN IMPLEMENTATION HERE
#endif
}
double KNN::validate_performance()
{
  double current_performance = 0;
  int count = 0;
  int data_index = 0;
  for (Data* query_point : *validation_data)
  {
    find_knearest(query_point);
    int prediction = predict();
    printf("%d -> %d\n", prediction, query_point->get_label());
    data_index++;
    if (prediction == query_point->get_label())
    {
      count++;
    }
    double numerator = (double)count;
    double denominator = (double)data_index;
    double cp = numerator / denominator * 100;
    printf("Current performance %.3f / %.3f = %.3f\n", numerator, denominator, cp);
  }
  current_performance = ((double)count) / ((double)validation_data->size()) * 100;
  printf("Validation performance for K = %d = %.3f\n", k, current_performance);
  return current_performance;
}
double KNN::test_performance()
{
  double current_performance = 0;
  int count = 0;
  for (Data* query_point : *test_data)
  {
    find_knearest(query_point);
    int prediction = predict();
    if (prediction == query_point->get_label())
    {
      count++;
    }
  }
  current_performance = ((double)count) * 100.0 / ((double)test_data->size());
  printf("Tested performance for K = %d: %.3f\n", k, current_performance);
  return current_performance;
}

/*
int main()
{
  DataHandler* dh = new DataHandler();
  dh->read_feature_vector("../data/train-images-idx3-ubyte");
  dh->read_feature_labels("../data/train-labels-idx1-ubyte");
  dh->count_classes();
  dh->split_data();

  KNN* knearest = new KNN();
  knearest->set_training_data(dh->get_training_data());
  knearest->set_test_data(dh->get_test_data());
  knearest->set_validation_data(dh->get_validation_data());

  double performance = 0;
  double best_performance = 0;
  double best_k = 1;
  for (int i = 1; i <= 3; i++)
  {
    if (i == 1)
    {
      knearest->set_k(i);
      performance = knearest->validate_performance();
      best_performance = performance;
    }
    else
    {
      knearest->set_k(i);
      performance = knearest->validate_performance();
      if (performance > best_performance)
      {
        best_performance = performance;
        best_k = i;
      }
    }
  }
  knearest->set_k(best_k);
  knearest->test_performance();
}
*/
