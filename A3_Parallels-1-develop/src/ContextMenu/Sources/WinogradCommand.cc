#include "../Headers/WinogradCommand.h"

namespace s21 {

bool WinogradCommand::WinogradChoice() {
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
      if (WinogradLoadMatricesFromFile()) return true;
    } else if (choice == 1) {
      std::cin.ignore(32767, '\n');
      if (WinogradInputMartices()) return true;
    } else if (choice == 2) {
      std::cin.ignore(32767, '\n');
      if (WinogradInputRandom()) return true;
    }
  } while (choice != 3);
  return false;
}

bool WinogradCommand::WinogradLoadMatricesFromFile() {
  std::istream& input = std::cin;
  std::string filename;
  ConsoleOutput("input filename", YELLOW);
  std::cout << "--> ";
  input >> filename;
  if (!winograd_.LoadMatricesFromFile(filename)) {
    ConsoleOutput("cant't load", RED);
    return false;
  }
  ConsoleOutput("matrices loaded", GREEN);
  if (!WinogradInputN()) {
    ConsoleOutput("invalid input", RED);
    return false;
  }
  return true;
}

bool WinogradCommand::WinogradInputMartices() {
  ConsoleOutput("format \n2 3\n1.2 2.1 3.0\n2.1 0.0 -4\n3 3\n3 5.7 -2.4\n12.1 0.3 5.5\n2.1 4.4 6\n", BLUE);
  ConsoleOutput("input martices", YELLOW);
  std::cout << "--> ";
  if(!winograd_.InputMatricesFromConsole()) {
    ConsoleOutput("invalid input", RED);
    return false;
  }
  ConsoleOutput("matrices inputed", GREEN);
  if (!WinogradInputN()) {
    ConsoleOutput("invalid input", RED);
    return false;
  }
  return true; 
}

bool WinogradCommand::WinogradInputRandom() {
  ConsoleOutput("format \n2 3\n3 3\n", BLUE);
  ConsoleOutput("input the sizes of matrices", YELLOW);
  std::cout << "--> ";
  if(!winograd_.InputMatricesRandom()) {
    ConsoleOutput("invalid input", RED);
    return false;
  }
  ConsoleOutput("matrices inputed\n", GREEN);
  PrintMatrix(winograd_.GetLeftMatrix());
  PrintMatrix(winograd_.GetRightMatrix());
  if (!WinogradInputN()) {
    ConsoleOutput("invalid input", RED);
    return false;
  }
  return true;
}

bool WinogradCommand::WinogradInputN() {
  std::istream& input = std::cin;
  ConsoleOutput("input count of iteration", YELLOW);
  std::cout << "--> ";
  if (!(input >> n_)) {
    return false;
  }
  return true;
}

bool WinogradCommand::WinogradDefault(std::size_t n) {
  const std::vector<std::vector<double>>& result = winograd_.GetResultDefault();
  return WinogradOutput(result, n);
}

bool WinogradCommand::WinogradClassic(std::size_t number_threads, std::size_t n) {
  const std::vector<std::vector<double>>& result = winograd_.GetResultClassic(number_threads);
  return WinogradOutput(result, n);
}

bool WinogradCommand::WinogradPipeline(std::size_t n) {
  const std::vector<std::vector<double>>& result = winograd_.GetResultPipeline();
  return WinogradOutput(result, n);
}

bool WinogradCommand::WinogradOutput(const std::vector<std::vector<double>>& result, std::size_t n) {
  if (result.empty()) {
    ConsoleOutput("solution not found", RED);
    return false;
  }
  if (n == 1) {
    std::cout << GREEN << "solution\n";
    PrintMatrix(result);
  }
  return true;
}

void WinogradCommand::PrintMatrix(const std::vector<std::vector<double>>& matrix) {
  for (std::size_t i = 0; i < matrix.size(); i++) {
    std::cout << "[ ";
    for (std::size_t j = 0; j < matrix[i].size(); j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "]\n";
  }
  std::cout << "\n" << RESET << std::endl;
}

}  // namespace s21
