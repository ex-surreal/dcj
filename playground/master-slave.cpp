#ifdef DEBUG
#include <debug.h>
#define debug(args...) Debugger::print(args)
#else
#define debug(args...)
#endif

#include <iostream>
#include <message.h>

#define MASTER_NODE 0
#define is_master(id) ((id) == MASTER_NODE)

#ifdef INPUT
#include INPUT
#else
// #include "input_file.h"
#endif

using namespace std;

void process_master(
    const int nodes
) {
  for (int node = 0; node < nodes; node ++) {
    if (is_master(node)) continue;
    // Task distribution here
    //

    // Send message to slaves
    //
    // NOTE: Slaves are waiting for messages, so we have to send message
    //       to every slave. Even if the input is small and we don't need
    //       all the slaves.
    // PutInt();
    Send(node);
  }
  for (int node = 0; node < nodes; node ++) {
    if (is_master(node)) continue;
    // Receive result from any slave
    Receive(-1);
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

// Only master talks to slaves

int main() {
  int id = MyNodeId();
  int nodes = NumberOfNodes();
  if (is_master(id)) process_master(nodes);
  else process_slave(MASTER_NODE);
  return 0;
}
