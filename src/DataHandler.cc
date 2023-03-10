#include "DataHandler.hpp"

DataHandler::DataHandler()
{
  data_array = new std::vector<Data*>;
  test_data = new std::vector<Data*>;
  training_data = new std::vector<Data*>;
  validation_data = new std::vector<Data*>;
}
DataHandler::~DataHandler()
{
  // FREE Dynamically Allocated Memory
}

void DataHandler::read_csv(std::string path, std::string delimiter)
{
  num_classes = 0;
  std::ifstream data_file;
  data_file.open(path.c_str());
  std::string line; // holds each line

  while (std::getline(data_file, line))
  {
    if (line.length() == 0)
      continue; // skip empty line
    Data* d{new Data()};
    d->set_normalized_feature_vector(new std::vector<double>());
    size_t position{0};
    std::string token; // value in between delimiter
    while ((position = line.find(delimiter)) != std::string::npos)
    {
      token = line.substr(0, position);
      d->append_to_feature_vector(std::stod(token));
      line.erase(0, position + delimiter.length());
    }

    if (class_map_str.find(line) != class_map_str.end())
    {
      d->set_label(class_map_str[line]);
    }
    else
    {
      class_map_str[line] = num_classes;
      d->set_label(class_map_str[line]);
      num_classes++;
    }
    data_array->push_back(d);
  }
  for (Data* data : *data_array)
    data->set_class_vector(num_classes);
  // normalize();
  feature_vector_size = data_array->at(0)->get_normalized_feature_vector()->size();
}

