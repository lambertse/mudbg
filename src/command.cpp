#include "mudbg/command.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

namespace mudbg {

static std::vector<std::string> split(const std::string& s, char delimiter) {
  std::vector<std::string> out{};
  std::stringstream ss{s};
  std::string item;

  while (std::getline(ss, item, delimiter)) {
    out.push_back(item);
  }

  return out;
}

static bool is_prefix(const std::string& line, const std::string& prefix) {
  return line.compare(0, prefix.length(), prefix) == 0;
}

std::shared_ptr<Command> Command::parse(const std::string& line) {
  auto args = split(line, ' ');
  if (args.empty()) {
    return nullptr;
  }
  if (is_prefix(args.front(), "continue")) {
    return std::make_shared<ContinueCommand>();
  }

  return nullptr;
}

CommandResult ContinueCommand::execute() {
  std::cout << "Continuing execution...\n";
  // Placeholder for continue command execution logic
  return CommandResult::SUCCESS;
}

}  // namespace mudbg
