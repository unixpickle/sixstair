#ifndef __SIXSTAIR_CHECKER_HPP__
#define __SIXSTAIR_CHECKER_HPP__

#import "state.hpp"

namespace sixstair {

class Checker {
public:
  Checker(const State & s);
  
  bool IsTubeSolved(int size) const;
  bool AreDregsSolved(int depth) const;
  
private:
  const State & state;
};

}

#endif