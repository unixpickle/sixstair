#include "tube.hpp"
#include <cassert>

namespace SixStair {

Tube::Tube(uint8_t _cap) : capacity(_cap) {
  assert(capacity <= 6);
}

Ball & Tube::operator[](uint8_t i) {
  assert(i < count);
  return balls[i];
}

uint8_t Tube::GetCount() {
  return count;
}

uint8_t Tube::GetCapacity() {
  return capacity;
}

void Tube::PushEnd(Ball ball) {
  assert(count < capacity);
  balls[count++] = ball;
}

Ball Tube::PopEnd() {
  assert(count > 0);
  return balls[--count];
}

}
