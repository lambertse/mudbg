#pragma once

#include <sys/types.h>
#include <string>
namespace mudbg {

class Debugger {
public:
  Debugger(const std::string &program, const pid_t &pid);
  void run();

private:
  std::string program_;
  pid_t pid_;
};

} // namespace mudbg
