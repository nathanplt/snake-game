#include <iostream>
#include <random>
#include <vector>
#include <string>

#include "utils.hpp"
#include "types.hpp"
#include "game.hpp"

Game::Game(int size)
 : m_high_score(0) {
  reset(size); 
}

void Game::reset(int size) {
  m_size = size;
  m_score = 0;
  m_state = GameState::ONGOING;
  m_direction = Dir::RIGHT;

  m_snake.clear();
  m_snake.push_front({DEFAULT_X, m_size / 2});

  m_snake_coords.clear();
  m_snake_coords.insert({DEFAULT_X, m_size / 2});

  generate_fruit();
}

GameState Game::tick(std::optional<char> move_chr) {
  if (m_state != GameState::ONGOING) {
    return GameState::ERROR;
  }
  
  Dir move = move_chr ? char_to_dir(move_chr.value()) : m_direction;
  if (is_valid_dir(move)) {
    m_direction = move;
  }

  Coord next_pos = next_coord(m_snake.front(), m_direction);
  if (is_collision(next_pos)) {
    return GameState::LOST;
  }

  m_snake.push_front(next_pos);
  m_snake_coords.insert(next_pos);

  if (next_pos == m_fruit) {
    ++m_score;
    m_high_score = std::max(m_high_score, m_score);
    generate_fruit();
  } else {
    m_snake_coords.erase(m_snake.back());
    m_snake.pop_back();
  }

  if (m_score == m_size * m_size) {
    return GameState::WON;
  }

  return GameState::ONGOING;
}

void Game::render() const {
  std::vector<std::vector<std::string>> board(m_size,
    std::vector<std::string>(m_size, BLANK_CHR));

  board[m_fruit.y][m_fruit.x] = FRUIT_CHR;
  for (const auto& [x, y] : m_snake_coords) {
    board[y][x] = BODY_CHR;
  }
  board[m_snake.back().y][m_snake.back().x] = TAIL_CHR;
  board[m_snake.front().y][m_snake.front().x] = HEAD_CHR;

  int expand_factor = 2;
  std::vector<std::vector<std::string>> output = expand_board(board, expand_factor);

  for (int i = output.size() - 1; i >= 0; --i) {
    for (int j = 0; j < output.size(); ++j) {
      std::cout << output[i][j] << " ";
    }
    std::cout << '\n';
  }

  std::cout << '\n' << "SCORE: " << m_score
            << '\n' << "HIGH SCORE: " << m_high_score
            << '\n' << '\n';
}

int Game::get_score() const { return m_score; }


void Game::generate_fruit() {
  Coord prev_coord = m_fruit;
  do {
    m_fruit = generate_coord();
  } while (m_fruit == prev_coord || 
           m_snake_coords.count(m_fruit));
}

Coord Game::generate_coord() const {
  static std::random_device rd;
  static std::mt19937 generator(rd());
  std::uniform_int_distribution<> distr(0, m_size - 1);
  return {distr(generator), distr(generator)};
}

bool Game::is_valid_dir(Dir move) const {
  return move != m_direction && move != opposite_dir(m_direction);
}

bool Game::is_collision(const Coord& pos) const {
  return pos.x < 0 ||
         pos.y < 0 ||
         pos.x == m_size ||
         pos.y == m_size ||
         m_snake_coords.count(pos);
}

Coord Game::next_coord(const Coord& curr, Dir move) const {
  switch (move) {
    case Dir::UP: return {curr.x, curr.y + 1};
    case Dir::DOWN: return {curr.x, curr.y - 1};
    case Dir::RIGHT: return {curr.x + 1, curr.y};
    case Dir::LEFT: return {curr.x - 1, curr.y};
  }
  return curr;
}

std::vector<std::vector<std::string>> Game::expand_board(const std::vector<std::vector<std::string>>& board,
                                                         int mult) const {
  int n = board.size();
  int m = board[0].size();

  std::vector<std::vector<std::string>> new_board(n * mult,
    std::vector<std::string>(m * mult));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      for (int r = i * mult; r < i * mult + mult; ++r) {
        for (int c = j * mult; c < j * mult + mult; ++c) {
          new_board[r][c] = board[i][j];
        }
      }
    }
  }

  return new_board;
}
