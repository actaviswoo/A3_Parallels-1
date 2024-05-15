#include "../Headers/s21_gauss_optimization.h"

#include <iostream>
namespace s21 {

GaussOptimization::GaussOptimization(const std::vector<std::vector<double>>& augmentedMatrix) 
    : size_(augmentedMatrix.size()) {
    Init(matrix_, constantTerm_, augmentedMatrix);
}


void GaussOptimization::Init(std::vector<std::vector<double>>& matrix, std::vector<double>& constantTerm, const std::vector<std::vector<double>>& augmentedMatrix) {
    matrix.resize(size_, std::vector<double>(size_));
    constantTerm.resize(size_);
    for (std::size_t i = 0; i < size_; i++) {
        constantTerm[i] = augmentedMatrix[i][size_];
        for (std::size_t j = 0; j < size_; j++) {
            matrix[i][j] = augmentedMatrix[i][j]; 
        }
    }
}

double GaussOptimization::StepFindMaxIndex(std::size_t nowIndex) {
  double max = std::abs(matrix_[nowIndex][nowIndex]);
  std::size_t maxIndex = nowIndex;
  for (std::size_t i = nowIndex + 1; i < size_; i++) {
    if (std::abs(matrix_[i][nowIndex]) > max) {
      max = std::abs(matrix_[i][nowIndex]);
      maxIndex = i;
    }
  }
  return maxIndex;
}

void GaussOptimization::StepSwapCols(std::size_t nowIndex, std::size_t maxIndex) {
  for (std::size_t j = 0; j < size_; j++) {
    std::swap(matrix_[nowIndex][j], matrix_[maxIndex][j]);
  }
  std::swap(constantTerm_[nowIndex], constantTerm_[maxIndex]);
}

std::vector<double> GaussOptimization::StepBackSubstitution() {
  std::vector<double> result(size_);
    for (int k = size_ - 1; k != -1; k--) {
      result[k] = constantTerm_[k];
      for (int i = 0; i < k; i++) {
        constantTerm_[i] = constantTerm_[i] - matrix_[i][k] * result[k];
      }
  }
  return result;
}

} // namespace s21
