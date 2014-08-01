#include "search.hpp"
#include "checker.hpp"

namespace sixstair {

Search::Search(const State & s, int d) : start(s), depth(d) {
}

void Search::Run() {
  stopped = false;
  ExpandAndSearch(start, MoveList(), false, false);
}

void Search::Stop() {
  stopped = true;
}

void Search::ExpandAndSearch(const State & state, const MoveList & moves,
                             bool hasMovedEmpty, bool hasFlipped) {
  if (moves.GetLength() == depth)  {
    HandleNode(state, moves);
    return;
  }
  
  State newState(state);
  MoveList newMoves(moves);
  
  // branch into an F move
  if (!hasFlipped) {
    newState.Flip();
    newMoves.Push(MoveList::Move(true, 0));
    ExpandAndSearch(state, moves, false, true);
    if (stopped) return;
  }
  
  if (hasMovedEmpty) return;
  
  if (Checker(state).IsTopEmpty()) {
    // top is empty, thus direction doesn't matter
    newState = state;
    newMoves = moves;
    newMoves.Push(MoveList::Move(false, 0));
    
    for (int i = 1; i < 6; i++) {
      newMoves[newMoves.GetLength() - 1] = MoveList::Move(false, i);
      newState.TurnOnce(true);
      ExpandAndSearch(newState, newMoves, true, false);
      if (stopped) return;
    }
  } else {
    newState = state;
    newMoves = moves;
    newMoves.Push(MoveList::Move(false, 0));
    
    // clockwise turns
    for (int i = 1; i < 6; i++) {
      newMoves[newMoves.GetLength() - 1] = MoveList::Move(false, i);
      newState.TurnOnce(true);
      ExpandAndSearch(newState, newMoves, true, false);
      if (stopped) return;
    }
    
    // counter-clockwise turns
    newState = state;
    for (int i = 1; i < 6; i++) {
      newMoves[newMoves.GetLength() - 1] = MoveList::Move(false, -i);
      newState.TurnOnce(false);
      ExpandAndSearch(newState, newMoves, false, false);
      if (stopped) return;
    }
  }
}

}
