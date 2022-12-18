#include "Data.hpp"

Data::Data()
{
  feature_vector = new std::vector<uint8_t>;
}
Data::~Data()
{
  // FREE
}

void Data::set_feature_vector(std::vector<uint8_t>* vec)
{
  feature_vector = vec;
}
void Data::append_to_feature_vector(uint8_t val)
{
  feature_vector->push_back(val);
}
void Data::set_label(uint8_t val)
{
  label = val;
}
void Data::set_enumerated_label(int val)
{
  enum_label = val;
}

std::vector<uint8_t>* Data::get_feature_vector()
{
  return feature_vector;
}
int Data::get_feature_vector_size()
{
  return feature_vector->size();
}
uint8_t Data::get_label()
{
  return label;
}
uint8_t Data::get_enumerated_label()
{
  return enum_label;
}
