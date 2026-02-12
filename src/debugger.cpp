#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>

#include "linenoise/linenoise.h"
#include "mudbg/command.h"
#include "mudbg/debugger.h"
#include "mudbg/mudbg.h"

namespace mudbg {

static void handle_command(const char* line) {
  auto command = Command::parse(line);
  if (command == nullptr) {
    std::cout << "Unknown command\n";
    return;
  }

  auto result = command->execute();
  if (result == CommandResult::FAILURE) {
    std::cout << "Command execution failed\n";
  }
}

Debugger::Debugger(const std::string& program, const pid_t& pid)
    : program_(program), pid_(pid) {}

void Debugger::run() {
  int wait_status;
  auto options = 0;
  waitpid(pid_, &wait_status, options);

  char* line = nullptr;
  while ((line = linenoise("mudbg> ")) != nullptr) {
    handle_command(line);
    linenoiseHistoryAdd(line);
    linenoiseFree(line);
  }
}

}  // namespace mudbg
