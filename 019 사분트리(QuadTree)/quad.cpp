#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i <= b; i++)
using namespace std;

vector<int> tree(100000, -1), dx{0, 0, 1, 1}, dy{1, 0, 0, 1};
vector<vector<int>> img(128, vector<int>(128, 0));

int mul(int x, int cnt);
void makeTree(const string &QTS);
void makeImg(int node, int depth, int maxDepth, int x, int y, int fix);
string makeQTS(int depth, int maxDepth, int x, int y);

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int k;
  string token;

  cin >> k >> token;

  if (token == "QTS") {
    string QTS;
    cin >> QTS;
    makeTree(QTS);
    makeImg(0, 0, k, 0, 0, -1);

    REP(i, 0, mul(2, k) - 1) {
      REP(j, 0, mul(2, k) - 1) { cout << img[i][j]; }
      cout << "\n";
    }
  } else {  // if (token == "IMG")
    string IMG;
    REP(i, 0, mul(2, k) - 1) {
      cin >> IMG;
      REP(j, 0, mul(2, k) - 1) { img[i][j] = IMG[j] - '0'; }
    }
    cout << makeQTS(0, k, 0, 0);
  }
}

int mul(int x, int cnt) {
  int answer = 1;
  REP(i, 1, cnt) answer *= x;
  return answer;
}

void makeTree(const string &QTS) {
  int node = 0;

  for (auto ch : QTS) {
    if (ch == '(') {
      node = node * 4 + 1;
    } else if (ch == ')') {
      node /= 4;
    } else {  // if (ch == '0' || ch == '1')
      tree[node] = ch - '0';
      node++;
    }
  }
}

void makeImg(int node, int depth, int maxDepth, int x, int y, int fix) {
  if (depth == maxDepth) {
    if (fix != -1)
      img[x][y] = fix;
    else
      img[x][y] = tree[node];
    return;
  }

  REP(i, 0, 3) {
    if (fix == -1 && tree[node] != -1) fix = tree[node];
    makeImg(node * 4 + i + 1, depth + 1, maxDepth,
            x + dx[i] * mul(2, maxDepth - depth - 1),
            y + dy[i] * mul(2, maxDepth - depth - 1), fix);
  }
}

string makeQTS(int depth, int maxDepth, int x, int y) {
  if (depth == maxDepth) {
    if (img[x][y] == 0)
      return "0";
    else
      return "1";  // if(img[x][y] == 1)
  }

  string str = "(";
  REP(i, 0, 3) {
    str +=
        makeQTS(depth + 1, maxDepth, x + dx[i] * mul(2, maxDepth - depth - 1),
                y + dy[i] * mul(2, maxDepth - depth - 1));
  }
  str += ")";
  if (str == "(0000)")
    return "0";
  else if (str == "(1111)")
    return "1";
  return str;
}