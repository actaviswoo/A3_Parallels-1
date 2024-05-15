#ifndef A3_PARALLELS_SRC_CONTEXTMENU_SLECOMMAND_H
#define A3_PARALLELS_SRC_CONTEXTMENU_SLECOMMAND_H

#include "../../Libs/sle/Headers/s21_sle.h"
#include "Command.h"
#include "Timer.h"

namespace s21 {

class SleCommand : public Command {
 public:
  SleCommand() {}
  ~SleCommand() {}

  bool SleChoice();
  bool SleInputMartix();
  bool SleLoadMatrixFromFile();
  bool SleInputN();
  bool SleDefault();
  bool SleAdvanced();
  bool SleOutput(std::vector<double>& result);

  void execute() override {
    try {
      if (!SleChoice()) return;
      {
        int count = n_;
        s21::Timer timer("SleDefault timer started");
        while (count != 0) {
          if (!SleDefault()) return;
          count--;
        }
      }
      {
        int count = n_;
        s21::Timer timer("SleAdvanced timer started");
        while (count != 0) {
          if (!SleAdvanced()) return;
          count--;
        }
      }

    } catch (const std::exception& e) {
      ConsoleOutput("matrix empty", RED);
    }
  }

 private:
  Sle sle_;
  int n_;
  std::string menu_ =
      ""
      "0.Load augmented matrix from file\n"
      "1.Input augmented matrix\n"
      "2.Back";
};

}  // namespace s21

#endif  // A3_PARALLELS_SRC_CONTEXTMENU_SLECOMMAND_H