#include "../Headers/s21_gauss_advanced.h"

namespace s21 {

GaussAdvanced::GaussAdvanced(const std::vector<std::vector<double>>& augmentedMatrix) : GaussOptimization(augmentedMatrix) {}

std::vector<double> GaussAdvanced::Algorithm() {
    for (std::size_t nowIndex = 0; nowIndex < size_; nowIndex++) {
      std::size_t maxIndex = StepFindMaxIndex(nowIndex);
      if (std::abs(matrix_[maxIndex][nowIndex]) < eps_) return {};
      if (nowIndex != maxIndex) StepSwapCols(nowIndex, maxIndex);
      StepNormalize(nowIndex);
      StepSub(nowIndex);
    }
    return StepBackSubstitution();
}

void GaussAdvanced::StepNormalize(std::size_t nowIndex) {
      double div = matrix_[nowIndex][nowIndex];
      if (std::abs(div) < eps_) return;
      for (std::size_t j = nowIndex; j < size_; j++) {
        matrix_[nowIndex][j] /= div;
      }
      constantTerm_[nowIndex] /= div;
}

void GaussAdvanced::StepSub(std::size_t nowIndex) {
    for (std::size_t iThread = 0; iThread < numThreads_; iThread++) {
        threads_.emplace_back([=]() {
            std::size_t rangeThreadSize = (size_ - nowIndex - 1) / numThreads_;
            std::size_t startIndex = iThread * rangeThreadSize + nowIndex + 1;
            std::size_t endIndex = (iThread == numThreads_ - 1) ? size_ : (startIndex + rangeThreadSize);
            for (std::size_t i = startIndex; i < endIndex; ++i) {
                double div = matrix_[i][nowIndex];
                if (std::abs(div) < eps_) continue;
                for (std::size_t j = nowIndex; j < size_; j++) {
                    matrix_[i][j] = matrix_[i][j] / div - matrix_[nowIndex][j];
                }
                constantTerm_[i] = constantTerm_[i] / div - constantTerm_[nowIndex];
            }
        });
    }
    for (auto& thread : threads_) thread.join();
    threads_.clear();
}

} // namespace s21 
