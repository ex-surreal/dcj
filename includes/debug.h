#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#ifdef DEBUG

class Debugger {
public:

  static void print() {}

  template <typename T>
  static void print(T t) {
    std::cerr << t << std::endl;
  }

  template<typename T, typename... Args>
  static void print(T t, Args... args) {
    std::cerr << t << " ";
    print(args...);
  }
};

#define debug(args...) Debugger::print(args)
#else
#define debug(args...)
#endif

#endif
