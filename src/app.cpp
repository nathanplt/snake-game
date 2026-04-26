#include <iostream>
#include <optional>
#include <thread>
#include <chrono>
#include <sys/time.h>

#include "app.hpp"
#include "game.hpp"
#include "utils.hpp"
#include "types.hpp"

void App::play() {
  clear_screen();
  std::cout << "WELCOME TO TERMINAL SNAKE GAME" << '\n'
            << "ENTER BOARD SIZE: ";

  int size;
  std::cin >> size;

  Game m_game(size);
  bool is_playing = true;

  const auto frame_time = std::chrono::milliseconds(110);
  timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 110000;

  while (is_playing) {
    std::cin.ignore();
    std::cout << '\n' << "PRESS ENTER TO PLAY" << '\n';
    std::cin.ignore();

    bool in_game = true;
    m_term.enable_raw();

    while (in_game) {
      clear_screen();
      m_game.render();

      auto frame_start = std::chrono::steady_clock::now();
      std::optional<char> move_chr = get_char(timeout);

      // drain input buffer
      while (true) {
        timeval no_wait;
        no_wait.tv_sec = 0;
        no_wait.tv_usec = 0;

        std::optional<char> c = get_char(no_wait);
        if (!c.has_value()) {
          break;
        }

        move_chr = c;
      }

      GameState result = m_game.tick(move_chr);

      if (result == GameState::ONGOING) {
        std::this_thread::sleep_until(frame_start + frame_time);
        continue;
      } else {
        m_term.disable_raw();

        if (result == GameState::LOST) {
          std::cout << "OOPS! Snake collided and died..." << '\n';
        } else if (result == GameState::WON) {
          std::cout << "Congrats! You ate all the fruit." << '\n';
        }

        std::cout << "Replay? (Y/N) ";
        
        char input;
        std::cin >> input;

        if (toupper(input) == 'Y') {
          m_game.reset(size);
        } else {
          is_playing = false;
        }

        in_game = false;
      }
    }
  }
}
