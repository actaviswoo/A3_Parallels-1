#ifndef A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_PIPELINE_H
#define A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_PIPELINE_H

#include <thread>
#include <condition_variable>
#include <mutex>
#include "s21_winograd_optimization.h"

namespace s21 {

class WinogradPipeline : public WinogradOptimization {
    public:
        WinogradPipeline(const std::vector<std::vector<double>>& left_matrix, const std::vector<std::vector<double>>& right_matrix);
        void Algorithm();
    private:
        std::mutex matrix_mutex_;
        std::mutex row_values_mutex_;
        std::mutex column_values_mutex_;
        std::condition_variable row_values_cv_;
        std::condition_variable column_values_cv_;
        std::condition_variable matrix_cv_;
        bool row_values_ready_;
        bool column_values_ready_;
        bool stage_three_ready_;
        void StageOne();
        void StageTwo();
        void StageThree();
        void StageFour();
};
} // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_PIPELINE_H