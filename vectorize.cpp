#include "block.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>//tmp

typedef std::unordered_map<block,int> umap;
typedef std::vector<std::vector<int>> matrix;

matrix vectorize(umap um) {
  matrix matr;
  for(auto e : um) {
    int y = e.first.y;
    if(y >= matr.size()) matr.resize(y+1);
    int x = e.first.x;
    if(x >= matr[y].size()) matr[y].resize(x+1);
    matr[y][x] = e.second;
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


