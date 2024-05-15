#include "../Headers/Timer.h"

namespace s21 {
Timer::Timer(const std::string& message) {
  ConsoleOutput(message, GREEN);
  start_ = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - start_);
  ConsoleOutput("Total time: " + std::to_string(duration.count()) + " ms",
                GREEN);
}

}  // namespace s21