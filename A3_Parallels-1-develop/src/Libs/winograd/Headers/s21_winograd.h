#ifndef A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_H
#define A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_H

#include "s21_winograd_default.h"
#include "s21_winograd_classic.h"
#include "s21_winograd_pipeline.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <random>

namespace s21 {

class Winograd {
    public:
        Winograd() {}
        ~Winograd() {}
        bool LoadMatricesFromFile(const std::string& filename);
        bool ReadMatrix(std::ifstream& file, std::vector<std::vector<double>>& matrix, size_t& rows, size_t& cols);
        bool InputMatricesFromConsole();
        bool ReadMatrix(std::vector<std::vector<double>>& matrix, size_t& rows, size_t& cols, bool random);
        bool InputMatricesRandom();
        const std::vector<std::vector<double>>& GetLeftMatrix();
        const std::vector<std::vector<double>>& GetRightMatrix();
        std::vector<std::vector<double>> GetResultDefault();
        std::vector<std::vector<double>> GetResultClassic(size_t threads_number);
        std::vector<std::vector<double>> GetResultPipeline();
    private:
        std::vector<std::vector<double>> left_matrix_;
        std::vector<std::vector<double>> right_matrix_;
        size_t left_matrix_rows_ = 0;
        size_t left_matrix_cols_ = 0;
        size_t right_matrix_rows_ = 0;
        size_t right_matrix_cols_ = 0;
};

} // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_H
