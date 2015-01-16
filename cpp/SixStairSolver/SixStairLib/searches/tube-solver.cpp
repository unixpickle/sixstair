#include "tube-solver.hpp"
#include "checker.hpp"

namespace sixstair {

TubeSolver::TubeSolver(const State & s, int d, const TubeList & t)
  : super(s, d), tubes(t) {
}

void TubeSolver::HandleNode(const State & state, const MoveList & moves) {
  for (int i = 0; i < 6; i++) {
    const Tube & t = state.GetBottom(i);
    if (!HasTube(t.GetCapacity())) continue;
    if (!t.IsSolved()) return;
  }
  HandleSolved(state, moves);
}

bool TubeSolver::HasTube(char tube) {
  for (int i = 0; i < tubes.count; i++) {
    if (tubes.tubes[i] == tube) return true;
  }
  return false;
}

}
