#include <bits/stdc++.h>
using namespace std;

vector<int> v[100001];
int n, column_idx, empty_line;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> column_idx;
    if (!column_idx) {
      cin >> empty_line;
      i += empty_line - 1;
      continue;
    }
    while (column_idx) {
      v[column_idx].push_back(i);
      cin >> column_idx;
    }
  }
  cout << n << "\n";
  empty_line = 0;
  for (int i = 1; i <= n; i++) {
    if (v[i].empty()) {
      empty_line++;
      continue;
    }
    if (empty_line) {
      cout << "0 " << empty_line << "\n";
      empty_line = 0;
    }
    for (auto row_idx : v[i]) cout << row_idx << " ";
    cout << "0\n";
  }
  if (empty_line) cout << "0 " << empty_line << "\n";
}