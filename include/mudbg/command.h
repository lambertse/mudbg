#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace mudbg {

enum class CommandType {
  UNKNOWN,
  CONTINUE,
  STEP_INSTRUCTION,
  STEP_INSTRUCTION_OVER,
  PRINT_REGISTER,
  PRINT_MEMORY,
  BREAKPOINT_SET,
  BREAKPOINT_REMOVE,
  BACKTRACE,
  QUIT
};

enum class CommandResult { SUCCESS, FAILURE };

class Command {
 public:
  Command(CommandType type, std::vector<std::string> args = {})
      : type_(type), args_(std::move(args)) {}
  CommandType type() const { return type_; }
  virtual ~Command() = default;
  std::vector<std::string> args() const { return args_; }

  static std::shared_ptr<Command> parse(const std::string& line);

 protected:
  CommandType type_;
  std::vector<std::string> args_;
};

class ContinueCommand : public Command {
 public:
  ContinueCommand() : Command(CommandType::CONTINUE) {}
};

class BreakCommand : public Command {
 public:
  BreakCommand(const std::string& location)
      : Command(CommandType::BREAKPOINT_SET, {location}) {}
};
}  // namespace mudbg
