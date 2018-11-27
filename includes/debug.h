#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#ifdef DEBUG
class Debugger {
  bool first;
public:
  Debugger() { first = true; }
  ~Debugger() { std::cerr << std::endl; }
  template <class type> Debugger& operator , (const type & val) {
    if (!first) std::cerr << " ";
    first = false;
    return *this;
  }
};
#define debug(args...) (Debugger()), args
#else
#define debug(args...)
#endif

#endif
