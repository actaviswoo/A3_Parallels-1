#include "../Headers/s21_aco.h"

namespace s21 {

bool Aco::LoadMatrixFromFile(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) return false;
  file >> size_;
  if (file.fail() || size_ <= 0) {
    file.close();
    size_ = 0;
    return false;
  }
  std::vector<std::vector<int>> matrix(size_, std::vector<int>(size_));
  for (std::size_t i = 0; i < size_; i++) {
    for (std::size_t j = 0; j < size_; j++) {
      file >> matrix[i][j];
      if (file.fail()) {
        file.close();
        size_ = 0;
        return false;
      }
    }
  }
  adjacencyMatrix_ = std::move(matrix);
  file.close();
  return true;
}

bool Aco::InputMatrix() {
    std::cin.clear();
    std::cin >> size_;
    if (std::cin.fail() || size_ <= 0) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        return false;
    }
    std::vector<std::vector<int>> matrix(size_, std::vector<int>(size_));
    for (std::size_t i = 0; i < size_; i++) {
        for (std::size_t j = 0; j < size_; j++) {
            std::cin >> matrix[i][j];
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                return false;
            }
        }
    }
    adjacencyMatrix_ = std::move(matrix);
    return true;
}


TsmResult Aco::GetResultDefault() {
    TsmResult result;
    AntAlgorithmDefault antAlgorithmDefault(adjacencyMatrix_);
    result = antAlgorithmDefault.Algorithm();
    return result;
}
TsmResult Aco::GetResultAdvanced() {
    TsmResult result;
    AntAlgorithmAdvanced antAlgorithmAdvanced(adjacencyMatrix_);
    result = antAlgorithmAdvanced.Algorithm();
    return result;
}

std::vector<std::vector<int>> Aco::GetAdjacencyMatrix() {
  return adjacencyMatrix_;
}

std::size_t Aco::GetSize() {
  return size_;
}

}  // namespace s21