void DataHandler::read_feature_vector(std::string path)
{
  uint32_t header[4]; // |MAGIC NUM|NUM IMAGES|ROW SIZE|COL SIZE|
  unsigned char bytes[4];
  FILE* f = fopen(path.c_str(), "r"); // open file
  if (f)
  {
    for (int i = 0; i < 4; i++)
    {
      if (fread(bytes, sizeof(bytes), 1, f)) // read file
      {
        header[i] = convert_to_little_endian(bytes);
      }
    }
    printf("Done getting input file header.\n");

    int image_size = header[2] * header[3];
    for (int i = 0; i < header[1]; i++)
    {
      Data* d = new Data(); // The only place initialized a new data container
      uint8_t element[1];
      for (int j = 0; j < image_size; j++)
      {
        if (fread(element, sizeof(element), 1, f))
        {
          d->append_to_feature_vector(element[0]);
        }
        else
        {
          printf("Error reading from file.\n");
          exit(1);
        }
      }
      data_array->push_back(d);
    }
    printf("Successfully read and stored %lu feature vectors.\n", data_array->size());
  }
  else
  {
    printf("Could not find feature_vector file.\n");
    exit(1);
  }
}
void DataHandler::read_feature_labels(std::string path)
{
  uint32_t header[2]; // |MAGIC NUM|NUM IMAGES|
  unsigned char bytes[4];
  FILE* f = fopen(path.c_str(), "r"); // open file
  if (f)
  {
    for (int i = 0; i < 2; i++)
    {
      if (fread(bytes, sizeof(bytes), 1, f)) // read file
      {
        header[i] = convert_to_little_endian(bytes);
      }
    }
    printf("Done getting label file header.\n");

    for (int i = 0; i < header[1]; i++)
    {
      uint8_t element[1];
      if (fread(element, sizeof(element), 1, f))
      {
        data_array->at(i)->set_label(element[0]);
      }
      else
      {
        printf("Error reading from file.\n");
        exit(1);
      }
    }
    printf("Successfully read and stored label.\n");
  }
  else
  {
    printf("Could not find feature_labels file.\n");
    exit(1);
  }
}
void DataHandler::split_data()
{
  std::unordered_set<int> used_indexes;
  int train_size = data_array->size() * TRAIN_SET_PERCENT;
  int test_size = data_array->size() * TEST_SET_PERCENT;
  int valid_size = data_array->size() * VALIDATION_PERCENT;

  // Training data

  int count = 0;
  while (count < train_size)
  {
    int rand_index = rand() % data_array->size();            // a range from 0 to data_array->size() - 1
    if (used_indexes.find(rand_index) == used_indexes.end()) // if not find, use it as a new index
    {
      training_data->push_back(data_array->at(rand_index));
      used_indexes.insert(rand_index);
      count++;
    }
  }

  // Test data

  count = 0;
  while (count < test_size)
  {
    int rand_index = rand() % data_array->size();            // a range from 0 to data_array->size() - 1
    if (used_indexes.find(rand_index) == used_indexes.end()) // if not find, use it as a new index
    {
      test_data->push_back(data_array->at(rand_index));
      used_indexes.insert(rand_index);
      count++;
    }
  }

  // Validation data

  count = 0;
  while (count < valid_size)
  {
    int rand_index = rand() % data_array->size();            // a range from 0 to data_array->size() - 1
    if (used_indexes.find(rand_index) == used_indexes.end()) // if not find, use it as a new index
    {
      validation_data->push_back(data_array->at(rand_index));
      used_indexes.insert(rand_index);
      count++;
    }
  }

  printf("Training data size: %lu.\n", training_data->size());
  printf("Test data size: %lu.\n", test_data->size());
  printf("Validation data size: %lu.\n", validation_data->size());
}
void DataHandler::count_classes()
{
  int count = 0;
  for (unsigned i = 0; i < data_array->size(); i++)
  {
    if (class_map.find(data_array->at(i)->get_label()) == class_map.end())
    {
      class_map[data_array->at(i)->get_label()] = count;
      data_array->at(i)->set_enumerated_label(count);
      count++;
    }
  }
  num_classes = count;
  printf("Successfully extracted %d unique classes.\n", num_classes);
}
void DataHandler::normalize()
{
  std::vector<double> mins, maxs;

  // file min and max lists
  Data* d = data_array->at(0);
  for (auto val : *d->get_feature_vector())
  {
    mins.push_back(val);
    maxs.push_back(val);
  }

  for (int i = 1; i < data_array->size(); i++)
  {
    d = data_array->at(i);
    for (int j = 0; j < j < d->get_feature_vector_size(); j++)
    {
      double value = (double)d->get_class_vector()->at(j);
      if (value < mins.at(j))
        mins[j] = value;
      if (value > maxs.at(j))
        maxs[j] = value;
    }
  }

  // normalize data array
  for (int i = 0; i < data_array->size(); i++)
  {
    data_array->at(i)->set_normalized_feature_vector(new std::vector<double>());
    data_array->at(i)->set_class_vector(num_classes);
    for (int j = 0; j < data_array->at(i)->get_feature_vector_size(); j++)
    {
      if (maxs[j] - mins[j] == 0)
        data_array->at(i)->append_to_normalized_feature_vector(0);
      else
        data_array->at(i)->append_to_normalized_feature_vector(
            (double)(data_array->at(i)->get_feature_vector()->at(j) - mins[j]) / (maxs[j] - mins[j]));
    }
  }
}

uint32_t DataHandler::convert_to_little_endian(const unsigned char* bytes)
{
  // convert big endian to little endian
  // check this: https://stackoverflow.com/a/2182184/8163324
  return (uint32_t)((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3]));
}

int DataHandler::get_class_counts()
{
  return num_classes;
}
std::vector<Data*>* DataHandler::get_training_data()
{
  return training_data;
}
std::vector<Data*>* DataHandler::get_test_data()
{
  return test_data;
}
std::vector<Data*>* DataHandler::get_validation_data()
{
  return validation_data;
}

/*
int main()
{
  DataHandler* dh = new DataHandler();
  // relative path is used because compiled files are under ${workspace}/dev/
  dh->read_feature_vector("../data/train-images-idx3-ubyte");
  dh->read_feature_labels("../data/train-labels-idx1-ubyte");
  dh->split_data();
  dh->count_classes();
}
*/
