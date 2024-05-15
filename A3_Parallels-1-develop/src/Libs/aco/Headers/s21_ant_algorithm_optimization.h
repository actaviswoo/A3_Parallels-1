#ifndef A3_PARALLELS_SRC_LIBS_ACO_HEADERS_S21_ANT_ALGORITHM_OPTIMIZATION_H
#define A3_PARALLELS_SRC_LIBS_ACO_HEADERS_S21_ANT_ALGORITHM_OPTIMIZATION_H

#include <algorithm>
#include <chrono>
#include <cmath>
#include <memory>
#include <random>

namespace s21 {

struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

class AntAlgorithmOptimization {
   public:
    AntAlgorithmOptimization() = delete;
    AntAlgorithmOptimization(const std::vector<std::vector<int>>& matrix);
    ~AntAlgorithmOptimization() {}

   protected:
   struct Ant {
      Ant(int start_vertex = 0) : start(start_vertex), current(start_vertex), is_finished(false) {}
      TsmResult path;
      std::vector<int> visited;
      int start = 0;
      int current = 0;
      bool is_finished = false;
    };
    const double kAlpha_ = 1.0;
    const double kBeta_ = 2.0;
    const double kPheromone_ = 1;
    const double kQ_ = 5.0;
    const double kEvaporation_ = 0.2;
    std::vector<std::vector<double>> pheromone_;
    const std::vector<std::vector<int>> adjacencyMatrix_;
    const std::size_t size_;
    const int imax_ = std::numeric_limits<int>::max();

    std::vector<Ant> InitAnts();
    std::vector<int> InitNeighbours(Ant& ant);
    std::vector<double> InitProbabilities(Ant& ant, std::vector<int> neigbhors);
    double InitChoice();
    int InitNext(double choice, std::vector<int> neighbours, std::vector<double> probabilities);
    void CheckNeighbours(Ant& ant);
    void MakeChoice(Ant& ant);
    void UpdatePheromone(const std::vector<std::vector<double>>& localPheromones);
};


}  // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_ACO_HEADERS_S21_ANT_ALGORITHM_OPTIMIZATION_H
