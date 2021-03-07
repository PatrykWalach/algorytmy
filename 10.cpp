#include <iostream>

template <typename T>
void swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

class Person {
  int _id;
  int _priority;
  static int nextI;
  int _i;

 public:
  Person() {  // std::cin >> _id >> _priority;
  }
  Person(int id, int priority)
      : _i(nextI++),
        _id(id),
        _priority(priority) {  // std::cin >> _id >> _priority;
  }

  bool operator<(const Person& b) const {
    auto i = _priority - b._priority;
    if (i != 0) {
      return i < 0;
    }
    return (_i - b._i) < 0;
  }

  int id() const { return _id; }
};

int Person::nextI = 0;

template <typename T>
class Heap {
  int _size = 0;
  int _maxSize;
  T* _values;

  int _parent(int i) const { return (i - 1) / 2; }
  int _left(int i) const { return (i * 2) + 1; }
  int _right(int i) const { return _left(i) + 1; }

  void _normalizeChildren(int i) {
    auto leftIndex = _left(i);
    auto rightIndex = _right(i);

    auto biggestIndex = i;

    if (leftIndex < _size && (_values[leftIndex]) < (_values[biggestIndex])) {
      biggestIndex = leftIndex;
    }
    if (rightIndex < _size && (_values[rightIndex]) < (_values[biggestIndex])) {
      biggestIndex = rightIndex;
    }
    if (biggestIndex != i) {
      swap(_values[i], _values[biggestIndex]);
      _normalizeChildren(biggestIndex);
    }
  }

 public:
  Heap(int maxSize) : _maxSize(maxSize), _values(new T[maxSize]) {}

  void allocate(int maxSize) {
    if (maxSize <= _maxSize) {
      return;
    }

    auto values = new T[maxSize];

    for (auto i = 0; i < _size; i++) {
      values[i] = _values[i];
    }

    delete _values;

    _maxSize = maxSize;
    _values = values;
  }

  int size() { return _size; }

  T shift() {
    if (_size == 1) {
      return _values[--_size];
    }
    auto v = _values[0];
    _values[0] = _values[--_size];
    _normalizeChildren(0);
    return v;
  }

  void insert(T value) {
    auto i = _size++;
    _values[i] = value;

    for (auto parentIndex = _parent(i);
         i != 0 && (_values[i]) < (_values[parentIndex]);
         parentIndex = _parent(i)) {
      swap(_values[i], _values[parentIndex]);
      i = parentIndex;
    }
  }
};

template <typename T>
T min(T a, T b) {
  return a < b ? a : b;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int people;
  short days;
  std::cin >> people >> days;
  Heap<Person> queue(people);

  while (days--) {
    int peopleToday;
    std::cin >> peopleToday;

    queue.allocate(queue.size() + peopleToday);

    for (auto j = 0; j < peopleToday; j++) {
      int id, priority;
      std::cin >> id >> priority;
      queue.insert(Person(id, priority));
    }

    auto size = queue.size();
    
    for (auto k = 0; k < min(size, people); k++) {
      std::cout << queue.shift().id() << " ";
    }

    std::cout << '\n';
  }
}
