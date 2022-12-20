#if !defined(__KNN_H)
#define __KNN_H

#include "Common.hpp"
#include "Data.hpp"

class KNN : public CommonData
{
  int k;

  std::vector<Data*>* neighbors;

  public:
  KNN(int);
  KNN();
  ~KNN();

  void find_knearest(Data* query_point);
  void set_k(int val);

  int predict();
  double calculate_distance(Data* query_point, Data* input);
  double validate_performance();
  double test_performance();
};

#endif // __KNN_H
