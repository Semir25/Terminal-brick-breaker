#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <vector>
#include "block.hpp"

typedef std::unordered_map<block,int> umap;
typedef std::vector<std::vector<int>> matrix;

int getWidth();
int getHeight();
umap shape_gen(int terminalW, int terminalH);
matrix vectorize(umap um, int w);
void print_matrix(matrix matr);//temporary, for testing

int main() {
  int w = getWidth(), h = getHeight();
  umap um = shape_gen(w,h);
  matrix matr = vectorize(um, w);
  print_matrix(matr);
}
