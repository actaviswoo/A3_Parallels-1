#ifndef A3_PARALLELS_SRC_LIBS_SLE_HEADERS_S21_GAUSS_DEFAULT_H
#define A3_PARALLELS_SRC_LIBS_SLE_HEADERS_S21_GAUSS_DEFAULT_H

#include <vector>
#include "s21_gauss_optimization.h"
namespace s21 {

class GaussDefault : public GaussOptimization {
    public: 
        GaussDefault(const std::vector<std::vector<double>>& matrix);
        std::vector<double> Algorithm();
    private:
        void StepNormalize(std::size_t nowIndex);
        void StepSub(std::size_t nowIndex);

};
} // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_SLE_HEADERS_S21_GAUSS_DEFAULT_H