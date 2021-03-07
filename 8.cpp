#include <iostream>
  
  void fn(int roomSize, int &resultSum, int **costs, int *result, bool *avalible,
          int &bestResultSum, int *bestResult, int col = 0) {
    if (col >= roomSize && resultSum < bestResultSum) {
      for (auto col = 0; col < roomSize; col++) {
        bestResult[col] = result[col];
      }
      bestResultSum = resultSum;
    }
  
    if (col >= roomSize || resultSum > bestResultSum) {
      return;
    }
  
    for (auto row = 0; row < roomSize; row++) {
      if (!avalible[row]) {
        continue;
      }
      avalible[row] = false;
      result[col] = row;
      resultSum += costs[row][col];
      fn(roomSize, resultSum, costs, result, avalible, bestResultSum, bestResult,
         col + 1);
      avalible[row] = true;
      resultSum -= costs[row][col];
    }
  };
  
  int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
  
    int roomSize;
  
    std::cin >> roomSize;
  
    int *costs[roomSize];
    bool avalible[roomSize];
  
    for (auto i = 0; i < roomSize; i++) {
      costs[i] = new int[roomSize];
  
      for (auto j = 0; j < roomSize; j++) {
        std::cin >> costs[i][j];
      }
  
      avalible[i] = true;
    }
  
    int result[roomSize];
    int resultSum = 0;
    int bestResult[roomSize];
    int bestResultSum = 2147483647;
  
    fn(roomSize, resultSum, costs, result, avalible, bestResultSum, bestResult);
  
    for (auto i = 0; i < roomSize; i++) {
      std::cout << bestResult[i] << " ";
    }
  }