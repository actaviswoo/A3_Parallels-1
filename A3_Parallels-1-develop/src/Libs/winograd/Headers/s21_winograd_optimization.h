#ifndef A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_OPTIMIZATION_H
#define A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_OPTIMIZATION_H

#include <vector>

namespace s21 {

class WinogradOptimization {
    public: 
        WinogradOptimization() = delete;
        WinogradOptimization(const std::vector<std::vector<double>>& left_matrix, const std::vector<std::vector<double>>& right_matrix);
        ~WinogradOptimization() {}
        const std::vector<std::vector<double>>& GetResult();
    protected:
        std::vector<std::vector<double>> left_matrix_;
        std::vector<std::vector<double>> right_matrix_;
        std::vector<std::vector<double>> result_matrix_;
        std::vector<double> row_values_;
        std::vector<double> column_values_;
        std::size_t lenght_;

        void Mul();
        void RowValuesCalc(std::size_t start, std::size_t end);
        void ColumnValuesCalc(std::size_t start, std::size_t end);
        void RowAndColumnValuesCalc(std::size_t start_r, std::size_t end_r, std::size_t start_c, std::size_t end_c);
        void ResultMatrixCalc(std::size_t start, std::size_t end);
};
} // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_OPTIMIZATION_H
