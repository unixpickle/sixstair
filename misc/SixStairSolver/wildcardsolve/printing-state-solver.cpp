#include "printing-state-solver.hpp"
#include <iostream>

namespace sixstair {

PrintingStateSolver::PrintingStateSolver(const State & a, int b,
                                         const StateDesc & c, bool d)
  : StateSolver(a, b, c), onlyOne(d) {
}

void PrintingStateSolver::HandleSolved(const State & state,
                                       const MoveList & moves) {
  std::cout << "Found solution: " << moves.ToString() << std::endl;
  std::cout << "Result: " << state.ToString("\n        ") << std::endl;
  didSolve = true;
  if (onlyOne) Stop();
}

}
