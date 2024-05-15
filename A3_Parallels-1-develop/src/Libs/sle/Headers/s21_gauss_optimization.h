#ifndef A3_PARALLELS_SRC_LIBS_SLE_HEADERS_S21_GAUSS_OPTIMIZATION_H
#define A3_PARALLELS_SRC_LIBS_SLE_HEADERS_S21_GAUSS_OPTIMIZATION_H

#include <vector>
#include <algorithm>
#include <cmath>
namespace s21 {

class GaussOptimization {
    public: 
        GaussOptimization() = delete;
        GaussOptimization(const std::vector<std::vector<double>>& matrix);
        ~GaussOptimization() {}
    protected:
        const std::size_t size_;
        const double eps_ = 1e-12;
        std::vector<std::vector<double>> matrix_;
        std::vector<double> constantTerm_;
        void Init(std::vector<std::vector<double>>& matrix, std::vector<double>& constantTerm, const std::vector<std::vector<double>>& augmentedMatrix);
        double StepFindMaxIndex(std::size_t nowIndex);
        void StepSwapCols(std::size_t nowIndex, std::size_t maxIndex);
        std::vector<double> StepBackSubstitution();

};
} // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_SLE_HEADERS_S21_GAUSS_OPTIMIZATION_H