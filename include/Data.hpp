#if !defined(__DATA_H)
#define __DATA_H

#include "stdint.h"
#include "stdio.h"
#include <vector>

class Data
{
  std::vector<uint8_t>* feature_vector; // No call at end.
  uint8_t label;                        // actual class
  int enum_label;                       // A -> 1, B -> 2

  public:
  Data();
  ~Data();

  void set_feature_vector(std::vector<uint8_t>*);
  void append_to_feature_vector(uint8_t);
  void set_label(uint8_t);
  void set_enumerated_label(int);

  std::vector<uint8_t>* get_feature_vector();
  int get_feature_vector_size();
  uint8_t get_label();
  uint8_t get_enumerated_label();
};

#endif // __DATA_H