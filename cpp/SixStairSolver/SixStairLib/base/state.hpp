#ifndef __SIXSTAIR_STATE_HPP__
#define __SIXSTAIR_STATE_HPP__

#include "tube.hpp"
#include <string>

namespace sixstair {

class State {
public:
  State();
  State(const State &);
  State & operator=(const State &);
  
  bool operator==(const State &);
  bool operator!=(const State &);
  
  void TurnOnce(bool clockwise);
  void Flip();
  
  std::string ToString() const;
  std::string ToString(const std::string & newLine) const;
  
  inline bool IsFlipped() const {
    return flipped;
  }
  
  inline const Tube & GetTop(int idx) const {
    return top[idx];
  }
  
  inline const Tube & GetBottom(int idx) const {
    return bottom[idx];
  }
  
  inline Tube & GetTop(int idx) {
    return top[idx];
  }
  
  inline Tube & GetBottom(int idx) {
    return bottom[idx];
  }
  
private:
  Tube top[6];
  Tube bottom[6];
  bool flipped = false;
  
  void ApplyGravity();
};

}

#endif
