#ifdef DEBUG
#include <debug.h>
#define debug(args...) Debugger::print(args)
#else
#define debug(args...)
#endif

#include <iostream>
#include <message.h>
#include <cassert>

#ifdef TEST
#include "test_todd_and_steven.h"
#define RUN_TEST 1
#else
#include "todd_and_steven.h"
#define RUN_TEST 0
#endif

#define MASTER_NODE 0
#define is_master(id) ((id) == MASTER_NODE)
#define MOD 1000000007

// 15 23
// 4 8 16 42

using namespace std;

pair <int, int> b_search(int l1, int r1, int l2, int r2, int k) {
  k = min(r1-l1+1+r2-l2+1, k);
  while (l1 <= r1 && l2 <= r2) {
    int m1 = (l1+r1) >> 1;
    int m2 = (l2+r2) >> 1;
    if (m1+m2-l1-l2+2 > k) {
      if (GetStevenValue(m2) > GetToddValue(m1)) r2 = m2-1;
      else r1 = m1-1;
    } else {
      if (GetStevenValue(m2) < GetToddValue(m1)) {
        k -= m2-l2+1;
        l2 = m2+1;
      } else {
        k -= m1-l1+1;
        l1 = m1+1;
      }
    }
  }
  if (r1 < l1) return {r1, l2+k-1};
  if (r2 < l2) return {l1+k-1, r2};
  return {r1, r2};
}

void process_master(
    const int nodes
) {
  int slaves = nodes - 1;

  // Task distribution here
  int odd_length = GetToddLength();
  int even_length = GetStevenLength();
  int total_size = (odd_length+even_length);
  int block_size =  (total_size+slaves-1) / slaves;
  int l1 = 0, l2 = 0, slave = 0;

  for (int i = 0; i < total_size; i += block_size, slave ++) {
    if (is_master(slave)) slave ++;
    int r1, r2;
    tie(r1, r2) = b_search(
      l1, min(l1+block_size, odd_length)-1,
      l2, min(l2+block_size, even_length)-1,
      block_size
    );
    PutInt(slave, l1);
    PutInt(slave, r1);
    PutInt(slave, l2);
    PutInt(slave, r2);
    PutInt(slave, l1+l2);
    Send(slave);
    l1 = r1+1;
    l2 = r2+1;
  }

  for (; slave < nodes; slave ++) {
    if (is_master(slave)) continue;
    PutInt(slave, 0);
    PutInt(slave, -1);
    PutInt(slave, 0);
    PutInt(slave, -1);
    PutInt(slave, 0);
    Send(slave);
  }

  int result = 0;

  for (int slave = 0; slave < slaves; slave ++) {
    // Receive result from slave
    int source = Receive(-1);
    int slave_result = GetInt(source);

    // Combine results here
    result += slave_result;
    if (result >= MOD) result -= MOD;
  }
  cout << result;
}

int merge(int l1, int r1, int l2, int r2, int rank) {
  int odd_cache, even_cache;
  char invalid = 3;
  int result = 0;
  while (l1 <= r1 && l2 <= r2) {
    if (invalid&1) {
      odd_cache = GetToddValue(l1);
      invalid ^= 1;
    }
    if (invalid&2) {
      even_cache = GetStevenValue(l2);
      invalid ^= 2;
    }
    if (odd_cache < even_cache) {
      l1 ++;
      invalid ^= 1;
      result += rank ^ odd_cache;
      if (result >= MOD) result -= MOD;
      rank ++;
    } else {
      l2 ++;
      invalid ^= 2;
      result += rank ^ even_cache;
      if (result >= MOD) result -= MOD;
      rank ++;
    }
  }
  while (l1 <= r1) {
    result += GetToddValue(l1 ++) ^ rank;
    if (result >= MOD) result -= MOD;
    rank ++;
  }
  while (l2 <= r2) {
    result += GetStevenValue(l2 ++) ^ rank;
    if (result >= MOD) result -= MOD;
    rank ++;
  }
  return result;
}

void process_slave(
  const int master
) {
  // Receive task from master
  Receive(master);
  int l1 = GetInt(master);
  int r1 = GetInt(master);
  int l2 = GetInt(master);
  int r2 = GetInt(master);
  int offset = GetInt(master);

  // Do task here
  int result = merge(l1, r1, l2, r2, offset);

  // Send result back to master
  PutInt(master, result);
  Send(master);
}

// Only master talkes to slaves

void test() {
  for (int i = 0; i < GetToddLength(); i ++) {
    for (int j = i; j < GetToddLength(); j ++) {
      for (int k = 0; k < GetStevenLength(); k ++) {
        for (int l = k; l < GetStevenLength(); l ++) {
          for (int m = 0; m <= 10; m ++) {
            int x, y;
            tie(x, y) = b_search(i, j, k, l, m);
            debug(i, j, k, l, m, x, y);
          }
        }
      }
    }
  }
}

int main() {
  debug(RUN_TEST);
  if (RUN_TEST) {
    if (MyNodeId() == 0) test();
    return 0;
  }
  int id = MyNodeId();
  int nodes = NumberOfNodes();
  if (is_master(id)) process_master(nodes);
  else process_slave(MASTER_NODE);
  return 0;
}
