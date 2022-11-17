#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i <= b; i++)
using namespace std;

int idx;
vector<int> tree[510], depth(510, 0), subtree(510, 0);
vector<string> names;
map<string, int> nameToInt;

/**
 * @brief Sort by considering subtree, depth, and dictionary order
 *
 * @param left
 * @param right
 * @return true
 * @return false
 */
bool cmp(string left, string right) {
  int a = nameToInt[left], b = nameToInt[right];
  if (subtree[a] != subtree[b]) return subtree[a] > subtree[b];
  if (depth[a] != depth[b]) return depth[a] < depth[b];
  return left < right;
}

/**
 * @brief Returns the number of subordinates of root
 *
 * @param root BOSS number
 * @return int
 */

int subtreeCnt(int root) {
  if (subtree[root]) return subtree[root];
  if (tree[root].size() == 0) return subtree[root] = 1;
  int sum = 1;
  for (auto i : tree[root]) sum += subtreeCnt(i);
  return subtree[root] = sum;
}

/**
 * @brief Assign depth based on root
 *
 * @param root BOSS number
 */
void depthMatch(int root) {
  int depthCnt = 0;
  queue<int> q;
  q.push(root);

  while (!q.empty()) {
    int qsize = q.size();
    REP(i, 1, qsize) {
      int now = q.front();
      q.pop();
      depth[now] = depthCnt;
      for (auto nxt : tree[now]) q.push(nxt);
    }
    depthCnt++;
  }
}

/**
 * @brief If a name does not exist, a number is given
 *
 * @param name name to check
 */
void generateName(string name) {
  if (nameToInt.find(name) != nameToInt.end()) return;
  nameToInt[name] = idx++;
  names.push_back(name);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  string root;
  string person, boss;

  cin >> n;
  REP(i, 1, n - 1) {
    cin >> person >> boss;
    generateName(person);
    generateName(boss);
    tree[nameToInt[boss]].push_back(nameToInt[person]);
  }

  int temp, maxSubtree = 0;
  for (auto name : names) {
    temp = subtreeCnt(nameToInt[name]);
    if (temp > maxSubtree) {
      maxSubtree = temp;
      root = name;
    }
  }

  depthMatch(nameToInt[root]);
  sort(names.begin(), names.end(), cmp);
  for (auto name : names) cout << name << "\n";
}