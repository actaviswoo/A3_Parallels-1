#include "../Headers/SleCommand.h"

namespace s21 {

bool SleCommand::SleChoice() {
  int choice = 0;
  do {
    ConsoleOutput(menu_, PURPLE);
    ConsoleOutput("make your choice", YELLOW);
    std::cout << "--> ";
    std::cin >> choice;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(32767, '\n');
    } else if (choice == 0) {
      std::cin.ignore(32767, '\n');
      if (SleLoadMatrixFromFile()) return true;
    } else if (choice == 1) {
      std::cin.ignore(32767, '\n');
      if (SleInputMartix()) return true;
    }
  } while (choice != 2);
  return false;
}

bool SleCommand::SleInputMartix() {
  ConsoleOutput("format \n 3\n-1.2 2.1 3.0 1.0\n2.1 0.0 -4 8.2\n-4 3.1 4.5 0.1", BLUE);
  ConsoleOutput("input martix", YELLOW);
  std::cout << "--> ";
  if(!sle_.InputMatrix()) {
    ConsoleOutput("invalid input", RED);
    return false;
  }
  ConsoleOutput("matrix inputed", GREEN);
  if (!SleInputN()) {
    ConsoleOutput("invalid input", RED);
    return false;
  }
  return true; 
}

bool SleCommand::SleLoadMatrixFromFile() {
  std::istream& input = std::cin;
  std::string filename;
  ConsoleOutput("input filename", YELLOW);
  std::cout << "--> ";
  input >> filename;
  if (!sle_.LoadMatrixFromFile(filename)) {
    ConsoleOutput("cant't load", RED);
    return false;
  }
  ConsoleOutput("matrix loaded", GREEN);
  if (!SleInputN()) {
    ConsoleOutput("invalid input", RED);
    return false;
  }
  return true;
}

bool SleCommand::SleInputN() {
  std::istream& input = std::cin;
  ConsoleOutput("input count of iteration", YELLOW);
  std::cout << "--> ";
  if (!(input >> n_)) {
    return false;
  }
  return true;
}

bool SleCommand::SleDefault() {
  std::vector<double> result = sle_.GetResultDefault();
  return SleOutput(result);
}

bool SleCommand::SleAdvanced() {
  std::vector<double> result = sle_.GetResultAdvanced();
  return SleOutput(result);
}

bool SleCommand::SleOutput(std::vector<double>& result) {
  if (result.empty()) {
    ConsoleOutput("solution not found", RED);
    return false;
  }
  std::cout << GREEN << "solution\n[ ";
  for (std::size_t i = 0; i < result.size(); i++) {
    std::cout << result[i] << " ";
  }
  std::cout << "]\n" << RESET << std::endl;
  return true;
}

}  // namespace s21
