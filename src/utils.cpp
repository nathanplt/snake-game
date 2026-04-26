#include <iostream>
#include <optional>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

#include "utils.hpp"

/* Terminal utils*/

TerminalMode::~TerminalMode() {
  if (m_raw && m_saved) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &m_term);
  }
}

void TerminalMode::enable_raw() {
  if (m_raw) return;

  if (!m_saved) {
    tcgetattr(STDIN_FILENO, &m_term);
    m_saved = true;
  }

  termios raw_term = m_term;
  raw_term.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_term);

  m_raw = true;
}

void TerminalMode::disable_raw() {
  if (!m_raw) return;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &m_term);
  m_raw = false;
}

void clear_screen() {
  std::cout << "\033[2J\033[1;1H";
}

std::optional<char> get_char(struct timeval& timeout) {
  fd_set set;
  int rv;

  FD_ZERO(&set);
  FD_SET(STDIN_FILENO, &set);

  rv = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);

  if (rv == -1 || rv == 0) {
    return std::nullopt;
  }

  char c;
  read(STDIN_FILENO, &c, 1);
  return c;
}

/* Direction utils */

Dir char_to_dir(char c) {
  switch (toupper(c)) {
    case 'W': return Dir::UP;
    case 'S': return Dir::DOWN;
    case 'D': return Dir::RIGHT;
    case 'A':
    default: return Dir::LEFT;
  }
}

Dir opposite_dir(Dir d) {
  switch (d) {
    case Dir::UP: return Dir::DOWN;
    case Dir::DOWN: return Dir::UP;
    case Dir::RIGHT: return Dir::LEFT;
    case Dir::LEFT: 
    default: return Dir::RIGHT;
  }
}
