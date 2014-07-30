#ifndef __SIXSTAIR_SIX_STAIR_HPP__
#define __SIXSTAIR_SIX_STAIR_HPP__

#include "tube.hpp"

namespace SixStair {

class SixStair {
public:
  SixStair();
  SixStair(SixStair && stair);
  
  ~SixStair();
  
  SixStair & operator=(Stair && stair);
  
  void Flip();
  void TurnForward();
  void TurnBackward();

private:
  Tube * topFirst = NULL;
  Tube * topLast = NULL;
  Tube * bottomFirst = NULL;
  Tube * bottomLast = NULL;
  
  void ApplyGravity();
};

}

#endif
