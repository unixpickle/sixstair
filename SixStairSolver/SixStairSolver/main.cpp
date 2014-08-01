#include <iostream>
#include "linear-solver.hpp"
#include "input.hpp"

using namespace sixstair;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

bool SolveAmount(State & s, int & numSolved, int maxDepth);

int main(int argc, const char * argv[]) {
  if (argc > 2) {
    cerr << "Usage: SixStairSolver [maxDepth (10)]" << endl;
    return 1;
  }
  
  int maxDepth = 10;
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
    if (!SolveAmount(state, numSolved, tempMaxDepth)) {
      tempMaxDepth++;
    } else {
      tempMaxDepth = maxDepth;
    }
  }
  
  return 0;
}

bool SolveAmount(State & s, int & numSolved, int maxDepth) {
  for (int amount = 21; amount > numSolved; --amount) {
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
