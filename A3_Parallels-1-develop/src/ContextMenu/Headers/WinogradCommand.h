#ifndef A3_PARALLELS_SRC_CONTEXTMENU_WINOGRADCOMMAND_H
#define A3_PARALLELS_SRC_CONTEXTMENU_WINOGRADCOMMAND_H

#include "../../Libs/winograd/Headers/s21_winograd.h"
#include "Command.h"
#include "Timer.h"

namespace s21 {

class WinogradCommand : public Command {
 public:
  WinogradCommand() {}
  ~WinogradCommand() {}

  bool WinogradChoice();
  bool WinogradLoadMatricesFromFile();
  bool WinogradInputMartices();
  bool WinogradInputRandom();
  bool WinogradInputN();
  bool WinogradDefault(std::size_t n);
  bool WinogradClassic(std::size_t number_threads, std::size_t n);
  bool WinogradPipeline(std::size_t n);
  bool WinogradOutput(const std::vector<std::vector<double>>& result, std::size_t n);
  void PrintMatrix(const std::vector<std::vector<double>>& matrix);

  void execute() override {
    try {
      if (!WinogradChoice()) return;
      {
        int count = n_;
        s21::Timer timer("WinogradDefault timer started");
        while (count != 0) {
          if (!WinogradDefault(count)) return;
          count--;
        }
      }
      {
        const std::size_t max_thread = 4 * std::thread::hardware_concurrency();
        std::size_t count_threads = static_cast<std::size_t>(pow(2, 1));
        for (std::size_t i = 1; count_threads <= max_thread; count_threads = static_cast<std::size_t>(pow(2, ++i))) {
          s21::Timer timer("WinogradClassic timer started for " + std::to_string(count_threads) + " threads");
          int count = n_;
          while (count != 0) {
            if (!WinogradClassic(count_threads, count)) return;
            count--;
          }
        }
      }
      {
        int count = n_;
        s21::Timer timer("WinogradPipeline timer started");
        while (count != 0) {
          if (!WinogradPipeline(count)) return;
          count--;
        }
      }
    } catch (const std::exception& e) {
      ConsoleOutput("matrix empty", RED);
    }
  }

 private:
  Winograd winograd_;
  int n_;
  std::string menu_ =
      ""
      "0.Load matrices from file\n"
      "1.Input matrices\n"
      "2.Random matrices(You need to input the sizes of matrices)\n"
      "3.Back";
};

}  // namespace s21

#endif  // A3_PARALLELS_SRC_CONTEXTMENU_WINOGRADCOMMAND_H
