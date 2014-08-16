#include "checker.hpp"

namespace sixstair {

Checker::Checker(const State & s) : state(s) {
}

bool Checker::IsTubeSolved(int size) const {
  for (int i = 0; i < 6; i++) {
    const Tube & t = state.GetBottom(i);
    if (t.GetCapacity() != size) continue;
    return t.IsSolved();
  }
  return false;
}

bool Checker::AreDregsSolved(int depth) const {
  if (state.IsFlipped()) return false;
  for (int i = 0; i < 6; i++) {
    const Tube & t = state.GetBottom(i);
    int req = t.GetCapacity() > depth ? depth : t.GetCapacity();
    if (req > t.GetLength()) return false;
    for (int j = 0; j < req; j++) {
      if (t[j] != t.GetCapacity()) return false;
    }
  }
  return true;
}

bool Checker::IsTopEmpty() const {
  for (int i = 0; i < 6; i++) {
    if (state.GetTop(i).GetLength()) return false;
  }
  return true;
}

bool Checker::AreStepsSolved(int ballCount) const {
  if (state.IsFlipped()) return false;
  
  int idx = 0;
  
  int offset;
  for (offset = 0; offset < 6; ++offset) {
    if (state.GetBottom(offset).GetCapacity() == 1) break;
  }
  
  for (int i = 0; i < 6; ++i) {
    const Tube & t = state.GetBottom((i + offset) % 6);
    for (int j = 0; j <= i; ++j) {
      if (idx++ == ballCount) return true;
      if (t.GetLength() <= j) return false;
      if (t[j] != i + 1) return false;
    }
  }
  return true;
}

}
