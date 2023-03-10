#if !defined(__DATA_HANDLER_H)
#define __DATA_HANDLER_H

#include "Data.hpp"
#include "stdint.h"
#include <fstream>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

class DataHandler
{
  std::vector<Data*>* data_array; // all of the data (pre-split)
  std::vector<Data*>* training_data;
  std::vector<Data*>* test_data;
  std::vector<Data*>* validation_data;

  int num_classes;
  int feature_vector_size;
  std::map<uint8_t, int> class_map;
  std::map<std::string, int> class_map_str;

  const double TRAIN_SET_PERCENT = 0.75;
  const double TEST_SET_PERCENT = 0.20;
  const double VALIDATION_PERCENT = 0.05;

  public:
  DataHandler();
  ~DataHandler();

  void read_csv(std::string path, std::string delimiter);
  void read_feature_vector(std::string path);
  void read_feature_labels(std::string path);
  void split_data();
  void count_classes();
  void normalize();

  uint32_t convert_to_little_endian(const unsigned char* bytes);

  int get_class_counts();
  std::vector<Data*>* get_training_data();
  std::vector<Data*>* get_test_data();
  std::vector<Data*>* get_validation_data();
  std::map<uint8_t, int> get_class_map();
  std::map<std::string, int> get_class_map_str();
};

#endif // __DATA_HANDLER_H
