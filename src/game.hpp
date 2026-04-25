#ifndef GAME_H_
#define GAME_H_

#include "types.hpp"

class Game {
public:

Game();

GameState tick();

void render();

private:
  
};

#endif  // GAME_H_
