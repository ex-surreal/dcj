// Sample input 3, in CPP.

#include <cassert>
#include <cstdlib>

using namespace std;

long long GetStackSize() {
#ifdef STACK_SIZE
  return STACK_SIZE;
#endif
  return 1;
}

long long GetNumDiners() {
#ifdef NUM_DINERS
  return NUM_DINERS;
#endif
  return 1;
}

long long GetStackItem(long long i) {
  return (i^(1ll*rand()*rand())) % GetNumDiners();
}
