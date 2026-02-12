#pragma once

#include <sys/types.h>

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

#include "mudbg/breakpoint.h"
#include "mudbg/command.h"
namespace mudbg {

class Debugger {
 public:
  Debugger(const std::string& program, const pid_t& pid);
  void run();

 private:
  CommandResult handle_command(std::shared_ptr<Command> command);
  CommandResult handle_cmd_continue();
  CommandResult handle_cmd_set_breakpoint(std::intptr_t addr);

 private:
  std::string program_;
  pid_t pid_;
  std::unordered_map<std::intptr_t, std::unique_ptr<BreakPoint>> breakpoints_;
};

}  // namespace mudbg
