#ifndef A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_DEFAULT_H
#define A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_DEFAULT_H

#include "s21_winograd_optimization.h"

namespace s21 {

class WinogradDefault : public WinogradOptimization {
    public: 
        WinogradDefault(const std::vector<std::vector<double>>& left_matrix, const std::vector<std::vector<double>>& right_matrix);
        void Algorithm();
    private:
        
};
} // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_WINOGRAD_HEADERS_S21_WINOGRAD_DEFAULT_H