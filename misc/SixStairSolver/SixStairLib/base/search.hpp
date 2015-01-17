#ifndef __SIXSTAIR_SEARCH_HPP__
#define __SIXSTAIR_SEARCH_HPP__

#include "state.hpp"
#include "move-list.hpp"

namespace sixstair {

class Search {
public:
  Search(const State & start, int depth);
  
  void Run();
  void Stop();
  
protected:
  virtual void HandleNode(const State & state, const MoveList & moves) = 0;
  
private:
  State start;
  int depth;
  bool stopped;
  
  void ExpandAndSearch(const State & state, const MoveList & moves,
                       bool hasMovedEmpty, bool hasFlipped);
};

}

#endif
