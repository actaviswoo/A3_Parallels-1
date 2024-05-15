#ifndef A3_PARALLELS_SRC_LIBS_ACO_HEADERS_S21_ANT_ALGORITHM_ADVANCED_H
#define A3_PARALLELS_SRC_LIBS_ACO_HEADERS_S21_ANT_ALGORITHM_ADVANCED_H

#include "s21_ant_algorithm_optimization.h"
#include <thread>
#include <mutex>
namespace s21 {

class AntAlgorithmAdvanced : public AntAlgorithmOptimization  {
    public:
    AntAlgorithmAdvanced(const std::vector<std::vector<int>>& matrix);
    TsmResult Algorithm();
    private:
    void CheckAnt(Ant& ant, TsmResult& result, std::size_t* count, std::vector<std::vector<double>> localPheromones);

    private:
    std::mutex mutex_;
    const std::size_t numThreads_ = 4;
    std::vector<std::thread> threads_;
};


}  // namespace s21

#endif  // A3_PARALLELS_SRC_LIBS_ACO_HEADERS_S21_ANT_ALGORITHM_ADVANCED_H
