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

// head -> ... -> tail
// head: who prints final result, don't send to anyone
// tail: who doesn't receive from anyone

#define is_head(id) ((id) == 0)
#define is_tail(id) ((id) == nodes-1)
#define send_to(id) ((id) - 1)
#define receive_from(id) ((id) + 1)

int main() {
  int id = MyNodeId();
  int nodes = NumberOfNodes();
  // long long N = GetN();
  // process_linear_segment(id, nodes, N);
  if (!is_tail(id)) {
    receive(
      receive_from(id)
    );
  }
  if (!is_head(id)) {
    send(
      send_to(id)
    );
  } else {
    // cout << ans << endl;
  }
  return 0;
}
