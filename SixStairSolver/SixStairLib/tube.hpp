#ifndef __SIXSTAIR_TUBE_HPP__
#define __SIXSTAIR_TUBE_HPP__

#include <cassert>

namespace sixstair {

class Tube {
public:
  inline Tube() : capacity(0) {}
  
  Tube(char capacity);
  Tube(const Tube &);
  Tube & operator=(const Tube &);
  
  bool operator==(const Tube &);
  bool operator!=(const Tube &);
  
  inline char GetLength() const {
    return length;
  }
  
  inline char GetCapacity() const {
    return capacity;
  }
  
  inline char & operator[](int idx) {
    assert(idx < length);
    return cells[idx];
  }
  
  inline char operator[](int idx) const {
    assert(idx < length);
    return cells[idx];
  }
  
  inline void Push(char c) {
    assert(length < capacity);
    cells[length++] = c;
  }
  
  char PopFront();
  void Flip();
  
  bool IsSolved() const;
  
private:
  char cells[6];
  char length = 0;
  char capacity;
};

}

#endif
