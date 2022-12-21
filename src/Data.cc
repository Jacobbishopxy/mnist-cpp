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
void Data::set_double_feature_vector(std::vector<double>* vec)
{
  double_feature_vector = vec;
}
void Data::append_to_feature_vector(double val)
{
  double_feature_vector->push_back(val);
}

void Data::set_label(uint8_t val)
{
  label = val;
}
void Data::set_enumerated_label(int val)
{
  enum_label = val;
}
void Data::set_distance(double val)
{
  distance = val;
}
void Data::set_class_vector(int count)
{
  class_vector = new std::vector<int>();
  for (int i = 0; i < count; i++)
  {
    if (i == label)
      class_vector->push_back(1);
    else
      class_vector->push_back(0);
  }
}

std::vector<uint8_t>* Data::get_feature_vector()
{
  return feature_vector;
}
std::vector<double>* Data::get_double_feature_vector()
{
  return double_feature_vector;
}
std::vector<int>* Data::get_class_vector()
{
  return class_vector;
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
double Data::get_distance()
{
  return distance;
}
