#include <iostream>
#include "linear-solver.hpp"
#include "input.hpp"

using namespace sixstair;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

bool SolveAmount(State & s, int & numSolved, int maxDepth, bool upwards);

int main(int argc, const char * argv[]) {
  if (argc > 2) {
    cerr << "Usage: SixStairSolver [maxDepth (9)]" << endl;
    return 1;
  }
  
  int maxDepth = 9;
  if (argc == 2) {
    maxDepth = atoi(argv[1]);
  }
  
  State * s = ReadState(cout, cin, cerr);
  if (!s) {
    cerr << endl;
    return 1;
  }
  State state(*s);
  delete s;
  
  int numSolved = 0;
  int tempMaxDepth = maxDepth;
  while (numSolved < 21) {
    bool upwards = tempMaxDepth != maxDepth;
    if (!SolveAmount(state, numSolved, tempMaxDepth, upwards)) {
      tempMaxDepth++;
    } else {
      tempMaxDepth = maxDepth;
    }
  }
  
  return 0;
}

bool SolveAmount(State & s, int & numSolved, int maxDepth, bool upwards) {
  int step, start;
  if (upwards) {
    step = 1;
    start = numSolved + 1;
  } else {
    step = -1;
    start = 21;
  }
  for (int amount = start; amount > numSolved && amount < 22; amount += step) {
    for (int i = 0; i <= maxDepth; ++i) {
      LinearSolver solver(s, i, amount);
      if (solver.Solve()) {
        s = solver.GetSolvedState();
        numSolved = amount;
        cout << "Solve " << amount << ": " << solver.GetSolution().ToString()
          << " (" << solver.GetSolution().GetLength() << " moves)" << endl;
        return true;
      }
    }
  }
  return false;
}
