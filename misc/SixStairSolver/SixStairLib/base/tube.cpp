#include "tube.hpp"

namespace sixstair {

Tube::Tube(char _capacity) : capacity(_capacity) {
  
}

Tube::Tube(const Tube & t) : capacity(t.capacity), length(t.length) {
  for (char i = 0; i < length; i++) {
    cells[i] = t.cells[i];
  }
}

Tube & Tube::operator=(const Tube & t) {
  capacity = t.capacity;
  length = t.length;
  for (char i = 0; i < length; ++i) {
    cells[i] = t.cells[i];
  }
  return *this;
}

bool Tube::operator==(const Tube & t) {
  if (capacity != t.capacity || length != t.length) return false;
  for (int i = 0; i < length; i++) {
    if (t.cells[i] != cells[i]) return false;
  }
  return true;
}

bool Tube::operator!=(const Tube & t) {
  return !(*this == t);
}

char Tube::PopFront() {
  assert(length > 0);
  char c = cells[0];
  for (char i = 0; i < length - 1; ++i) {
    cells[i] = cells[i + 1];
  }
  --length;
  return c;
}

void Tube::Flip() {
  for (char i = 0; i < length / 2; i++) {
    char temp = cells[i];
    cells[i] = cells[length - i - 1];
    cells[length - i - 1] = temp;
  }
}

bool Tube::IsSolved() const {
  if (length != capacity) return false;
  for (int i = 0; i < length; i++) {
    if (cells[i] != length) return false;
  }
  return true;
}

}
