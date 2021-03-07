#include <iostream>

template <typename T>
void swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <typename T>
T min(T a, T b) {
  return a < b ? a : b;
}

template <typename V>
struct Node {
  Node<V>* _next = nullptr;
  V _value;

  Node(V& value) : _value(value) {}
  Node<V> next() { return _next; }
  V& value() { return _value; }
};


template <typename T>
struct List {
  Node<T>* _head = nullptr;
  Node<T>* _tail = nullptr;
  int _size = 0;

  void push(T value) {
    _size++;
    if (_head == nullptr) {
      _head = new Node<T>(value);
      _tail = _head;
      return;
    }
    _tail->_next = new Node<T>(value);
    _tail = _tail->_next;
  }

  Iterator<T> begin() { return Iterator<T>(_head); }
  Iterator<T> end() { return Iterator<T>(nullptr); }

  void sort(double (*comparator)(T& a, T& b)) {
    bool swapped = true;

    while (swapped) {
      swapped = false;

      auto iterator = begin();
      for (int i = 0; i < _size - 1; i++, ++iterator) {
        if (comparator(*iterator, *(iterator + 1)) > 0) {
          swap(*iterator, *(iterator + 1));
          swapped = true;
        }
      }
    }
  }
};

struct Box {
  double _sum = 0;
  double* _bottles = nullptr;
  static double _max;
  static int size;

  Box() : _bottles(new double[size]) {
    for (auto i = 0; i < size; i++) {
      std::cin >> _bottles[i];
      _sum += _bottles[i];
    }

    if (_sum > _max) {
      _max = _sum;
    }
  }

  double sum() { return _sum; }

  double* begin() { return _bottles; }
  double* end() { return _bottles + size; }

  static double max() { return _max; }
};

double Box::_max = 0;
int Box::size = 0;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int boxesLength;
  int trucksLength;
  std::cin >> boxesLength >> Box::size >> trucksLength;

  Box bottlesBoxes[boxesLength];

  auto boxesListsLength = min(Box::size * 1000, boxesLength);

  List<Box*> boxesLists[boxesListsLength];

  for (auto& bottlesBox : bottlesBoxes) {
    int bucketIndex = (boxesListsLength - 1) -
                      bottlesBox.sum() * (boxesListsLength - 1) / Box::max();

    boxesLists[bucketIndex].push(&bottlesBox);
  }

  for (auto& boxesList : boxesLists) {
    boxesList.sort(
        [](auto& a, auto& b) -> double { return b->sum() - a->sum(); });

    for (auto& box : boxesList) {
      for (auto& bottle : *box) {
        std::cout << bottle << " ";
      }
      if (!--trucksLength) {
        return 0;
      }
      std::cout << '\n';
    }
  }
}