#ifndef A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_CLASSIC_H
#define A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_CLASSIC_H

#include <thread>
#include "s21_winograd_optimization.h"

namespace s21 {

class WinogradClassic : public WinogradOptimization {
    public: 
        WinogradClassic(const std::vector<std::vector<double>>& left_matrix, const std::vector<std::vector<double>>& right_matrix);
        void Algorithm(size_t threads_number);
    private:
        
};
} // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_CLASSIC_H