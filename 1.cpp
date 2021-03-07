#include <iostream>

bool isSequenceable(int *aminoacidTypes, int aminoacidTypesLength) {
  for (int i = 0; i < aminoacidTypesLength; i++) {
    if (aminoacidTypes[i] != 0) {
      return false;
    }
  }
  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int testsCount;

  std::cin >> testsCount;

  while (testsCount--) {
    int aminoacidTypesLength;

    std::cin >> aminoacidTypesLength;

    int aminoacidTypes[aminoacidTypesLength];

    for (int i = 0; i < aminoacidTypesLength; i++) {
      aminoacidTypes[i] = 0;
    }

    int aminoacidType;
    do {
      std::cin >> aminoacidType;
      aminoacidTypes[aminoacidType]++;
    } while (aminoacidType != -1);

    do {
      std::cin >> aminoacidType;
      aminoacidTypes[aminoacidType]--;
    } while (aminoacidType != -1);

    if (isSequenceable(aminoacidTypes, aminoacidTypesLength)) {
      std::cout << "TAK" << std::endl;
    } else {
      std::cout << "NIE" << std::endl;
    }
  }
}