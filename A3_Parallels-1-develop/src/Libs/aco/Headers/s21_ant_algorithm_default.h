#ifndef A3_PARALLELS_SRC_LIBS_ACO_HEADERS_S21_ANT_ALGORITHM_DEFAULT_H
#define A3_PARALLELS_SRC_LIBS_ACO_HEADERS_S21_ANT_ALGORITHM_DEFAULT_H

#include "s21_ant_algorithm_optimization.h"
namespace s21 {

class AntAlgorithmDefault : public AntAlgorithmOptimization  {
    public:
    AntAlgorithmDefault(const std::vector<std::vector<int>>& matrix);
    TsmResult Algorithm();
    private:
    void CheckAnt(Ant& ant, TsmResult& result, std::size_t* count, std::vector<std::vector<double>> localPheromones);
};


}  // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_ACO_HEADERS_S21_ANT_ALGORITHM_DEFAULT_H
