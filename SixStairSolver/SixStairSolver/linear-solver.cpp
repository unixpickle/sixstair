#include "linear-solver.hpp"
#include "checker.hpp"

namespace sixstair {

LinearSolver::LinearSolver(const State & a, int b, int c)
  : Search(a, b), count(c) {
}

bool LinearSolver::Solve() {
  Run();
  return didSolve;
}

const State & LinearSolver::GetSolvedState() const {
  return solveState;
}

const MoveList & LinearSolver::GetSolution() const {
  return solveMoves;
}

void LinearSolver::HandleNode(const State & state, const MoveList & moves) {
  if (!Checker(state).AreStepsSolved(count)) return;
  didSolve = true;
  solveState = state;
  solveMoves = moves;
  Stop();
}

}
