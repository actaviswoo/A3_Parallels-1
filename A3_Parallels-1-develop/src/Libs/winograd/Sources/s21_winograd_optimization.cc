#include "../Headers/s21_winograd_optimization.h"

namespace s21 {

WinogradOptimization::WinogradOptimization(const std::vector<std::vector<double>>& left_matrix, const std::vector<std::vector<double>>& right_matrix) {
    left_matrix_ = left_matrix;
    right_matrix_ = right_matrix;
    result_matrix_.resize(left_matrix_.size());
    for (std::size_t i = 0; i < left_matrix_.size(); ++i)
        result_matrix_[i].resize(right_matrix_[0].size());
    row_values_.resize(left_matrix_.size());
    column_values_.resize(right_matrix_[0].size());
    lenght_ = left_matrix_[0].size() / 2;
}

const std::vector<std::vector<double>>& WinogradOptimization::GetResult() {
    return result_matrix_;
}

void WinogradOptimization::Mul() {
    for (std::size_t i = 0; i < left_matrix_.size(); ++i) {
        for (std::size_t j = 0; j < right_matrix_[0].size(); ++j) {
            double sum = 0;
            for (std::size_t k = 0; k < left_matrix_[0].size(); ++k)
                sum += left_matrix_[i][k] * right_matrix_[k][j];
            result_matrix_[i][j] = sum;
        }
    }
}

void WinogradOptimization::RowValuesCalc(std::size_t start, std::size_t end) {
    for (std::size_t i = start; i < end; ++i) {
        row_values_[i] = left_matrix_[i][0] * left_matrix_[i][1];
        for (std::size_t j = 1; j < lenght_; ++j)
            row_values_[i] += left_matrix_[i][2 * j] * left_matrix_[i][2 * j + 1];
    }
}

void WinogradOptimization::ColumnValuesCalc(std::size_t start, std::size_t end) {
    for (std::size_t i = start; i < end; ++i) {
        column_values_[i] = right_matrix_[0][i] * right_matrix_[1][i];
        for (std::size_t j = 1; j < lenght_; ++j)
            column_values_[i] += right_matrix_[2 * j][i] * right_matrix_[2 * j + 1][i];
    }
}

void WinogradOptimization::RowAndColumnValuesCalc(std::size_t start_r, std::size_t end_r, std::size_t start_c, std::size_t end_c) {
    RowValuesCalc(start_r, end_r);
    ColumnValuesCalc(start_c, end_c);
}

void WinogradOptimization::ResultMatrixCalc(std::size_t start, std::size_t end) {
    std::size_t left_matrix_cols = left_matrix_[0].size();
    for (std::size_t i = start; i < end; ++i) {
        for (std::size_t j = 0; j < right_matrix_[0].size(); ++j) {
            result_matrix_[i][j] += -row_values_[i] - column_values_[j];
            for (std::size_t k = 0; k < lenght_; ++k)
                result_matrix_[i][j] += (left_matrix_[i][2 * k] + right_matrix_[2 * k + 1][j]) * (left_matrix_[i][2 * k + 1] + right_matrix_[2 * k][j]);
            if (left_matrix_cols % 2 != 0)
                result_matrix_[i][j] += left_matrix_[i][left_matrix_cols - 1] * right_matrix_[left_matrix_cols - 1][j];
        }
    }
}

} // namespace s21
