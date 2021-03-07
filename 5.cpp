#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  unsigned short int centersLength;
  unsigned int roadsLength;
  unsigned short int centerId;
  unsigned short int maxTime;

  std::cin >> centersLength >> roadsLength >> centerId >> maxTime;

  std::vector<std::vector<bool>> centers(centersLength,
                                         std::vector<bool>(centersLength));

  for (auto i = 0; i < roadsLength; i++) {
    unsigned int id1;
    unsigned int id2;
    std::cin >> id1 >> id2;
    centers[id1][id2] = true;
    centers[id2][id1] = true;
  }

  for (auto j = 0; j < centersLength; j++) {
    centers[j][centerId] = false;
  }

  std::queue<std::tuple<unsigned short int, unsigned char>> clinicsToVisit;
  clinicsToVisit.push(std::make_tuple(centerId, 0));

  unsigned short int visitedInDistance = 0;
  unsigned char distance = 0;

  while (!clinicsToVisit.empty()) {
    std::tie(centerId, distance) = clinicsToVisit.front();
    auto& center = centers[centerId];

    if (distance >= maxTime / 2) {
      break;
    }

    for (auto i = 0; i < centersLength; i++) {
      if (center[i] == false) {
        continue;
      }
      for (auto& center : centers) {
        center[i] = false;
      }
      clinicsToVisit.push(std::make_tuple(i, distance + 1));
      visitedInDistance++;
    }

    clinicsToVisit.pop();
  }

  while (!clinicsToVisit.empty()) {
    std::tie(centerId, distance) = clinicsToVisit.front();
    auto& center = centers[centerId];

    for (auto i = 0; i < centersLength; i++) {
      if (center[i] == false) {
        continue;
      }
      for (auto& center : centers) {
        center[i] = false;
      }
      clinicsToVisit.push(std::make_tuple(i, distance + 1));
    }

    clinicsToVisit.pop();
  }

  std::cout << (int)distance << " " << visitedInDistance << std::endl;
}