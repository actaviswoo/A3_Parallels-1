#include "../Headers/AcoCommand.h"

namespace s21 {

bool AcoCommand::AcoChoice() {
  int choice = 0;
  do {
    ConsoleOutput(menu_, PURPLE);
    ConsoleOutput("make your choice", YELLOW);
    std::cout << "--> ";
    std::cin.clear();
    std::cin >> choice;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(32767, '\n');
    } else if (choice == 0) {
      std::cin.ignore(32767, '\n');
      if (AcoLoadMatrixFromFile()) return true;
    } else if (choice == 1) {
      std::cin.ignore(32767, '\n');
      if (AcoInputMartix()) return true;
    }
  } while (choice != 2);
  return false;
}

bool AcoCommand::AcoLoadMatrixFromFile() {
  std::istream& input = std::cin;
  std::string filename;
  ConsoleOutput("input filename", YELLOW);
  std::cout << "--> ";
  input >> filename;
  if (!aco_.LoadMatrixFromFile(filename)) {
    ConsoleOutput("cant't load", RED);
    return false;
  }
  ConsoleOutput("matrix loaded", GREEN);
  if (!AcoInputN()) return false;
  return true;
}

bool AcoCommand::AcoInputMartix() { 
  ConsoleOutput("format \n 3\n1 2 3 \n2 1 3 \n5 8 1", BLUE);
  ConsoleOutput("input martix", YELLOW);
  std::cout << "--> ";
  if(!aco_.InputMatrix()) {
    ConsoleOutput("invalid input", RED);
    return false;
  }
  ConsoleOutput("matrix inputed", GREEN);
  if (!AcoInputN()) {
    ConsoleOutput("invalid input", RED);
    return false;
  }
  return true; 
}

bool AcoCommand::AcoInputN() {
  std::istream& input = std::cin;
  ConsoleOutput("input count of iteration", YELLOW);
  std::cout << "--> ";
  if (!(input >> n_)) {
    ConsoleOutput("invalid input", RED);
    return false;
  }
  return true;
}

bool AcoCommand::AcoDefault() {
  TsmResult result = aco_.GetResultDefault();
  return AcoOutput(result);
}

bool AcoCommand::AcoAdvanced() {
  TsmResult result = aco_.GetResultAdvanced();
  return AcoOutput(result);
}

bool AcoCommand::AcoOutput(TsmResult& result) {
  if (result.vertices.empty()) {
    ConsoleOutput("solution not found", RED);
    return false;
  }
  std::cout << GREEN << "vertices\n[ ";
  for (std::size_t i = 0; i < result.vertices.size(); i++) {
    std::cout << result.vertices[i] + 1 << " ";
  }
  std::cout << "]\ndistance\n[ " << result.distance << " ]" << RESET
            << std::endl;
  return true;
}

}  // namespace s21