#include "../Headers/s21_sle.h"

namespace s21 {

bool Sle::LoadMatrixFromFile(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) return false;
  file >> size_;
  if (file.fail() || size_ <= 0) {
    file.close();
    size_ = 0;
    return false;
  }
  std::vector<std::vector<double>> matrix(size_, std::vector<double>(size_ + 1));
  for (std::size_t i = 0; i < size_; i++) {
    for (std::size_t j = 0; j < size_ + 1; j++) {
      file >> matrix[i][j];
      if (file.fail()) {
        file.close();
        size_ = 0;
        return false;
      }
    }
  }
  augmentedMatrix_ = std::move(matrix);
  return true;
}

bool Sle::InputMatrix() {
  std::cin.clear();
    std::cin >> size_;
    if (std::cin.fail() || size_ <= 0) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        return false;
    }
    std::vector<std::vector<double>> matrix(size_, std::vector<double>(size_ + 1));
    for (std::size_t i = 0; i < size_; i++) {
        for (std::size_t j = 0; j < size_ + 1; j++) {
            std::cin >> matrix[i][j];
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                return false;
            }
        }
    }
    augmentedMatrix_ = std::move(matrix);
    return true;
}

std::vector<double> Sle::GetResultDefault() {
    std::vector<double> result;
    GaussDefault gaussDefault(augmentedMatrix_);
    result = gaussDefault.Algorithm();
    return result;
}
std::vector<double> Sle::GetResultAdvanced() {
    std::vector<double> result;
    GaussAdvanced gaussAdvanced(augmentedMatrix_);
    result = gaussAdvanced.Algorithm();
    return result;
}

std::vector<std::vector<double>> Sle::GetAugmentedMatrix() {
  return augmentedMatrix_; 
}
std::size_t Sle::GetSize() {
  return size_;
}


}  // namespace s21