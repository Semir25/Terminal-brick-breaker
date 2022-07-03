#include "block.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>//tmp

typedef std::unordered_map<block,int> umap;
typedef std::vector<std::vector<int>> matrix;

matrix vectorize(umap um, int w) {
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
  int padding = (w/3-width*2)/2;

  matrix matr;
  matr.resize(height);
  for(int i=0; i<height; ++i) {
    matr[i].resize(padding+width*2);
    for(int j=width-right_half[i].size(); j<width; ++j) {
      matr[i][j+padding] = right_half[i][width-j-1];
    }
    for(int j=width; j<width+right_half[i].size(); ++j) {
      matr[i][j+padding] = right_half[i][j-width];
    }
  }
  return matr;
}

void print_matrix(matrix matr) {
  for(int i=0; i<matr.size(); ++i) {
    for(int j=0; j<matr[i].size(); ++j) {
      if(matr[i][j] == 1)
        std::cout << "\033[1;45m   \033[0m";
      else if(matr[i][j] == 2)
        std::cout << "\033[1;44m   \033[0m";
      else if(matr[i][j] == 3)
        std::cout << "\033[1;46m   \033[0m";
      else if(matr[i][j] == 4)
        std::cout << "\033[1;42m   \033[0m";
      else if(matr[i][j] == 5)
        std::cout << "\033[1;43m   \033[0m";
      else if(matr[i][j] == 6)
        std::cout << "\033[1;41m   \033[0m";
      else
        std::cout << "   ";
    }
    std::cout << std::endl;
  }
}


