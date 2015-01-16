#ifndef __SIXSTAIR_STATE_SOLVER_HPP__
#define __SIXSTAIR_STATE_SOLVER_HPP__

#include "search.hpp"

namespace sixstair {

class StateSolver : public Search {
public:
  typedef Search super;
  
  struct StateDesc {
    char spaces[21]; // zero is any tile
  };
  
  StateSolver(const State & start, int depth, const StateDesc & desc);
  
  virtual void HandleSolved(const State & state, const MoveList & moves) = 0;
  
protected:
  virtual void HandleNode(const State & state, const MoveList & moves);
  bool MatchesDesc(const State & state);
  
private:
  StateDesc desc;
};

}

#endif
