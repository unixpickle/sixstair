#include "state-solver.hpp"

namespace sixstair {

StateSolver::StateSolver(const State & s, int d,
                         const StateDesc & _desc) : super(s, d), desc(_desc) {
}

void StateSolver::HandleNode(const State & state, const MoveList & moves) {
  if (MatchesDesc(state)) {
    HandleSolved(state, moves);
  }
}

bool StateSolver::MatchesDesc(const State & state) {
  int idx = 0;
  int offset;
  for (offset = 0; offset < 6; ++offset) {
    if (state.GetBottom(offset).GetCapacity() == 1) break;
  }
  for (int i = 0; i < 6; ++i) {
    const Tube & t = state.GetBottom((i + offset) % 6);
    for (int j = 0; j <= i; ++j) {
      char space = desc.spaces[idx++];
      if (!space) continue;
      if (t.GetLength() <= j) return false;
      if (t[j] != space) return false;
    }
  }
  return true;
}

}
