#pragma once

#include <optional>
#include <vector>
#include <deque>
#include <set>
#include <string>

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

  inline static const std::string BLANK_CHR = "·";
  inline static const std::string BODY_CHR = "o";
  inline static const std::string HEAD_CHR = "O";
  inline static const std::string FRUIT_CHR = "*";

  std::vector<std::vector<std::string>> expand_board(const std::vector<std::vector<std::string>>& board,
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

