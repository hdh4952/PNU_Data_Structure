#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define N_MAX 15
#define INF 1e9
using namespace std;

int N, t;
vector<vector<int>> arr(N_MAX + 1, vector<int>(N_MAX + 1, 0)),
    minCost(N_MAX + 1, vector<int>(N_MAX + 1, INF));

vector<int> dx{-1, 1, 0, 0}, dy{0, 0, -1, 1};

void dfs(int px, int py, int x, int y, int cost) {
  minCost[x][y] = cost;
  REP(i, 0, 3) {
    int nx = x + dx[i], ny = y + dy[i];
    if (nx <= 0 || ny <= 0 || nx > N || ny > N) continue;
    if (arr[nx][ny]) continue;
    int nxtCost = cost + 1;
    if ((px - x && ny - y) || (py - y && nx - x)) nxtCost += t;
    if (nxtCost > minCost[nx][ny]) continue;
    dfs(x, y, nx, ny, nxtCost);
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

  dfs(1, 1, 1, 1, 0);
  if (minCost[N][N] == INF)
    cout << "-1";
  else
    cout << minCost[N][N];

  REP(i, 1, N) {
    REP(j, 1, N) {
      if (minCost[j][N - i + 1] == INF)
        cout << "-1 ";
      else
        cout << minCost[j][N - i + 1] << " ";
    }
    cout << "\n";
  }
}