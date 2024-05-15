#ifndef A3_PARALLELS_SRC_TESTS_S21_TEST_H
#define A3_PARALLELS_SRC_TESTS_S21_TEST_H

#include <vector>
#include <iostream>

const std::vector<std::vector<int>> acoMatrix = {
    {0   , 29,  20,  21,  16,  31,  100, 12,  4  , 31,  18},
    {29  , 0 ,  15,  29,  28,  40,  72 , 21,  29 , 41,  12},
    {20  , 15,  0 ,  15,  14,  25,  81 , 9 ,  23 , 27,  13},
    {21  , 29,  15,  0 ,  4 ,  12,  92 , 12,  25 , 13,  25},
    {16  , 28,  14,  4 ,  0 ,  16,  94 , 9 ,  20 , 16,  22},
    {31  , 40,  25,  12,  16,  0 ,  95 , 24,  36 , 3 ,  37},
    {100 , 72,  81,  92,  94,  95,  0  , 90,  101, 99,  84},
    {12  , 21,  9 ,  12,  9 ,  24,  90 , 0 ,  15 , 25,  13},
    {4   , 29,  23,  25,  20,  36,  101, 15,  0  , 35,  18},
    {31  , 41,  27,  13,  16,  3 ,  99 , 25,  35 , 0 ,  35},
    {18  , 12,  13,  25,  22,  37,  84 , 13,  18 , 35,  0 }
};
const int acoMatrixSize = 11;
const std::vector<std::vector<double>> sleMatrix = {
    {1, 2, 3, 4, 5, 6, 7},
    {1, 2, 3, 4, 5, 6, 7},
    {1, 2, 3, 4, 5, 6, 7},
    {1, 2, 3, 4, 5, 6, 7},
    {1, 2, 3, 4, 5, 6, 7},
    {1, 2, 3, 4, 5, 6, 7},
};
const int sleMatrixSize = 6;
const std::vector<std::vector<double>> winogradLeftMatrix = {
    {3, 5, 1},
    {7, 4, 2},
};
const std::vector<std::vector<double>> winogradRightMatrix = {
    {2, 4, 3},
    {5, 1, 6},
    {1, 8, 3},
};

const std::vector<int> acoResult1 = {0, 1, 2, 3, 4, 0};
const std::vector<int> acoResult2 = {1, 2, 3, 4, 0, 1};
const int acoDistace = 15;

const std::vector<double> sleResult = {1, 1, 1};

const std::vector<std::vector<double>> winogradResult = {
    {1720.392, 190.179093, 287.5807,	508.230965,	-266.3795,	1936.5893455,	-248.2745,	-80.053,	111.94898},
    {7536.794736,	453.480046,	4153.7141696,	6355.543282,	-392.30924,	6590.793465,	4449.457768,	-461.684464,	7844.43664064},
    {-508.596092,	-216.1810454317,	290.652706,	396.9436554,	429.8298116,	-2889.50544922395,	1053.775386,	231.3087056,	1122.0312684},
    {2488.06,	-1156.646616,	30.762,	2842.68424,	7305.048,	-58348.191396,	3524.428,	7167.4,	740.642},
    {8480.3104,	-438.42457006,	2740.1014,	6292.997404,	4911.99588,	-37707.23964861,	4941.2521,	5014.44028,	5290.63518},
    {4957.9626,	262.03016401,	1673.5127,	3061.229588,	516.28652,	-3265.624657065,	1481.3888,	728.24872,	2618.73782},
};

const std::string acoMatrixPath = "Tests/Resources/aco_matrix.txt";
const std::string doesntExistPath = "Tests/Resources/doesntExist.txt";
const std::string emptyPath = "Tests/Resources/empty.txt";
const std::string incorrectPath = "Tests/Resources/incorrect.txt";
const std::string acoPath = "Tests/Resources/aco_test.txt";
const std::string sleMatrixPath = "Tests/Resources/sle_matrix.txt";
const std::string slePath = "Tests/Resources/sle_test.txt";
const std::string winogradMatricesPath = "Tests/Resources/winograd_matrices.txt";
const std::string winogradPath = "Tests/Resources/winograd_test.txt";

const double eps = 0.0000001;
template<typename T>
bool AreMatricesEqual(const std::vector<std::vector<T>>& matrix1,
                      const std::vector<std::vector<T>>& matrix2) {
  if (matrix1.size() != matrix2.size()) {
    return false;
  }
  for (size_t i = 0; i < matrix1.size(); ++i) {
    if (matrix1[i].size() != matrix2[i].size()) {
      return false;
    }

    for (size_t j = 0; j < matrix1[i].size(); ++j) {
      if (std::abs(matrix1[i][j] - matrix2[i][j]) >= eps) {
        return false;
      }
    }
  }
  return true;
}

template<typename T>
bool AreVectorsEqual(const std::vector<T>& vec1,
                     const std::vector<T>& vec2) {
  if (vec1.size() != vec2.size()) {
    return false;
  }
  for (size_t i = 0; i < vec1.size(); ++i) {
    if (vec1[i] != vec2[i]) {
      return false;
    }
  }
  return true;
}

#endif //A3_PARALLELS_SRC_TESTS_S21_TEST_H

