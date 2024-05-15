#include "../Headers/s21_winograd_pipeline.h"

namespace s21 {

WinogradPipeline::WinogradPipeline(const std::vector<std::vector<double>>& left_matrix, const std::vector<std::vector<double>>& right_matrix) : WinogradOptimization(left_matrix, right_matrix) {}

void WinogradPipeline::Algorithm() {
    if (left_matrix_[0].size() == 1) {
        Mul();
        return;
    }
    row_values_ready_ = false;
    column_values_ready_ = false;
    stage_three_ready_ = false;
    std::thread t1(&WinogradPipeline::StageOne, this);
    std::thread t2(&WinogradPipeline::StageTwo, this);
    std::thread t3(&WinogradPipeline::StageThree, this);
    std::thread t4(&WinogradPipeline::StageFour, this);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

void WinogradPipeline::StageOne() {
    row_values_mutex_.lock();
    RowValuesCalc(0, left_matrix_.size());
    row_values_ready_ = true;
    row_values_mutex_.unlock();
    row_values_cv_.notify_all();
}

void WinogradPipeline::StageTwo() {
    column_values_mutex_.lock();
    ColumnValuesCalc(0, right_matrix_[0].size());
    column_values_ready_ = true;
    column_values_mutex_.unlock();
    column_values_cv_.notify_all();
}

void WinogradPipeline::StageThree() {
    matrix_mutex_.lock();
    size_t left_matrix_c = left_matrix_[0].size();
    if (left_matrix_[0].size() % 2 != 0) {
        for (size_t i = 0; i < left_matrix_.size(); ++i) {
            for (size_t j = 0; j < result_matrix_[0].size(); ++j)
                result_matrix_[i][j] += left_matrix_[i][left_matrix_c - 1] * right_matrix_[left_matrix_c - 1][j];;
        }
    }
    stage_three_ready_ = true;
    matrix_mutex_.unlock();
    matrix_cv_.notify_all();
}

void WinogradPipeline::StageFour() {
    std::unique_lock<std::mutex> ul1(row_values_mutex_);
    std::unique_lock<std::mutex> ul2(column_values_mutex_);
    std::unique_lock<std::mutex> ul3(matrix_mutex_);
    row_values_cv_.wait(ul1, [&] { return row_values_ready_; });
    column_values_cv_.wait(ul2, [&] { return column_values_ready_; });
    matrix_cv_.wait(ul3, [&] { return stage_three_ready_; });
    for (size_t i = 0; i < left_matrix_.size(); ++i) {
        for (size_t j = 0; j < result_matrix_[0].size(); ++j) {
            double value = -row_values_[i] - column_values_[j];
            for (size_t k = 0; k < lenght_; ++k)
                value += (left_matrix_[i][2 * k] + right_matrix_[2 * k + 1][j]) * (left_matrix_[i][2 * k + 1] + right_matrix_[2 * k][j]);
            result_matrix_[i][j] += value;
        }
    }
}

} // namespace s21 
