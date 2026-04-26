#include <iostream>
#include <optional>

#include "app.hpp"
#include "game.hpp"
#include "utils.hpp"
#include "types.hpp"

App::App(int size)
 : m_game(size)  {
}

App::~App() {
  reset_term_mode(m_term);
}

void App::play() {
  bool is_playing = true;

  while (is_playing) {
    std::cout << "WELCOME TO TERMINAL SNAKE GAME!!" << '\n'
              << "PRESS ENTER TO PLAY" << '\n';
    std::cin.ignore();

    bool in_game = true;
    set_raw_term(m_term);

    while (in_game) {
      clear_screen();
      m_game.render();

      std::optional<char> move_chr = get_char();
      if (!move_chr) {
        move_chr.emplace('X');
      }

      Dir move = char_to_dir(move_chr.value());
      GameState result = m_game.tick(move);

      if (result == GameState::ONGOING) {
        continue;
      } else {
        reset_term_mode(m_term);

        if (result == GameState::LOST) {
          std::cout << "OOPS! Snake collided and died..." << '\n';
        } else if (result == GameState::WON) {
          std::cout << "Congrats! You ate all the fruit." << '\n';
        }

        std::cout << "You ended with score: " << m_game.get_score() << '\n'
                   << "Replay? (Y/N) ";
        
        char input;
        std::cin >> input;

        if (toupper(input) == 'Y') {
          m_game.reset();
          set_raw_term(m_term);
        } else {
          is_playing = false;
        }

        in_game = false;
      }
    }
  }
}
