#include <iostream>

template <typename T>
void swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int testsCount;

  std::cin >> testsCount;

  while (testsCount--) {
    int arrLength;
    std::cin >> arrLength;

    std::string labels[arrLength];
    int timestamps[arrLength];
    int indexes[arrLength];

    for (int i = 0; i < arrLength; i++) {
      std::cin >> labels[i] >> timestamps[i];
      indexes[i] = i;
    }

    int comparatorField;
    std::cin >> comparatorField;

    if (comparatorField == 0) {
      auto cmp = [&](const int &i, const int &j) -> int {
        int k = labels[i].compare(labels[j]);
        if (k != 0) {
          return k;
        }
        return timestamps[j] - timestamps[i];
      };

      for (int i = 1; i < arrLength; i++) {
        for (int j = i; (j > 0) && (cmp(indexes[j - 1], indexes[j]) > 0); j--) {
          swap(indexes[j], indexes[j - 1]);
        }
      }

    } else {
      auto cmp = [&](const int &i, const int &j) -> int {
        int k = timestamps[j] - timestamps[i];
        if (k != 0) {
          return k;
        }
        return labels[i].compare(labels[j]) ;
      };

      for (int i = 1; i < arrLength; i++) {
        for (int j = i; (j > 0) && (cmp(indexes[j - 1], indexes[j]) > 0); j--) {
          swap(indexes[j], indexes[j - 1]);
        }
      }
    }

    for (int i = 0; i < arrLength; i++) {
      int j = indexes[i];
      std::cout << labels[j] << "-" << timestamps[j] << " ";
    }
    std::cout << std::endl;
  }
}