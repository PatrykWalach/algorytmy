#include <iostream>
  
  class Researcher {
    std::string _name;
    unsigned int _subordinatesMaxLength;
    unsigned int _subordinatesLength = 0;
    Researcher** _subordinates;
  
   public:
    Researcher() {
      std::cin >> _subordinatesMaxLength;
      std::cin >> _name;
    }
  
    void setSubordinates(Researcher** subordinates,
                         unsigned int subordinatesLength) {
      _subordinatesLength = subordinatesLength;
      _subordinates = subordinates;
    }
  
    unsigned int maxLength() const { return _subordinatesMaxLength; }
  
    void log() const {
      for (auto i = 0; i < _subordinatesLength; i++) {
        _subordinates[i]->log();
      }
      std::cout << _name << '\n';
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
  
    int researchersLength;
    std::cin >> researchersLength;
  
    Researcher* researchers[researchersLength];
    researchers[0] = new Researcher();
  
    for (auto i = 0, j = 1; j < researchersLength; i++) {
      auto node = researchers[i];
      auto subordinatesLength = min((int)node->maxLength(), researchersLength - j);
  
      node->setSubordinates(researchers + j, subordinatesLength);
  
      for (auto k = 0; k < subordinatesLength; k++, j++) {
        researchers[j] = new Researcher();
      }
    }
  
    researchers[0]->log();
  }