#include "../Headers/Parallels.h"

namespace s21 {

void Parallels::start() {
  std::vector<std::shared_ptr<Command>> commands_;
  commands_.push_back(std::make_shared<AcoCommand>());
  commands_.push_back(std::make_shared<SleCommand>());
  commands_.push_back(std::make_shared<WinogradCommand>());
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
    } else if (choice >= 0 && choice < (int)commands_.size()) {
      std::cin.ignore(32767, '\n');
      commands_[choice]->execute();
    }
  } while (choice != 11);
};

}  // namespace s21