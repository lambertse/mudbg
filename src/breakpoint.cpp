#include "mudbg/breakpoint.h"
#include <sys/ptrace.h>

namespace mudbg {

void BreakPoint::enable() {
  if (enabled_) {
    return;
  }
  long data = ptrace(PTRACE_PEEKDATA, pid_, addr_, nullptr);
  saved_data_ = static_cast<uint8_t>(data & 0xFF); // Save original bottom byte
  long int3_data = (data & ~0xFF) | 0xCC; // Replace bottom byte with 0xCC
  ptrace(PTRACE_POKEDATA, pid_, addr_, int3_data);
  enabled_ = true;
}

void BreakPoint::disable() {
  if (!enabled_) {
    return;
  }
  long data = ptrace(PTRACE_PEEKDATA, pid_, addr_, nullptr);
  long restored_data = (data & ~0xFF) | saved_data_; // Restore original bottom byte
  ptrace(PTRACE_POKEDATA, pid_, addr_, restored_data);

  enabled_ = false;
}

}  // namespace mudbg
