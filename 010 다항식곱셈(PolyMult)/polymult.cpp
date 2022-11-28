#include <bits/stdc++.h>
using namespace std;

int N, t, c, e;
vector<pair<int, int>> poly, answer;

bool cmp(pair<int, int> a, pair<int, int> b) { return a.second > b.second; }

void addPoly(vector<pair<int, int>> v) {
  answer.clear();
  map<int, int> m;
  vector<int> key;

  for (auto i : v) {
    if (m.find(i.second) == m.end()) {
      m[i.second] = i.first;
      key.push_back(i.second);
    } else
      m[i.second] += i.first;
  }

  for (auto i : key) {
    if (m[i] == 0) continue;
    answer.push_back({m[i], i});
  }
}

void setPoly() {
  poly.clear();
  cin >> t;
  while (t--) {
    cin >> c >> e;
    poly.push_back({c, e});
  }
}

void multiPoly() {
  vector<pair<int, int>> temp;
  for (auto i : poly)
    for (auto j : answer)
      temp.push_back({i.first * j.first, i.second + j.second});
  addPoly(temp);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N;
  answer.push_back({1, 0});
  for (int i = 0; i < N; i++) {
    setPoly();
    multiPoly();
  }

  if (answer.size() == 0) {
    cout << "0 0";
    return 0;
  }

  sort(answer.begin(), answer.end(), cmp);
  cout << answer.size() << "\n";
  for (auto i : answer) cout << i.first << " " << i.second << "\n";
}