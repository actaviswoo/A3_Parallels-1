#include "../Headers/s21_winograd_default.h"

namespace s21 {

WinogradDefault::WinogradDefault(const std::vector<std::vector<double>>& left_matrix, const std::vector<std::vector<double>>& right_matrix) : WinogradOptimization(left_matrix, right_matrix) {}

void WinogradDefault::Algorithm() {
    if (left_matrix_[0].size() == 1) {
        Mul();
        return;
    }
    RowAndColumnValuesCalc(0, left_matrix_.size(), 0, right_matrix_[0].size());
    ResultMatrixCalc(0, left_matrix_.size());
}

} // namespace s21
