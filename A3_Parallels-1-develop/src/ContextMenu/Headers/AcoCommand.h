#ifndef A3_PARALLELS_SRC_CONTEXTMENU_ACOCOMMAND_H
#define A3_PARALLELS_SRC_CONTEXTMENU_ACOCOMMAND_H

#include "../../Libs/aco/Headers/s21_aco.h"
#include "Command.h"
#include "Timer.h"

namespace s21 {

class AcoCommand : public Command {
 public:
  AcoCommand() {}
  ~AcoCommand() {}

  bool AcoChoice();
  bool AcoInputMartix();
  bool AcoLoadMatrixFromFile();
  bool AcoInputN();
  bool AcoDefault();
  bool AcoAdvanced();
  bool AcoOutput(TsmResult& result);

  void execute() override {
    try {
      if (!AcoChoice()) return;
      {
        int count = n_;
        s21::Timer timer("AcoDefault timer started");
        while (count != 0) {
          if (!AcoDefault()) return;
          count--;
        }
      }
      {
        int count = n_;
        s21::Timer timer("AcoAdvanced timer started");
        while (count != 0) {
          if (!AcoAdvanced()) return;
          count--;
        }
      }

    } catch (const std::exception& e) {
      ConsoleOutput("matrix empty", RED);
    }
  }

 private:
  Aco aco_;
  int n_;
  std::string menu_ =
      ""
      "0.Load adjacency matrix from file\n"
      "1.Input adjacency matrix\n"
      "2.Back";
};

}  // namespace s21

#endif  // A3_PARALLELS_SRC_CONTEXTMENU_COMMAND_H