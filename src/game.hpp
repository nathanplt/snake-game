#pragma once

#include <deque>
#include <set>
#include "types.hpp"

class Game {
public:

Game(int size = DEFAULT_SIZE);

void reset(int size = DEFAULT_SIZE);

GameState tick(Dir move);

void render() const;

int get_score() const;

private:
  static const int DEFAULT_SIZE = 15;
  static const int DEFAULT_X = 1;

  void generate_fruit();
  Coord generate_coord() const;

  bool is_valid_dir(Dir move) const;
  Dir opposite_dir(Dir d) const;

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

