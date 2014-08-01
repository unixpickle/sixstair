#ifndef __SIXSTAIR_MOVE_LIST_HPP__
#define __SIXSTAIR_MOVE_LIST_HPP__

#include <cassert>
#include <string>

namespace sixstair {

class MoveList {
public:
  struct Move {
    char isFlip : 1;
    char turns : 4;
    
    Move(bool flip, int count)
      : isFlip(flip ? 1 : 0), turns((char)(count + 5)) {
    }
    
    inline bool IsFlip() const {
      return isFlip == 1;
    }
    
    inline int GetTurns() const {
      return (int)turns - 5;
    }
  };
  
  MoveList();
  MoveList(const MoveList &);
  
  inline int GetLength() const {
    return length;
  }
  
  inline Move operator[](int idx) const {
    return moves[idx];
  }
  
  inline void Push(const Move & m) {
    assert(length < 0x20);
    moves[length++] = m;
  }
  
  std::string ToString() const;
  
private:
  Move moves[0x20];
  int length;
};

}

#endif
