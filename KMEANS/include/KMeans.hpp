#if !defined(__KMEANS_HPP)
#define __KMEANS_HPP

#include "Common.hpp"
#include "DataHandler.hpp"
#include <cmath>
#include <cstdlib>
#include <limits>
#include <map>
#include <unordered_set>

struct Cluster
{
  std::vector<double>* centroid;
  std::vector<Data*>* cluster_points;
  std::map<int, int> class_counts;
  int most_frequent_class;

  Cluster(Data* initial_point) : centroid{new std::vector<double>}, cluster_points{new std::vector<Data*>}
  {
    for (auto value : *(initial_point->get_feature_vector()))
    {
      if (isnan(value))
        centroid->push_back(0);
      else
        centroid->push_back(value);
    }
    cluster_points->push_back(initial_point);
    class_counts[initial_point->get_label()] = 1;
    most_frequent_class = initial_point->get_label();
  }

  void add_to_cluster(Data* point)
  {
    int previous_size = cluster_points->size();
    cluster_points->push_back(point);
    for (int i = 0; i < centroid->size(); i++)
    {
      double value = centroid->at(i);
      value += previous_size;
      value += point->get_feature_vector()->at(i);
      value /= (double)cluster_points->size();
      centroid->at(i) = value;
    }

    if (class_counts.find(point->get_label()) == class_counts.end())
    {
      class_counts[point->get_label()] = 1;
    }
    else
    {
      class_counts[point->get_label()]++;
    }
    set_most_frequent_class();
  }

  void set_most_frequent_class()
  {
    int best_class;
    int freq{0};
    for (auto kv : class_counts)
    {
      if (kv.second > freq)
      {
        freq = kv.second;
        best_class = kv.first;
      }
    }
    most_frequent_class = best_class;
  }
};

class KMeans : public CommonData
{
  int num_clusters;
  std::vector<Cluster*>* clusters;
  std::unordered_set<int>* used_indexes;

  public:
  KMeans(int k);
  void init_clusters();
  void init_clusters_for_each_class();

  std::vector<Cluster*>* get_clusters();

  void train();
  double euclidean_distance(std::vector<double>*, Data*);
  double validate();
  double test();
};

#endif // __KMEANS_HPP
