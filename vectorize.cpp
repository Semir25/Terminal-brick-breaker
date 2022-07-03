#include "block.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>//tmp

typedef std::unordered_map<block,int> umap;
typedef std::vector<std::vector<int>> matrix;

matrix vectorize(umap um) {
  matrix right_half;
  int width = 0, height = 0;
  for(auto e : um) {
    int y = e.first.y;
    if(y >= right_half.size()) right_half.resize(y+1);
    int x = e.first.x;
    if(x >= right_half[y].size()) right_half[y].resize(x+1);
    right_half[y][x] = e.second;

    if(width < x+1) width = x+1;
    if(height < y+1) height = y+1;
  }
  matrix matr;
  matr.resize(height);
  for(int i=0; i<height; ++i) {
    matr[i].resize(width*2);
    for(int j=width-right_half[i].size(); j<width; ++j) {
      matr[i][j] = right_half[i][width-j-1];
    }
    for(int j=width; j<width+right_half[i].size(); ++j) {
      matr[i][j] = right_half[i][j-width];
    }
  }
  return matr;
}

void print_matrix(matrix matr) {
  for(int i=0; i<matr.size(); ++i) {
    for(int j=0; j<matr[i].size(); ++j) {
      if(matr[i][j] != 0)
        std::cout << "L"<< matr[i][j] << "/";
      else
        std::cout << "   ";
    }
    std::cout << std::endl;
  }
}


