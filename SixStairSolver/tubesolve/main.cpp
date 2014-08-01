#include "printing-tube-solver.hpp"
#include "input.hpp"
#include <iostream>
#include <sstream>

using namespace sixstair;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

int main(int argc, const char * argv[]) {
  if (argc < 2 || argc > 8) {
    cerr << "Usage: tubesolve [--only-one] <tube> [tube2 ...]" << endl;
    return 1;
  }
  
  int start = 1;
  bool onlyOne = false;
  if (strcmp(argv[1], "--only-one") == 0) {
    onlyOne = true;
    start = 2;
  }
  
  if (start == argc) {
    cerr << "Usage: tubesolve [--only-one] <tube> [tube2 ...]" << endl;
    return 1;
  }
  
  std::stringstream err("");
  State * s = ReadState(cout, cin, err);
  if (!s) {
    cerr << err.str() << endl;
    return 1;
  }
  State state(*s);
  delete s;
  
  cout << "Solving: " << state.ToString("\n         ") << endl;
  
  TubeSolver::TubeList tubes;
  tubes.count = 0;
  for (int i = start; i < argc; i++) {
    tubes.tubes[tubes.count++] = atoi(argv[i]);
  }
  
  int depth = 0;
  while (1) {
    cout << "exploring depth " << depth << " ..." << endl;
    PrintingTubeSolver solver(state, depth, tubes, onlyOne);
    solver.Run();
    if (solver.GetDidSolve() && onlyOne) return 0;
    ++depth;
  }
  
  return 0;
}

