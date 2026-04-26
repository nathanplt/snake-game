#pragma once

#include <optional>
#include <termios.h>

#include "types.hpp"

/* Terminal utils */
void clear_screen();

class TerminalMode {
public:
  ~TerminalMode();  

  void enable_raw();

  void disable_raw();

private:
  termios m_term{};
  bool m_saved = false;
  bool m_raw = false;
};

std::optional<char> get_char(timeval& timeout);

/* Direction utils */
Dir char_to_dir(char c);

Dir opposite_dir(Dir d);
