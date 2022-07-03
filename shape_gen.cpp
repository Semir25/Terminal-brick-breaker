#include <unordered_map>
#include <vector>
#include <ctime>
#include <cmath>
#include "block.hpp"

std::ostream& operator<<(std::ostream& out, const block& b) {
  out << "(" << b.x << "," << b.y << ")";
  return out;
}

static void rot90(int& x, int& y) {
  int tmp = x;
  x = y;
  y = -tmp;
}
static bool find_empty(block b, int& x, int& y, std::unordered_map<block, int>& half_of_shape, int w, int h) {
  for(int i = 0; i < 4; ++i) {
    if(b.x+x >= 0 && b.x+x < w && b.y+y >= 0 && b.y+y < h && half_of_shape.find(block{b.x+x,b.y+y}) == half_of_shape.end()) {
      int x1 = 0, y1 = 1, count = 0;
      for(int j = 0; j < 4; ++j) {
        if(b.x+x+x1 >= 0 && b.x+x+x1 < w && b.y+y+y1 >= 0 && b.y+y+y1 < h && half_of_shape.find(block{b.x+x+x1,b.y+y+y1}) == half_of_shape.end()) {
          count++;
        }
        rot90(x1,y1);
      }
      if(count == 3) 
        return true;
      else if(count == 2) {
        int r = rand()%4;
        if(r == 1) return true;
      }
      else if(count == 1) {
        int r = rand()%10;
        if(r == 1) return true;
      }
      else if(count == 0) {
        return true;
      }
    }

    rot90(x,y);
  }
  return false;
}
static block find_empty(const block& b, std::unordered_map<block, int>& half_of_shape, int w, int h) {
  int x, y;
  int r = rand()%4;
  //chosing random starting pos
  switch (r) {
    case 0:
      x = 1; y = 0; 
      break;
    case 1:
      x = 0; y = 1; 
      break;
    case 2:
      x = -1; y = 0; 
      break;
    case 3:
      x = 0; y = -1; 
      break;
      
    default:
      break;
  }
  //finding next empty
  if(find_empty(b, x, y, half_of_shape, w, h)) {
    return block{b.x+x,b.y+y};
  }
  return block{-1,-1};
}
static void remove(std::unordered_map<block, int>& edges, std::vector<block>& indexed_edges, const block& old_block) {
  //remove in indexed edges by swaping that block with last and calling pop_back
  block b_for_update = indexed_edges[indexed_edges.size()-1];
  int index = edges[old_block];
  std::swap(indexed_edges[index], indexed_edges[indexed_edges.size()-1]);
  indexed_edges.pop_back();
  //update index value of swaped element in edges
  edges[b_for_update] = index;
  //remove that element from edges
  edges.erase(old_block);
}
static void update_edges(const std::unordered_map<block, int>& half_of_shape, std::unordered_map<block, int>& edges, std::vector<block>& indexed_edges, const block& new_block, int w, int h) {
  int x1 = 0, y1 = 1;
  for(int i = 0; i < 4; ++i) {
    if(new_block.x+x1 >= 0 && new_block.x+x1 < w && new_block.y+y1 >= 0 && new_block.y+y1 < h && half_of_shape.find(block{new_block.x+x1,new_block.y+y1}) != half_of_shape.end()) {
      int x2 = 0, y2 = 1;
      bool still_edge = false;
      for(int j = 0; j < 4; ++j) {
        // std::cout << "new_block.x: " << new_block.x << " x1: " << x1 << " x2: " << x2 << " new_block.y: " << new_block.y << " y1: " << y1 << " y2: " << y2 << std::endl;
        // std::cout << (new_block.x+x1+x2 >= 0) << (new_block.x+x1+x2 < w) << 
        //   (new_block.y+y1+y2 >= 0) << (new_block.y+y1+y2 < h) << 
        //   (edges.find(block{new_block.x+x1+x2,new_block.y+y1+y2}) == edges.end()) << std::endl;
        if(new_block.x+x1+x2 >= 0 && new_block.x+x1+x2 < w && new_block.y+y1+y2 >= 0 && new_block.y+y1+y2 < h && half_of_shape.find(block{new_block.x+x1+x2,new_block.y+y1+y2}) == half_of_shape.end()) {
          still_edge = true;
          break;
        }
        // std::cout << "false: " << std::endl; 
        rot90(x2,y2);
      }
      if(!still_edge) {
        // std::cout << "remove: " << block{new_block.x+x1,new_block.y+y1} << std::endl;
        remove(edges, indexed_edges, block{new_block.x+x1,new_block.y+y1});
      }
    }
    rot90(x1,y1);
  }
}
static void add_block(std::unordered_map<block, int>& half_of_shape, std::unordered_map<block, int>& edges, std::vector<block>& indexed_edges, int w, int h, int points) {
  block b, new_block;
  while(true) {
    //pick a random block on edge
    b = indexed_edges[rand()%indexed_edges.size()]; 
    //find first random empty block around b in half_of_shape
    // std::cout << "random pick: " << b << std::endl;
    new_block = find_empty(b, half_of_shape, w, h);
    if(new_block != block{-1,-1}) break;
  }

  // std::cout << "new block: " << new_block << std::endl;

  //add that block in in all containers
  half_of_shape[new_block] = points;
  edges[new_block] = indexed_edges.size();
  indexed_edges.push_back(new_block);
  //check if that new block closed some other blocks, if it did remove those blocks
  update_edges(half_of_shape, edges, indexed_edges, new_block, w, h);
}

std::unordered_map<block, int> shape_gen(int terminalW, int terminalH) {
  std::unordered_map<block, int> half_of_shape;
  std::unordered_map<block, int> edges;
  std::vector<block> indexed_edges;

  int w, h, n;
  w = terminalW/6;
  h = terminalH/2;
  n = w*h/3;

  srand(time(0));

  half_of_shape[block{0,h/2}] = 9; 
  edges[block{0,h/2}] = 0;
  indexed_edges.push_back(block{0,h/2});

  for(int i = 0; i < n; ++i) {
    add_block(half_of_shape, edges, indexed_edges, w, h, 9-(log(i+1)/log(n))*8);
  }

  return half_of_shape;
}
