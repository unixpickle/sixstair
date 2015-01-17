#include "move-list.hpp"
#include <sstream>

namespace sixstair {

MoveList::MoveList() {
}

MoveList::MoveList(const MoveList & m) : length(m.length) {
  for (int i = 0; i < length; i++) {
    moves[i] = m.moves[i];
  }
}

std::string MoveList::ToString() const {
  std::stringstream str("");
  
  for (int i = 0; i < GetLength(); ++i) {
    if (i != 0) str << " ";
    if ((*this)[i].IsFlip()) {
      str << "F";
    } else {
      str << "T" << (int)(*this)[i].GetTurns();
    }
  }
  
  return str.str();
}

}
