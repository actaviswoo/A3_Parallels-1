#include "../Headers/s21_winograd.h"

namespace s21 {

bool Winograd::LoadMatricesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open() || !ReadMatrix(file, left_matrix_, left_matrix_rows_, left_matrix_cols_) || !ReadMatrix(file, right_matrix_, right_matrix_rows_, right_matrix_cols_) || left_matrix_cols_ != right_matrix_rows_) {
        file.close();
        left_matrix_.clear();
        right_matrix_.clear();
        return false;
    }
    file.close();
    return true;
}

bool Winograd::ReadMatrix(std::ifstream& file, std::vector<std::vector<double>>& matrix, size_t& rows, size_t& cols) {
    std::string line;
    if (!std::getline(file, line))
        return false;
    std::istringstream dims(line);
    if (!(dims >> rows >> cols) || rows <= 0 || cols <= 0)
        return false;
    matrix.resize(rows);
    for (size_t i = 0; i < rows; ++i)
        matrix[i].resize(cols);
    size_t currentRow = 0;
    while (currentRow < rows && getline(file, line)) {
        std::istringstream iss(line);
        for (size_t col = 0; col < cols; ++col) {
            if (!(iss >> matrix[currentRow][col]))
                return false;
        }
        ++currentRow;
    }
    return true;
}

bool Winograd::InputMatricesFromConsole() {
    if (!ReadMatrix(left_matrix_, left_matrix_rows_, left_matrix_cols_, false) || !ReadMatrix(right_matrix_, right_matrix_rows_, right_matrix_cols_, false) || left_matrix_cols_ != right_matrix_rows_)
        return false;
    return true;
}

bool Winograd::ReadMatrix(std::vector<std::vector<double>>& matrix, size_t& rows, size_t& cols, bool random) {
    std::string line;
    if (!std::getline(std::cin, line))
        return false;
    std::istringstream dims(line);
    if (!(dims >> rows >> cols) || rows <= 0 || cols <= 0)
        return false;
    matrix.resize(rows);
    for (size_t i = 0; i < rows; ++i)
        matrix[i].resize(cols);
    size_t currentRow = 0;
    if (random) {
        std::random_device rd;
        std::mt19937 mersenne(rd());
        for (; currentRow < rows; ++currentRow) {
            for (size_t col = 0; col < cols; ++col)
                matrix[currentRow][col] = mersenne() % 100;
        }
    } else {
        while (currentRow < rows && getline(std::cin, line)) {
            std::istringstream iss(line);
            for (size_t col = 0; col < cols; ++col) {
                if (!(iss >> matrix[currentRow][col]))
                    return false;
            }
            ++currentRow;
        }
    }
    return true;
}

bool Winograd::InputMatricesRandom() {
    if (!ReadMatrix(left_matrix_, left_matrix_rows_, left_matrix_cols_, true) || !ReadMatrix(right_matrix_, right_matrix_rows_, right_matrix_cols_, true) || left_matrix_cols_ != right_matrix_rows_)
        return false;
    return true;
}

const std::vector<std::vector<double>>& Winograd::GetLeftMatrix() {
    return left_matrix_;
}

const std::vector<std::vector<double>>& Winograd::GetRightMatrix() {
    return right_matrix_;
}

std::vector<std::vector<double>> Winograd::GetResultDefault() {
    WinogradDefault winogradDefault(left_matrix_, right_matrix_);
    winogradDefault.Algorithm();
    return winogradDefault.GetResult();
}

std::vector<std::vector<double>> Winograd::GetResultClassic(size_t threads_number) {
    WinogradClassic winogradClassic(left_matrix_, right_matrix_);
    winogradClassic.Algorithm(threads_number);
    return winogradClassic.GetResult();
}

std::vector<std::vector<double>> Winograd::GetResultPipeline() {
    WinogradPipeline winogradPipeline(left_matrix_, right_matrix_);
    winogradPipeline.Algorithm();
    return winogradPipeline.GetResult();
}

}  // namespace s21