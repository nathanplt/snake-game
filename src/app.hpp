#pragma once

#include <optional>
#include <sys/time.h>

#include "utils.hpp"
#include "game.hpp"

class App {
public:
  App() = default;

  void play();

private:  
  TerminalMode m_term;
};

