#ifndef __SIXSTAIR_INPUT_HPP__
#define __SIXSTAIR_INPUT_HPP__

#include <iostream>
#include "state.hpp"

namespace sixstair {

State * ReadState(std::ostream & output, std::istream & input,
                  std::ostream & error);

}

#endif
