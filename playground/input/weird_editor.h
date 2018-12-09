// Sample input 3, in CPP.

#include <cassert>
#include <cstdlib>
#include <ctime>

#ifndef NUMBER_LENGTH
#define NUMBER_LENGTH 9
#endif

long long GetNumberLength() {
  return NUMBER_LENGTH;
}

long long GetDigit(long long i) {
  return (i+1) % 10;
  /* srand(clock()); */
  /* if (i == 0) return rand() % 9 + 1; */
  /* return rand() % 10; */
}
