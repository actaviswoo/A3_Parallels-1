#include "../Headers/s21_winograd_classic.h"

namespace s21 {

WinogradClassic::WinogradClassic(const std::vector<std::vector<double>>& left_matrix, const std::vector<std::vector<double>>& right_matrix) : WinogradOptimization(left_matrix, right_matrix) {}

void WinogradClassic::Algorithm(size_t threads_number) {
    if (left_matrix_[0].size() == 1) {
        Mul();
        return;
    }
    std::vector<std::thread> threads(threads_number);
    for (std::size_t i = 0; i < threads_number; ++i)
        threads[i] = std::thread(&s21::WinogradClassic::RowAndColumnValuesCalc, this, i * left_matrix_.size() / threads_number, (i + 1) * left_matrix_.size() / threads_number, i * right_matrix_[0].size() / threads_number, (i + 1) * right_matrix_[0].size() / threads_number);
    for (std::size_t i = 0; i < threads_number; ++i)
        threads[i].join();
    for (std::size_t i = 0; i < threads_number; ++i)
        threads[i] = std::thread(&s21::WinogradClassic::ResultMatrixCalc, this, i * left_matrix_.size() / threads_number, (i + 1) * left_matrix_.size() / threads_number);
    for (std::size_t i = 0; i < threads_number; ++i)
        threads[i].join();
}

} // namespace s21 
