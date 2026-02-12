#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>
#include <memory>

#include "linenoise/linenoise.h"
#include "mudbg/command.h"
#include "mudbg/debugger.h"
#include "mudbg/mudbg.h"

namespace mudbg {

Debugger::Debugger(const std::string& program, const pid_t& pid)
    : program_(program), pid_(pid) {}

CommandResult Debugger::handle_command(std::shared_ptr<Command> command) {
  if (command == nullptr) {
    std::cout << "Unknown command\n";
    return CommandResult::FAILURE;
  }
  switch (command->type()) {
    case CommandType::CONTINUE:
      return handle_cmd_continue();
    case CommandType::BREAKPOINT_SET:
      return handle_cmd_set_breakpoint(
          std::stol(command->args().front(), nullptr, 16));
    default:
      std::cout << "Unknown command\n";
      return CommandResult::FAILURE;
  }
  return CommandResult::FAILURE;
}

void Debugger::run() {
  int wait_status;
  auto options = 0;
  waitpid(pid_, &wait_status, options);

  char* line = nullptr;
  while ((line = linenoise("mudbg> ")) != nullptr) {
    auto command = Command::parse(line);
    handle_command(command);
    linenoiseHistoryAdd(line);
    linenoiseFree(line);
  }
}

CommandResult Debugger::handle_cmd_continue() { return CommandResult::SUCCESS; }

CommandResult Debugger::handle_cmd_set_breakpoint(std::intptr_t addr) {
  auto bp = std::make_unique<BreakPoint>(pid_, addr);
  bp->enable();
  breakpoints_[addr] = std::move(bp);
  std::cout << "Breakpoint set at address " << std::hex << addr << "\n";
  return CommandResult::SUCCESS;
}

}  // namespace mudbg
