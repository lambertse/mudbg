#pragma once

#include <sys/types.h>
namespace mudbg {

class BreakPoint {
 private:
  pid_t pid_;
  std::intptr_t addr_;
  bool enabled_;
  uint8_t saved_data_;

 public:
  BreakPoint(pid_t pid, std::intptr_t addr)
      : pid_(pid), addr_(addr), enabled_(false), saved_data_(0) {}

  void enable();
  void disable();
  bool is_enabled() const { return enabled_; }
  std::intptr_t get_addr() const { return addr_; }
};

}  // namespace mudbg
