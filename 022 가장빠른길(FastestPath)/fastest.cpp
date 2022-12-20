#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define INF 1e9
using namespace std;

map<char, int> m;
map<int, char> mR;
int vCnt = 0;

int v(char vName) {
  if (m.find(vName) != m.end()) return m[vName];
  mR[vCnt] = vName;
  return m[vName] = vCnt++;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N;
  cin >> N;
  int ans = 0;
  char vName;
  vector<vector<int>> path(N, vector<int>(N, INF));
  vector<int> deg(N, 0);

  REP(i, 0, N - 1) path[i][i] = 0;
  REP(i, 1, N) {
    cin >> vName;
    int now = v(vName), cost;
    while (cin >> vName) {
      if (vName == '$') break;
      cin >> cost;
      deg[now]++;
      path[now][v(vName)] = cost * 2;
    }
  }

  REP(k, 0, N - 1) {
    REP(i, 0, N - 1) {
      REP(j, 0, N - 1) {
        path[i][j] = min(path[i][j], path[i][k] + path[k][j] + deg[k]);
      }
    }
  }
  REP(i, 0, N - 1)
  REP(j, 0, N - 1)
  ans = max(ans, path[i][j]);

  cout << ans;
}