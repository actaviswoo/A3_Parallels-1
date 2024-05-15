#include <chrono>
#include <iostream>
#include <memory>

#include "AcoCommand.h"
#include "SleCommand.h"
#include "WinogradCommand.h"

namespace s21 {

class Parallels {
 public:
  void start();

 private:
  std::string menu_ =
      ""
      "0.Ant colony optimization algorithm (ACO)\n"
      "1.Solving systems of linear equations (SLE)\n"
      "2.Winograd algorithm\n"
      "11.exit\n";
};

}  // namespace s21