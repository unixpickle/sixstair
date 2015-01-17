#include "printing-tube-solver.hpp"
#include <iostream>

namespace sixstair {

PrintingTubeSolver::PrintingTubeSolver(const State & a, int b,
                                       const TubeList & c, bool d)
  : TubeSolver(a, b, c), onlyOne(d) {
}
  
void PrintingTubeSolver::HandleSolved(const State & state,
                                      const MoveList & moves) {
  std::cout << "Found solution: " << moves.ToString() << std::endl;
  didSolve = true;
  if (onlyOne) Stop();
}

}
