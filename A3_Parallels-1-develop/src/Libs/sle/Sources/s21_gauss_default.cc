#include "../Headers/s21_gauss_default.h"

namespace s21 {

GaussDefault::GaussDefault(const std::vector<std::vector<double>>& augmentedMatrix) : GaussOptimization(augmentedMatrix) {}

std::vector<double> GaussDefault::Algorithm() {
    for (std::size_t nowIndex = 0; nowIndex < size_; nowIndex++) {
      std::size_t maxIndex = StepFindMaxIndex(nowIndex);
      if (std::abs(matrix_[maxIndex][nowIndex]) < eps_) return {};
      if (nowIndex != maxIndex) StepSwapCols(nowIndex, maxIndex);
      StepNormalize(nowIndex);
      StepSub(nowIndex);
    }
    return StepBackSubstitution();
}


void GaussDefault::StepNormalize(std::size_t nowIndex) {
    for (std::size_t i = nowIndex; i < size_; i++) {
      double div = matrix_[i][nowIndex];
      if (std::abs(div) < eps_) continue;
      for (std::size_t j = nowIndex; j < size_; j++) {
        matrix_[i][j] /= div;
      }
      constantTerm_[i] /= div;
    }
}

void GaussDefault::StepSub(std::size_t nowIndex) {
    for (std::size_t i = nowIndex + 1; i < size_; ++i) {
      for (std::size_t j = nowIndex; j < size_; j++) {
        matrix_[i][j] -= matrix_[nowIndex][j];
      }
      constantTerm_[i] -= constantTerm_[nowIndex];
    }
}


} // namespace s21
