#if !defined(__KNN_H)
#define __KNN_H

#include "Data.hpp"
#include <vector>

class KNN
{
  int k;

  std::vector<Data*>* neighbors;
  std::vector<Data*>* training_data;
  std::vector<Data*>* test_data;
  std::vector<Data*>* validation_data;

  public:
  KNN(int);
  KNN();
  ~KNN();

  void find_knearest(Data* query_point);
  void set_training_data(std::vector<Data*>* vec);
  void set_test_data(std::vector<Data*>* vec);
  void set_validation_data(std::vector<Data*>* vec);
  void set_k(int val);

  int predict();
  double calculate_distance(Data* query_point, Data* input);
  double validate_performance();
  double test_performance();
};

#endif // __KNN_H
