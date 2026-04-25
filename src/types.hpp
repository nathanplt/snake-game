#ifndef TYPES_H_
#define TYPES_H_

enum class GameState {
  ONGOING,
  WON,
  LOST,
  ERROR
};

enum class Dir {
  UP,
  DOWN,
  RIGHT,
  LEFT
};

struct Coord {
  int x{};
  int y{};

  bool operator==(const Coord& other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Coord& other) const {
    return !(*this == other);
  }

  bool operator<(const Coord& other) const {
    if (x == other.x) {
      return y < other.y;
    }
    return x < other.x;
  }
};

#endif  // TYPES_H_
