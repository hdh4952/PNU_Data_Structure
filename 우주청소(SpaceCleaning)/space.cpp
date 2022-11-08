#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i <= b; i++)
using namespace std;

int main() {
  int i, j;
  queue<int> q;

  cin >> i >> j;
  REP(N, i, j) q.push(N);
  while (q.size() != 1) {
    int now = q.front();
    q.pop();
    now = now % 3 + 1;
    while (now--) {
      q.push(q.front());
      q.pop();
    }
  }
  cout << q.front();
}