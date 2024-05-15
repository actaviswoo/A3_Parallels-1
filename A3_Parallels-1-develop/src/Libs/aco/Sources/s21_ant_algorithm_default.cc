#include "../Headers/s21_ant_algorithm_default.h"

namespace s21 {

AntAlgorithmDefault::AntAlgorithmDefault(const std::vector<std::vector<int>>& adjacencyMatrix) : AntAlgorithmOptimization(adjacencyMatrix) {}

TsmResult AntAlgorithmDefault::Algorithm() {
  TsmResult result;
  std::size_t maxIteration = 5000;
  std::size_t count = 0;
  result.distance = imax_;
  while (count != maxIteration) {
    count++;
    std::vector<std::vector<double>> localPheromones(size_, std::vector<double>(size_, 0));
    std::vector<Ant> ants_ = InitAnts();
    for (auto& ant : ants_) {
      while (!ant.is_finished) {
        MakeChoice(ant);
      }
      CheckAnt(ant, result, &count, localPheromones);
    }
    UpdatePheromone(localPheromones);
  }
  return result;
}

void AntAlgorithmDefault::CheckAnt(
    Ant& ant, TsmResult& result, std::size_t* count,
    std::vector<std::vector<double>> localPheromones) {
  TsmResult ant_path = ant.path;
  if (ant_path.vertices.size() == size_ + 1) {
    if (result.distance > ant.path.distance) {
      result = std::move(ant.path);
      *count = 0;
    }
    for (std::size_t v = 0; v != ant_path.vertices.size() - 1; ++v) {
      localPheromones[ant_path.vertices[v]][ant_path.vertices[v + 1]] +=
          kQ_ / ant_path.distance;
    }
  }
}

}