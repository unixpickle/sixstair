#ifndef __SIXSTAIR_TUBE_SOLVER_HPP__
#define __SIXSTAIR_TUBE_SOLVER_HPP__

#include "search.hpp"

namespace sixstair {

class TubeSolver : public Search {
public:
  typedef Search super;
  
  struct TubeList {
    char count;
    char tubes[6];
  };
  
  TubeSolver(const State & start, int depth, const TubeList & tubes);
  
  virtual void HandleSolved(const State & state, const MoveList & moves) = 0;
  
protected:
  virtual void HandleNode(const State & state, const MoveList & moves);
  bool HasTube(char tube);
  
private:
  TubeList tubes;
};

}

#endif
