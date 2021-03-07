#include <algorithm>
#include <iostream>

long int errors = 0;

void mergeSorted(unsigned int *A, int iLeft, int iRight, int iEnd,
                 unsigned int *B) {
  auto i = iLeft, j = iRight;
  auto k = iLeft;

  for (; i < iRight && j < iEnd; k++) {
    if (A[i] > A[j]) {
      B[k] = A[j];
      errors += iRight - i;
      j++;
    } else {
      B[k] = A[i];
      i++;
    }
  }

  for (; i < iRight; i++, k++) {
    B[k] = A[i];
  }

  for (; j < iEnd; j++, k++) {
    B[k] = A[j];
  }
}

void merge(unsigned int *A, unsigned int *B, int n, int width = 1) {
  if (width >= n) {
    return;
  }

  for (auto i = 0; i < n; i += 2 * width) {
    mergeSorted(A, i, std::min(i + width, n), std::min(i + 2 * width, n), B);
  }

  merge(B, A, n, width * 2);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  unsigned int patientsLength;
  std::cin >> patientsLength;

  unsigned int patients[patientsLength];

  for (auto i = 0; i < patientsLength; i++) {
    std::cin >> patients[i];
  }

  unsigned int w[patientsLength];

  merge(patients, w, patientsLength);

  std::cout << errors;
}
