#include <algorithm>
#include <cmath>
#include <iostream>
// #include <list>
#include <forward_list>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
T findNthSmallest(std::vector<T>& vector, int nthBiggest) {
  if (vector.size() <= 10) {
    std::vector<T> vectorCopy(vector);
    std::nth_element(vectorCopy.begin(), vectorCopy.begin() + nthBiggest,
                     vectorCopy.end());
    return vectorCopy[nthBiggest];
  }

  std::vector<T> fragmentsMedians(std::ceil((double)vector.size() / (double)5));

  for (auto i = 0; i < vector.size(); i += 5) {
    auto fragmentBegin = vector.begin() + i;
    std::vector<T> fragment(
        fragmentBegin,
        fragmentBegin +
            std::min<int>(5, std::distance(fragmentBegin, vector.end())));

    std::nth_element(fragment.begin(), fragment.begin() + fragment.size() / 2,
                     fragment.end());

    fragmentsMedians[i / 5] = fragment[fragment.size() / 2];
  }

  const auto medianOfFragmentsMedians =
      findNthSmallest(fragmentsMedians, fragmentsMedians.size() / 2);

  std::vector<T> nextVector;
  std::copy_if(
      vector.begin(), vector.end(), std::back_inserter(nextVector),
      [&](auto& element) { return element < medianOfFragmentsMedians; });

  if (nthBiggest == nextVector.size()) {
    return medianOfFragmentsMedians;
  }

  fragmentsMedians.resize(0);

  if (nthBiggest < nextVector.size()) {
    return findNthSmallest(nextVector, nthBiggest);
  }

  nextVector.clear();
  std::copy_if(
      vector.begin(), vector.end(), std::back_inserter(nextVector),
      [&](auto& element) { return element > medianOfFragmentsMedians; });

  return findNthSmallest(nextVector,
                         nextVector.size() - vector.size() + nthBiggest);
}

struct Person {
  int id;
  int i;

  bool operator>(const Person& b) { return id > b.id; }
  bool operator<(const Person& b) { return id < b.id; }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int peopleLength, changesLength;
  std::cin >> peopleLength >> changesLength;

  std::vector<std::string> peopleNames(peopleLength);
  std::vector<Person> people(peopleLength);

  for (auto i = 0; i < peopleLength; i++) {
    people[i].i = i;
    std::cin >> people[i].id;
    std::getline(std::cin, peopleNames[i]);
  }

  for (auto i = 0; i < changesLength; i++) {
    int nthSmallest;
    std::cin >> nthSmallest;

    const auto nthSmallestPersonIndex = findNthSmallest(people, nthSmallest).i;

    for (auto i = std::max(0, nthSmallestPersonIndex - 2);
         i < std::min<int>(people.size(), nthSmallestPersonIndex + 3); i++) {
      std::cout << people[i].id << peopleNames[i] << '\n';
    }

    std::cin >> people[nthSmallestPersonIndex].id;

    std::getline(std::cin, peopleNames[nthSmallestPersonIndex]);
  }
}