#include "input.hpp"

namespace sixstair {

State * ReadState(std::ostream & output, std::istream & input,
                  std::ostream & error) {
  State s;
  
  for (int i = 0; i < 6; ++i) {
    output << "Enter bottom tube " << i << ": ";
    std::string line;
    std::getline(input, line);
    
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
      error << "invalid length of tube " << i + 1;
      return nullptr;
    }
    
    Tube & t = s.GetBottom(i);
    for (int j = 0; j <= i; ++j) {
      char c = line[j];
      if (c == '1' || c == 'D') t[j] = 1;
      else if (c == '2' || c == 'W') t[j] = 2;
      else if (c == '3' || c == 'B') t[j] = 3;
      else if (c == '4' || c == 'Y') t[j] = 4;
      else if (c == '5' || c == 'G') t[j] = 5;
      else if (c == '6' || c == 'R') t[j] = 6;
      else {
        error << "invalid character " << c << " in tube " << i + 1;
        return nullptr;
      }
    }
  }
  
  return new State(s);
}

}
