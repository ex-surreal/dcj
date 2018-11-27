#ifdef DEBUG
#include <debug.h>
#define debug(args...) Debugger::print(args)
#else
#define debug(args...)
#endif

#include <iostream>
#include <message.h>

using namespace std;

int main() {
  return 0;
}
