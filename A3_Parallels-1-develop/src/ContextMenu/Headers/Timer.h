#ifndef A3_PARALLELS_SRC_CONTEXTMENU_TIMER_H
#define A3_PARALLELS_SRC_CONTEXTMENU_TIMER_H

#include <chrono>
#include <string>

#include "Command.h"

namespace s21 {
class Timer {
 public:
  Timer() = delete;
  Timer(const std::string& message);
  ~Timer();

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};

}  // namespace s21

#endif  // A3_PARALLELS_SRC_CONTEXTMENU_TIMER_H