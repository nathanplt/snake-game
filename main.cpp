#include <iostream>
#include "src/app.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);  
  std::cin.tie(NULL);

  App snake_game;
  snake_game.play();
}
