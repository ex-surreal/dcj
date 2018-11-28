#ifdef DEBUG
#include <debug.h>
#define debug(args...) Debugger::print(args)
#else
#define debug(args...)
#endif

#include <iostream>
#include <message.h>

#define is_master(id) ((id) == 0)

using namespace std;

void process_master(
    const int nodes
) {
  for (int node = 0; node < nodes; node ++) {
    if (is_master(node)) continue;
    // Task distribution here
    //

    // PutInt();
    Send(node);
  }
  for (int node = 0; node < nodes; node ++) {
    if (is_master(node)) continue;
    // Receive result from slave
    Receive(node);
    // GetInt();

    // Combine results here
    //
  }
  // cout << ans;
}

void process_slave(
  const int master
) {
  // Receive task from master
  Receive(master);
  // GetInt();

  // Do task here
  //

  // Send result back to master
  // PutInt()
  Send(master);
}

// Only master talkes to slaves

int main() {
  int id = MyNodeId();
  int nodes = NumberOfNodes();
  if (is_master(id)) process_master(nodes);
  else process_slave(id);
  return 0;
}
