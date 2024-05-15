#include "../Headers/s21_ant_algorithm_advanced.h"

namespace s21 {

AntAlgorithmAdvanced::AntAlgorithmAdvanced(const std::vector<std::vector<int>>& adjacencyMatrix) : AntAlgorithmOptimization(adjacencyMatrix) {}

TsmResult AntAlgorithmAdvanced::Algorithm() {
    TsmResult result;
    std::size_t maxIteration = 5000;
    std::size_t count = 0;
    result.distance = imax_;
    while (count != maxIteration) {
        count++;
        std::vector<std::vector<double>> localPheromones(size_, std::vector<double>(size_, 0));
        std::vector<Ant> ants = InitAnts();
        for (std::size_t i = 0; i < numThreads_; ++i) {
            threads_.emplace_back([this, &ants, &result, &count, &localPheromones, i]() {
                std::size_t rangeThreadSize = ants.size() / numThreads_;
                std::size_t startIndex = i * rangeThreadSize;
                std::size_t endIndex = (i == numThreads_ - 1) ? ants.size() : (startIndex + rangeThreadSize);

                for (std::size_t j = startIndex; j < endIndex; ++j) {
                    Ant& ant = ants[j];
                    while (!ant.is_finished) {
                        MakeChoice(ant);
                    }
                    CheckAnt(ant, result, &count, localPheromones);
                }
            });
        }
        for (auto& thread : threads_) thread.join();
        threads_.clear();
        UpdatePheromone(localPheromones);
    }

    return result;
}

void AntAlgorithmAdvanced::CheckAnt(
    Ant& ant, TsmResult& result, std::size_t* count,
    std::vector<std::vector<double>> localPheromones) {
  TsmResult ant_path = ant.path;
  if (ant_path.vertices.size() == size_ + 1) {
    std::lock_guard<std::mutex> lock(mutex_);
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