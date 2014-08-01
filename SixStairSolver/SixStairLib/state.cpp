#include "state.hpp"
#include <sstream>

namespace sixstair {

State::State() {
  for (int i = 0; i < 6; i++) {
    bottom[i] = Tube(i + 1);
    top[i] = Tube(i + 1);
    for (int j = 0; j <= i; j++) {
      bottom[i].Push(i + 1);
    }
  }
}

State::State(const State & s) : flipped(s.flipped) {
  for (int i = 0; i < 6; i++) {
    bottom[i] = s.bottom[i];
    top[i] = s.top[i];
  }
}

State & State::operator=(const State & s) {
  flipped = s.flipped;
  for (int i = 0; i < 6; i++) {
    bottom[i] = s.bottom[i];
    top[i] = s.top[i];
  }
  return *this;
}

bool State::operator==(const State & s) {
  if (flipped != s.flipped) return false;
  for (int i = 0; i < 6; i++) {
    if (top[i] != s.top[i]) return false;
    if (bottom[i] != s.bottom[i]) return false;
  }
  return true;
}

bool State::operator!=(const State & s) {
  return !(*this == s);
}

void State::TurnOnce(bool clockwise) {
  if (clockwise) {
    Tube last(top[0]);
    for (int i = 5; i >= 0; --i) {
      Tube temp(top[i]);
      top[i] = last;
      last = temp;
    }
  } else {
    Tube last(top[5]);
    for (int i = 0; i < 6; ++i) {
      Tube temp(top[i]);
      top[i] = last;
      last = temp;
    }
  }
  
  ApplyGravity();
}

void State::Flip() {
  flipped = !flipped;
  
  for (int i = 0; i < 6; ++i) {
    Tube t1(top[i]);
    top[i] = bottom[i];
    bottom[i] = t1;
    
    bottom[i].Flip();
    top[i].Flip();
  }
  
  for (int i = 0; i < 3; ++i) {
    Tube t(top[i]);
    top[i] = top[5 - i];
    top[5 - i] = t;
    
    t = bottom[i];
    bottom[i] = bottom[5 - i];
    bottom[5 - i] = t;
  }
  
  ApplyGravity();
}

std::string State::ToString() const {
  return ToString("\n");
}

std::string State::ToString(const std::string & newLine) const {
  std::stringstream str("");
  
  for (int j = 0; j < 7; ++j) {
    int idx = 6 - j;
    for (int i = 0; i < 6; ++i) {
      const Tube & t = top[i];
      if (t.GetCapacity() == idx) {
        str << " _ ";
      } else if (t.GetCapacity() < idx) {
        str << "   ";
      } else if (t.GetLength() > idx) {
        str << "|" << (int)t[idx] << "|";
      } else {
        str << "| |";
      }
    }
    str << newLine;
  }
  
  str << "------------------" << newLine;
  
  for (int idx = 0; idx < 7; ++idx) {
    for (int i = 0; i < 6; i++) {
      const Tube & t = bottom[i];
      int baseIdx = t.GetCapacity() - idx - 1;
      if (t.GetCapacity() == idx) {
        str << " - ";
      } else if (t.GetCapacity() < idx) {
        str << "   ";
      } else if (t.GetLength() > baseIdx) {
        str << "|" << (int)t[baseIdx] << "|";
      } else {
        str << "| |";
      }
    }
    if (idx != 6) str << newLine;
  }
  
  return str.str();
}

void State::ApplyGravity() {
  for (int i = 0; i < 6; i++) {
    Tube & t = top[i];
    Tube & b = bottom[i];
    while (t.GetLength() > 0 && b.GetLength() < b.GetCapacity()) {
      b.Push(t.PopFront());
    }
  }
}

}
