#include <iostream>
#include "game.hpp"
#include "types.hpp"

Dir char_to_dir(char c) {
  switch (toupper(c)) {
    case 'U': 
    case 'S': return Dir::UP;
    case 'D': 
    case 'X': return Dir::DOWN;
    case 'R': 
    case 'C': return Dir::RIGHT;
    case 'L': 
    case 'Z': return Dir::LEFT;
  }
  return Dir::UP;
}

int main() {
  Game game;
  bool is_playing = true;

  while (is_playing) {
    std::cout << "WELCOME TO TERMINAL SNAKE GAME!!" << '\n'
              << "PRESS ENTER TO PLAY" << '\n';
    std::cin.ignore();

    bool in_game = true;

    while (in_game) {
      game.render();
      std::cout << "ENTER MOVE (U/D/L/R): ";

      char move_chr;
      std::cin >> move_chr;

      Dir move = char_to_dir(move_chr);
      GameState result = game.tick(move);

      if (result == GameState::ONGOING) {
        continue;
      } else if (result == GameState::LOST) {
        std::cout << "OOPS! Snake collided and died..." << '\n'
                  << "You ended with score: " << game.get_score() << '\n'
                  << "Replay? (Y/N) ";
        
        char input;
        std::cin >> input;

        if (toupper(input) == 'Y') {
          game.reset();
        } else {
          is_playing = false;
        }

        in_game = false;
      } else if (result == GameState::WON) {
        std::cout << "Congrats! You ate all the fruit." << '\n'
                  << "You ended with score: " << game.get_score() << '\n'
                  << "Replay? (Y/N) ";

        char input;
        std::cin >> input;

        if (toupper(input) == 'Y') {
          game.reset();
        } else {
          is_playing = false;
        }
        
        in_game = false;
      }
    }
  }
}