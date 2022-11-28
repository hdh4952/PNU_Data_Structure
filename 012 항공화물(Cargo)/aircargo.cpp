#include <bits/stdc++.h>
using namespace std;

vector<int> container[200];
vector<int> w_data;
bool complete;
int n, w;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> w;
    complete = false;
    for (int c = 0; c < w_data.size(); c++) {
      if (w_data[c] + w <= 100) {
        w_data[c] += w;
        container[c].push_back(i);
        complete = true;
        break;
      }
    }
    if (complete) continue;
    w_data.push_back(w);
    container[w_data.size() - 1].push_back(i);
  }

  for (auto c : container) {
    if (c.empty()) break;
    for (auto w : c) cout << w << " ";
    cout << "\n";
  }
}