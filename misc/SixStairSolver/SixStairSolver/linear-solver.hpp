#ifndef __SIXSTAIR_LINEAR_SOLVER_HPP__
#define __SIXSTAIR_LINEAR_SOLVER_HPP__

#include "search.hpp"

namespace sixstair {

class LinearSolver : protected Search {
public:
  LinearSolver(const State & start, int depth, int count);
  
  bool Solve();
  const State & GetSolvedState() const;
  const MoveList & GetSolution() const;
  
protected:
  virtual void HandleNode(const State & state, const MoveList & moves);
  
private:
  State solveState;
  MoveList solveMoves;
  bool didSolve = false;
  int count;
};

}

#endif
