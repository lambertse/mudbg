#include "mudbg/debugger.h"
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
using namespace mudbg;
static void execute_debugee(const char* program) {
  if (ptrace(PT_TRACE_ME, 0, 0, 0) < 0) {
    std::cerr << "Error in ptrace\n";
    return;
  }
  execl(program, program, nullptr);
}

int main(int argc, char* argv[]) {
  if(argc < 2) {
    std::cerr << "Usage: mudbg <program> <args>\n";
    return -1;
  }
  char* program = argv[1];

  pid_t pid = fork();
  if (pid == 0) {
    std::cout << "Starting debugee process\n";
    execute_debugee(program);
  } else {
    std::cout << "Starting debugger process\n";
    Debugger dbg{program, pid};
    dbg.run();
  }
}



