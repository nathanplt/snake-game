#include <iostream>
#include <optional>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

#include "utils.hpp"

/* Terminal utils*/

void set_raw_term(struct termios &orig_termios) {
  tcgetattr(STDIN_FILENO, &orig_termios);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void reset_term_mode(struct termios &orig_termios) {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void clear_screen() {
  std::cout << "\033[2J\033[1;1H";
}

std::optional<char> get_char() {
  fd_set set;
  struct timeval timeout;
  int rv;

  FD_ZERO(&set);
  FD_SET(STDIN_FILENO, &set);

  timeout.tv_sec = 0;
  timeout.tv_usec = 130000;

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
    case 'A': return Dir::LEFT;
  }
  return Dir::SAME;
}
