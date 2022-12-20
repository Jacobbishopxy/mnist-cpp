#if !defined(__COMMON_HPP)
#define __COMMON_HPP

#include "Data.hpp"
#include <vector>

class CommonData
{
protected:
  std::vector<Data*>* training_data;
  std::vector<Data*>* test_data;
  std::vector<Data*>* validation_data;

public:
  void set_training_data(std::vector<Data*>* vec);
  void set_test_data(std::vector<Data*>* vec);
  void set_validation_data(std::vector<Data*>* vec);

};

#endif // __COMMON_HPP
