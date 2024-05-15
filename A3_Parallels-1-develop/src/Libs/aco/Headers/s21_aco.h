#ifndef A3_PARALLELS_SRC_LIBS_ACO_HEADERS_S21_ACO_H
#define A3_PARALLELS_SRC_LIBS_ACO_HEADERS_S21_ACO_H

#include "s21_ant_algorithm_default.h"
#include "s21_ant_algorithm_advanced.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace s21 {

class Aco {
    public:
     Aco() {}
     ~Aco() {}
    bool LoadMatrixFromFile(std::string filename);
    bool InputMatrix();
    
    TsmResult GetResultDefault();
    TsmResult GetResultAdvanced();

    std::vector<std::vector<int>> GetAdjacencyMatrix();
    std::size_t GetSize();

    protected:
    std::vector<std::vector<int>> adjacencyMatrix_;
    std::size_t size_ = 0;
};


}  // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_ACO_HEADERS_S21_ACO_H