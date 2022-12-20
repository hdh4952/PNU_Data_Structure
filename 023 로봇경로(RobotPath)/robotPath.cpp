#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define N_MAX 15
#define INF 1e9
using namespace std;

int N, t;
vector<vector<int>> arr(N_MAX + 1,
                        vector<int>(N_MAX + 1, 0));  // 0: 좌우, 1: 상하
vector<vector<vector<int>>> minCost(N_MAX + 1,
                                    vector<vector<int>>(N_MAX + 1,
                                                        vector<int>(2, INF)));
vector<int> dx{-1, 1, 0, 0}, dy{0, 0, -1, 1};

void dfs(int x, int y, int cost, int dir) {
  minCost[x][y][dir] = cost;
  REP(i, 0, 3) {
    int nx = x + dx[i], ny = y + dy[i];
    if (nx <= 0 || ny <= 0 || nx > N || ny > N) continue;
    if (arr[nx][ny]) continue;
    int nxtCost = cost + 1;
    if (i < 2) {
      if (dir != 0) nxtCost += t;
      if (nxtCost > minCost[nx][ny][0]) continue;
      dfs(nx, ny, nxtCost, 0);
    } else {
      if (dir != 1) nxtCost += t;
      if (nxtCost > minCost[nx][ny][1]) continue;
      dfs(nx, ny, nxtCost, 1);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> N >> t;
  REP(i, 1, N)
  REP(j, 1, N)
  cin >> arr[j][N - i + 1];

  dfs(1, 1, 0, 0);
  dfs(1, 1, 0, 1);
  if (minCost[N][N][0] == INF && minCost[N][N][1] == INF)
    cout << "-1";
  else
    cout << min(minCost[N][N][0], minCost[N][N][1]);
}