#ifdef DEBUG
#include <debug.h>
#define debug(args...) Debugger::print(args)
#else
#define debug(args...)
#endif

#include <iostream>
#include <message.h>

using namespace std;

template <class type>
void process_linear_segment(
    const int id,
    const int nodes,
    const type N
) {
  type s = (N + nodes-1) / nodes;
  type l = id*s;
  type r = min(l+s, N);
  // This node's segment: [l, r)
}

void receive(
  const int from
) {
  Receive(from);
  // GetLL(from)
}

void send(
  const int to
) {
  // PutLL(to, val)
  Send(to);
}

int main() {
  int id = MyNodeId();
  int nodes = NumberOfNodes();
  // long long N = GetN();
  return 0;
}
