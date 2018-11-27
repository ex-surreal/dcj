#include <debug.h>
#include <message.h>
#include "pancakes.h"
#include <iostream>

using namespace std;

pair <long long, long long> get_my_segment(const int my_id, const int num_nodes, const long long N) {
  long long s = (N + num_nodes-1) / num_nodes;
  return {my_id*s, min(my_id*s+s, N)};
}

int main() {
  int num_nodes = NumberOfNodes();
  int my_id = MyNodeId();
  long long N = GetStackSize();
  long long my_start, my_end;
  tie(my_start, my_end) = get_my_segment(my_id, num_nodes, N);
  long long my_ans = 0ll;
  long long first = N;
  long long last = -1ll;
  for (auto i = my_start; i < my_end; i ++) {
    auto item = GetStackItem(i);
    if (first == N) first = item;
    if (item < last) my_ans ++;
    last = item;
  }
  if (my_id > 0) {
    Receive(my_id-1);
    my_ans += GetLL(my_id-1);
    if (first < GetLL(my_id-1)) my_ans ++;
  }
  if (my_id < num_nodes-1) {
    PutLL(my_id+1, my_ans);
    PutLL(my_id+1, last);
    Send(my_id+1);
  } else {
    cout << my_ans + 1 << endl;
  }
  return 0;
}
