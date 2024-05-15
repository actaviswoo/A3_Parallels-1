#include "../Headers/s21_ant_algorithm_optimization.h"

namespace s21 {

AntAlgorithmOptimization::AntAlgorithmOptimization(const std::vector<std::vector<int>>& adjacencyMatrix)
    : adjacencyMatrix_(adjacencyMatrix), size_(adjacencyMatrix.size()) {
  if (adjacencyMatrix_.empty()) {
    throw std::exception();
  }
  std::vector<std::vector<double>> p(size_, std::vector<double>(size_));
  for (std::size_t i = 0; i != size_; i++) {
    for (std::size_t j = 0; j != size_; j++) {
      if (i != j) {
        p[i][j] = kPheromone_;
      }
    }
  }
  pheromone_ = std::move(p);
  }

std::vector<s21::AntAlgorithmOptimization::Ant> AntAlgorithmOptimization::InitAnts() {
  std::vector<Ant> ants(size_);
  for (std::size_t i = 0, size = ants.size(); i != size; ++i) {
    ants[i] = Ant(i);
  }
  return ants;
}

void AntAlgorithmOptimization::MakeChoice(Ant& ant) {
  if (ant.path.vertices.empty()) {
    ant.path.vertices.push_back(ant.current);
    ant.visited.push_back(ant.current);
  }

  std::vector<int> neighbours = InitNeighbours(ant);
  if (neighbours.empty()) {
    CheckNeighbours(ant);
    return;
  }

  std::vector<double> probabilities = InitProbabilities(ant, neighbours);
  double choice = InitChoice();
  int next = InitNext(choice, neighbours, probabilities);
  ant.path.vertices.push_back(next);
  ant.visited.push_back(next);
  ant.path.distance += adjacencyMatrix_[ant.current][next];
  ant.current = next;
}

std::vector<int> AntAlgorithmOptimization::InitNeighbours(Ant& ant) {
  std::vector<int> neighbours;
  for (std::size_t i = 0; i != size_; i++) {
    if (adjacencyMatrix_[ant.current][i] != 0 &&
        std::find(ant.visited.begin(), ant.visited.end(), i) ==
            ant.visited.end()) {
      neighbours.push_back(i);
    }
  }
  return neighbours;
}

void AntAlgorithmOptimization::CheckNeighbours(Ant& ant) {
  ant.is_finished = true;
  if (adjacencyMatrix_[ant.current][ant.start] != 0) {
    ant.path.vertices.push_back(ant.start);
    ant.path.distance += adjacencyMatrix_[ant.current][ant.start];
  }
}

double AntAlgorithmOptimization::InitChoice() {
  std::uniform_real_distribution<> dist(0.0, 1.0);
  std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
  return dist(re);
}

int AntAlgorithmOptimization::InitNext(double choice,
                                            std::vector<int> neighbours,
                                            std::vector<double> probabilities) {
  int next;
  std::size_t size = neighbours.size();
  for (std::size_t i = 0; i != size; i++) {
    if (choice <= probabilities[i]) {
      next = neighbours[i];
      break;
    }
  }
  return next;
}

std::vector<double> AntAlgorithmOptimization::InitProbabilities(Ant& ant, std::vector<int> neighbours) {
  std::vector<double> probabilities(neighbours.size());
  std::vector<double> wish;
  std::vector<double> probability;
  double summaryWish = 0.0f;
  for (auto neighbour : neighbours) {
    double pheremone = pheromone_[ant.current][neighbour];
    double weight = adjacencyMatrix_[ant.current][neighbour];
    double inverseWeight = 1 / weight;
    wish.push_back(std::pow(pheremone, kAlpha_) *
                   std::pow(inverseWeight, kBeta_));
    summaryWish += wish.back();
  }
  std::size_t size = neighbours.size();
  for (std::size_t i = 0; i != size; i++) {
    probability.push_back(wish[i] / summaryWish);
    if (i == 0) {
      probabilities[i] = probability.back();
    } else {
      probabilities[i] = probabilities[i - 1] + probability.back();
    }
  }
  return probabilities;
}

void AntAlgorithmOptimization::UpdatePheromone(const std::vector<std::vector<double>>& localPheromones) {
  for (std::size_t from = 0, size = localPheromones.size(); from != size; ++from) {
    for (std::size_t to = 0; to != size; ++to) {
      pheromone_[from][to] = (1 - kEvaporation_) * pheromone_[from][to] +
                             localPheromones[from][to];
      if (pheromone_[from][to] < 0.01 and from != to)
        pheromone_[from][to] = 0.01;
    }
  }
}

}


