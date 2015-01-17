#ifndef __SIXSTAIR_PRINTING_STATE_SOLVER_HPP__
#define __SIXSTAIR_PRINTING_STATE_SOLVER_HPP__

#include "state-solver.hpp"

namespace sixstair {

class PrintingStateSolver : public StateSolver {
public:
  PrintingStateSolver(const State & start, int depth, const StateDesc & desc,
                      bool onlyOne);
  
  virtual void HandleSolved(const State & state, const MoveList & moves);
  
  inline bool GetDidSolve() const {
    return didSolve;
  }
  
private:
  bool onlyOne;
  bool didSolve = false;
};

}

#endif
