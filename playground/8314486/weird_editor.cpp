#ifdef DEBUG
#include <debug.h>
#define debug(args...) Debugger::print(args)
#else
#define debug(args...)
#endif

#include <iostream>
#include <message.h>
#include "weird_editor.h"

#define MOD 1000000007

using namespace std;

template <class type>
void process_linear_segment(
    const int id,
    const int nodes,
    const type N,
    int * const c,
    int * const v,
    int * const t
) {
  type s = (N + nodes-1) / nodes;
  type l = id*s;
  type r = min(l+s, N);
  for (int i = 1; i <= 9; i ++) {
    c[i] = v[i] = 0;
    t[i] = 1;
  }
  int st[10], top = 0;
  for (int i = l; i < r; i ++) {
    long long d = GetDigit(i);
    while (top > 0 && d > st[top-1]) {
      top --;
      c[st[top]] = v[st[top]] = 0;
      t[st[top]] = 1;
    }
    if (c[d] == 0) st[top ++] = d;
    c[d] ++;
    v[d] = (10ll*v[d] + d) % MOD;
    t[d] = 10ll*t[d] % MOD;
  }
}

void receive(
  const int from,
  int * const c,
  int * const v,
  int * const t
) {
  Receive(from);
  for (int d = 9; d >= 1; d --) {
    int cc = GetInt(from);
    int vv = GetInt(from);
    int tt = GetInt(from);
    if (cc == 0) continue;
    c[d] += cc;
    v[d] = (1ll*v[d]*tt + vv) % MOD;
    t[d] = 1ll*t[d]*tt % MOD;
    for (int j = d-1; j >= 1; j--) {
      c[j] = v[j] = 0;
      t[j] = 1;
    }
  }
}

void send(
  const int to,
  const int * c,
  const int * v,
  const int * t
) {
  for (int d = 9; d >= 1; d --) {
    PutInt(to, c[d]);
    PutInt(to, v[d]);
    PutInt(to, t[d]);
  }
  Send(to);
}

// head -> ... -> tail
// head: who prints final result, don't send to anyone
// tail: who doesn't receive from anyone

#define is_head(id) ((id) == 0)
#define is_tail(id) ((id) == nodes-1)
#define send_to(id) ((id) - 1)
#define receive_from(id) ((id) + 1)

#include <ctime>

int main() {
  int id = MyNodeId();
  int nodes = NumberOfNodes();
  long long N = GetNumberLength();
  int c[10], v[10], t[10];
  int start = clock();
  process_linear_segment(id, nodes, N, c, v, t);
  debug("process: ", 1.0*(clock()-start)/CLOCKS_PER_SEC);
  if (!is_tail(id)) {
    receive(
      receive_from(id), c, v, t
    );
  }
  if (!is_head(id)) {
    send(
      send_to(id), c, v, t
    );
  } else {
    int ans = 0, k = N;
    for (int d = 9; d >= 1; d --) {
      ans = (1ll*ans*t[d] + v[d]) % MOD;
      k -= c[d];
    }
    int b = 10;
    while (k > 0) {
      if (k&1) ans = 1ll*ans*b % MOD;
      b = 1ll*b*b % MOD;
      k >>= 1;
    }
    cout << ans << endl;
  }
  return 0;
}
