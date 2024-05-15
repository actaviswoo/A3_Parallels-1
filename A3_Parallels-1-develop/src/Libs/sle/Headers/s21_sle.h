#ifndef A3_PARALLELS_SRC_LIBS_SLE_HEADERS_S21_SLE_H
#define A3_PARALLELS_SRC_LIBS_SLE_HEADERS_S21_SLE_H

#include "s21_gauss_default.h"
#include "s21_gauss_advanced.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {

class Sle {
    public: 
        Sle() {}
        ~Sle() {}

        bool LoadMatrixFromFile(std::string filename);
        bool InputMatrix();

        std::vector<double> GetResultDefault();
        std::vector<double> GetResultAdvanced();

        std::vector<std::vector<double>> GetAugmentedMatrix();
        std::size_t GetSize();


    private:
        std::vector<std::vector<double>> augmentedMatrix_;
        std::size_t size_ = 0;

};

} // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_SLE_HEADERS_S21_SLE_H