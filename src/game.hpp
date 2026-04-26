#pragma once

#include <optional>
#include <vector>
#include <deque>
#include <set>

#include "types.hpp"

class Game {
public:

Game(int size = DEFAULT_SIZE);

void reset(int size = DEFAULT_SIZE);

GameState tick(std::optional<char> move_chr);

void render() const;

int get_score() const;

private:
  static const int DEFAULT_SIZE = 15;
  static const int DEFAULT_X = 1;

  inline static const char BLANK_CHR = '.';
  inline static const char SNAKE_CHR = 'S';
  inline static const char FRUIT_CHR = 'F';  

  std::vector<std::vector<char>> expand_board(const std::vector<std::vector<char>>& board,
                                              int mult) const;

  void generate_fruit();
  Coord generate_coord() const;

  bool is_valid_dir(Dir move) const;

  bool is_collision(const Coord& pos) const;
  Coord next_coord(const Coord& curr, Dir move) const;

  int m_size;
  int m_score;

  GameState m_state;
  Coord m_fruit;

  Dir m_direction;
  std::deque<Coord> m_snake;
  std::set<Coord> m_snake_coords;
};

