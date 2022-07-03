#pragma once
#include <unordered_map>
#include <iostream>

struct block {
  int x;
  int y;
  bool operator==(const block& other) const { return x == other.x && y == other.y; }
  bool operator!=(const block& other) const { return !(*this == other); }
};


namespace std {

  template <>
  struct hash<block>
  {
    std::size_t operator()(const block& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      return hash<int>()(k.x) ^ hash<int>()(k.y);
    }
  };

}
