#include "../Headers/Command.h"

namespace s21 {
void ConsoleOutput(const std::string& message, const std::string& color) {
    std::cout << color << message << RESET << std::endl;
    std::cin.clear();
}

} // namespace s21

