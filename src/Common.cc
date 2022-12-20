
#include "Common.hpp"

void CommonData::set_training_data(std::vector<Data*>* vec)
{
  training_data = vec;
}
void CommonData::set_test_data(std::vector<Data*>* vec)
{
  test_data = vec;
}
void CommonData::set_validation_data(std::vector<Data*>* vec)
{
  validation_data = vec;
}
