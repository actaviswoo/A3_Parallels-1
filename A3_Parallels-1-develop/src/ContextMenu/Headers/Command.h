#ifndef A3_PARALLELS_SRC_CONTEXTMENU_COMMAND_H
#define A3_PARALLELS_SRC_CONTEXTMENU_COMMAND_H

#include <iostream>

namespace s21 {

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string BLACK = "\033[30m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string PURPLE = "\033[35m";
const std::string WHITE = "\033[37m";

void ConsoleOutput(const std::string& message, const std::string& color);

class Parallels;

class Command {
 public:
  virtual ~Command() {}
  virtual void execute() = 0;
};

}  // namespace s21

#endif  // A3_PARALLELS_SRC_CONTEXTMENU_COMMAND_H