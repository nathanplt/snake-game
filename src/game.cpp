#include <iostream>
#include <random>
#include <vector>
#include "types.hpp"
#include "game.hpp"

Game::Game(int size) {
  reset(size); 
}

void Game::reset(int size) {
  m_size = size;
  m_score = 0;
  m_state = GameState::ONGOING;
  m_direction = Dir::RIGHT;

  m_snake.clear();
  m_snake.push_front({DEFAULT_X, DEFAULT_Y});

  m_snake_coords.clear();
  m_snake_coords.insert({DEFAULT_X, DEFAULT_Y});
  generate_fruit();
}

GameState Game::tick(Dir move) {
  if (m_state != GameState::ONGOING) {
    return GameState::ERROR;
  }
  if (!is_valid_dir(move)) {
    move = m_direction;
  }

  m_direction = move;

  Coord next_pos = next_coord(m_snake.front(), move);
  if (is_collision(next_pos)) {
    return GameState::LOST;
  }

  m_snake.push_front(next_pos);
  m_snake_coords.insert(next_pos);

  if (next_pos == m_fruit) {
    ++m_score;
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
  static const char DEFAULT_CHR = '.';
  static const char SNAKE_CHR = 'S';
  static const char FRUIT_CHR = 'F';  

  std::vector<std::vector<char>> board(m_size, std::vector<char>(m_size, DEFAULT_CHR));

  board[m_fruit.y][m_fruit.x] = FRUIT_CHR;
  for (const auto& [x, y] : m_snake_coords) {
    board[y][x] = SNAKE_CHR;
  }

  for (int i = m_size - 1; i >= 0; --i) {
    for (int j = 0; j < m_size; ++j) {
      std::cout << board[i][j] << " ";
    }
    std::cout << '\n';
  }
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
  static std::uniform_int_distribution<> distr(0, m_size - 1);
  return {distr(generator), distr(generator)};
}

bool Game::is_valid_dir(Dir move) const {
  return move != m_direction && move != opposite_dir(m_direction);
}

Dir Game::opposite_dir(Dir d) const {
  switch (d) {
    case Dir::UP: return Dir::DOWN;
    case Dir::DOWN: return Dir::UP;
    case Dir::RIGHT: return Dir::LEFT;
    case Dir::LEFT: return Dir::RIGHT;
  }
  return m_direction;
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
