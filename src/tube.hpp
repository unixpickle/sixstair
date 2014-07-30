#ifndef __SIXSTAIR_TUBE_HPP__
#define __SIXSTAIR_TUBE_HPP__

#include <cstdint>

namespace SixStair {

friend class SixStair;

class Tube {
public:
  typedef uint8_t Ball;
  
  Tube(uint8_t capacity);
  
  Ball & operator[](uint8_t);
  uint8_t GetCount();
  uint8_t GetCapacity();
  
  void PushEnd(Ball ball);
  Ball PopEnd();
  
protected:
  Tube * next = NULL;
  Tube * last = NULL;
  friend class SixStair;
  
private:
  Ball balls[6];
  uint8_t count;
  uint8_t start;
  uint8_t capacity;
};

}

#endif
