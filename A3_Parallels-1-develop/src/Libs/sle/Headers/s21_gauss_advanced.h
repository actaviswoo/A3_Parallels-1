#ifndef A3_PARALLELS_SRC_LIBS_SLE_HEADERS_S21_GAUSS_ADVANCED_H
#define A3_PARALLELS_SRC_LIBS_SLE_HEADERS_S21_GAUSS_ADVANCED_H

#include <vector>
#include <thread>
#include "s21_gauss_optimization.h"

namespace s21 {

class GaussAdvanced : public GaussOptimization {
    public: 
        GaussAdvanced(const std::vector<std::vector<double>>& matrix);
        std::vector<double> Algorithm();
    private:
        void StepNormalize(std::size_t nowIndex);
        void StepSub(std::size_t nowIndex);
        const std::size_t numThreads_ = 4;
        std::vector<std::thread> threads_;
};
} // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_SLE_HEADERS_S21_GAUSS_ADVANCED_H