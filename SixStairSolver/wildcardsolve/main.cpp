#include <iostream>
#include "printing-state-solver.hpp"
#include "input.hpp"

using namespace sixstair;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

StateSolver::StateDesc ReadDescription();

int main(int argc, const char * argv[]) {
  if (argc > 2) {
    cerr << "Usage: wildcardsolve [--only-one]" << endl;
    return 1;
  }
  
  bool onlyOne = false;
  if (argc == 2 && strcmp(argv[1], "--only-one") == 0) {
    onlyOne = true;
  } else if (argc == 2) {
    cerr << "Usage: tubesolve [--only-one]" << endl;
    return 1;
  }
  
  State * s = ReadState(cout, cin, cerr);
  if (!s) {
    cerr << endl;
    return 1;
  }
  State state(*s);
  delete s;
  
  cout << "Solving: " << state.ToString("\n         ") << endl;
  
  cout << "--- Enter solved state ---" << endl << endl;
  
  StateSolver::StateDesc desc(ReadDescription());
  
  int depth = 0;
  while (1) {
    cout << "exploring depth " << depth << " ..." << endl;
    PrintingStateSolver solver(state, depth, desc, onlyOne);
    solver.Run();
    if (solver.GetDidSolve() && onlyOne) return 0;
    ++depth;
  }
  
  return 0;
}

StateSolver::StateDesc ReadDescription() {
  StateSolver::StateDesc desc;
  
  cout << "** Use asterisk (*) for wildcard **" << endl;
  
  int idx = 0;
  for (int i = 0; i < 6; ++i) {
    cout << "Enter bottom tube " << i << ": ";
    std::string line;
    std::getline(cin, line);
    
    if (line.length() > 0) {
      if (line[line.length() - 1] == '\n') {
        line.replace(line.length() - 1, 1, "");
        if (line.length() > 0) {
          if (line[line.length() - 1] == '\r') {
            line.replace(line.length() - 1, 1, "");
          }
        }
      }
    }
    
    if (line.length() != i + 1) {
      cerr << "invalid length of tube " << i + 1;
      exit(1);
    }
    
    for (int j = 0; j <= i; ++j) {
      char c = line[j];
      char & dest = desc.spaces[idx++];
      if (c == '1' || c == 'D') dest = 1;
      else if (c == '2' || c == 'W') dest = 2;
      else if (c == '3' || c == 'B') dest = 3;
      else if (c == '4' || c == 'Y') dest = 4;
      else if (c == '5' || c == 'G') dest = 5;
      else if (c == '6' || c == 'R') dest = 6;
      else if (c == '*') dest = 0;
      else {
        cerr << "invalid character " << c << " in tube " << i + 1;
        exit(1);
      }
    }
  }
  
  return desc;
}
