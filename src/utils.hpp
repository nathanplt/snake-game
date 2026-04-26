#pragma once

#include <optional>

#include "types.hpp"

/* Terminal utils */
void set_raw_term(struct termios &orig_termios);

void reset_term_mode(struct termios &orig_termios);

void clear_screen();

std::optional<char> get_char();

/* Direction utils */
Dir char_to_dir(char c);



