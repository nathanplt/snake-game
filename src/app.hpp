#pragma once

#include <optional>

#include "termios.h"
#include "game.hpp"

class App {
public:
  App(int size);

  ~App();

  void play();

private:
  Game m_game;
  struct termios m_term;
};

