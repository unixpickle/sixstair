#ifndef __SIXSTAIR_PRINTING_TUBE_SOLVER_HPP__
#define __SIXSTAIR_PRINTING_TUBE_SOLVER_HPP__

#include "tube-solver.hpp"

namespace sixstair {

class PrintingTubeSolver : public TubeSolver {
public:
  PrintingTubeSolver(const State & start, int depth, const TubeList & tubes,
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
