#include "KMeans.hpp"

KMeans::KMeans(int k)
{
  num_clusters = k;
  clusters = new std::vector<Cluster*>;
  used_indexes = new std::unordered_set<int>;
}

void KMeans::init_clusters()
{
  for (int i = 0; i < num_clusters; i++)
  {
    int index = rand() % training_data->size(); // list initialization needs `static_cast<int>` here
    while (used_indexes->find(index) != used_indexes->end())
    {
      index = rand() % training_data->size();
    }
    clusters->push_back(new Cluster(training_data->at(index)));
    used_indexes->insert(index);
  }
}
void KMeans::init_clusters_for_each_class()
{
  std::unordered_set<int> classes_used;
  for (int i = 0; i < training_data->size(); i++)
  {
    if (classes_used.find(training_data->at(i)->get_label()) == classes_used.end())
    {
      clusters->push_back(new Cluster(training_data->at(i)));
      classes_used.insert(training_data->at(i)->get_label());
      used_indexes->insert(i);
    }
  }
}

std::vector<Cluster*>* KMeans::get_clusters()
{
  return this->clusters;
}

void KMeans::train()
{
  while (used_indexes->size() < training_data->size())
  {
    int index = rand() % training_data->size();
    while (used_indexes->find(index) != used_indexes->end())
    {
      index = rand() % training_data->size();
    }
    double min_dist{std::numeric_limits<double>::max()};
    int best_cluster{0};
    for (int j = 0; j < clusters->size(); j++)
    {
      double current_dist{euclidean_distance(clusters->at(j)->centroid, training_data->at(index))};
      if (current_dist < min_dist)
      {
        min_dist = current_dist;
        best_cluster = j;
      }
    }
    clusters->at(best_cluster)->add_to_cluster(training_data->at(index));
    used_indexes->insert(index);
  }
}
double KMeans::euclidean_distance(std::vector<double>* centroid, Data* point)
{
  double dist{0};
  for (int i = 0; i < centroid->size(); i++)
  {
    dist += pow(centroid->at(i) - point->get_feature_vector()->at(i), 2);
  }
  return sqrt(dist);
}
double KMeans::validate()
{
  double num_correct{0};
  for (auto query_point : *validation_data)
  {
    double min_dist{std::numeric_limits<double>::max()};
    int best_cluster{0};
    for (int j = 0; j < clusters->size(); j++)
    {
      double current_dist{euclidean_distance(clusters->at(j)->centroid, query_point)};
      if (current_dist < min_dist)
      {
        min_dist = current_dist;
        best_cluster = j;
      }
    }
    if (clusters->at(best_cluster)->most_frequent_class == query_point->get_label())
      num_correct++;
  }
  return 100.0 * (num_correct / (double)validation_data->size());
}
double KMeans::test()
{
  double num_correct{0};
  for (auto query_point : *test_data)
  {
    double min_dist{std::numeric_limits<double>::max()};
    int best_cluster{0};
    for (int j = 0; j < clusters->size(); j++)
    {
      double current_dist{euclidean_distance(clusters->at(j)->centroid, query_point)};
      if (current_dist < min_dist)
      {
        min_dist = current_dist;
        best_cluster = j;
      }
    }
    if (clusters->at(best_cluster)->most_frequent_class == query_point->get_label())
      num_correct++;
  }
  return 100.0 * (num_correct / (double)test_data->size());
}

int main()
{
  DataHandler* dh{new DataHandler()};
  dh->read_feature_vector("../data/train-images-idx3-ubyte");
  dh->read_feature_labels("../data/train-labels-idx1-ubyte");
  dh->count_classes();
  dh->split_data();

  double performance{0};
  double best_performance{0};
  int best_k{1};
  for (int k = dh->get_class_counts(); k < dh->get_training_data()->size() * 0.1; k++)
  {
    KMeans* km{new KMeans(k)};
    km->set_training_data(dh->get_training_data());
    km->set_test_data(dh->get_test_data());
    km->set_validation_data(dh->get_validation_data());
    km->init_clusters();
    km->train();
    performance = km->validate();
    printf("Current performance @ K = %d: %.2f\n", k, performance);
    if (performance > best_performance)
    {
      best_performance = performance;
      best_k = k;
    }
  }

  KMeans* km{new KMeans(best_k)};
  km->set_training_data(dh->get_training_data());
  km->set_test_data(dh->get_test_data());
  km->set_validation_data(dh->get_validation_data());
  km->init_clusters();
  performance = km->test();
  printf("Tested performance %.2f\n", performance);
}
