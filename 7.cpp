#include <algorithm>
#include <iostream>
#include <list>
#include <tuple>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  unsigned int testsLength;
  std::cin >> testsLength;

  while (testsLength--) {
    unsigned int roomSize;
    std::cin >> roomSize;

    std::vector<std::tuple<unsigned int, unsigned int>> columns;

    for (auto i = 0; i < roomSize; i++) {
      unsigned int rowStart, rowEnd;

      std::cin >> rowStart >> rowEnd;
      columns.push_back(std::make_tuple(rowEnd, rowStart));
    }

    std::sort(columns.begin(), columns.end());

    std::vector<int> rows;

    for (auto i = 0; i < roomSize; i++) {
      rows.push_back(i);
    }

    ([&]() {
      for (const auto& column : columns) {
        int rowStart, rowEnd;
        std::tie(rowEnd, rowStart) = column;

        auto i = std::upper_bound(rows.begin(), rows.end(), rowStart - 1);

        if (i == rows.end() || *i > rowEnd) {
          std::cout << "NIE" << '\n';
          return;
        }
        rows.erase(i);
      }
      std::cout << "TAK" << '\n';
    })();
  }
}