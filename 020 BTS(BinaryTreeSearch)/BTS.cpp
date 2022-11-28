#include <bits/stdc++.h>

using namespace std;

unordered_map<string, int> exist;
unordered_map<string, string> nodes;

void insert(const string& node, const string& s) {
  if (nodes[node].empty()) {
    nodes[node] = s;
    return;
  }
  if (s < nodes[node])
    insert(node + "2", s);
  else
    insert(node + "1", s);
}

string erase_recursive(string node, const string& str) {
  if (nodes[node] == str) return node;
  if (nodes[node].empty()) return "\1";
  return max(erase_recursive(node + "2", str),
             erase_recursive(node + "1", str));
}

string find_max(const string& node) {
  if (nodes[node].empty()) return "";
  vector<string> vec = {nodes[node]};
  auto A = find_max(node + "2");
  auto B = find_max(node + "1");
  if (!A.empty()) vec.push_back(A);
  if (!B.empty()) vec.push_back(B);
  sort(vec.begin(), vec.end(), greater<>());
  return vec[0];
}

string find_min(const string& node) {
  if (nodes[node].empty()) return "";
  vector<string> vec = {nodes[node]};
  auto A = find_min(node + "2");
  auto B = find_min(node + "1");
  if (!A.empty()) vec.push_back(A);
  if (!B.empty()) vec.push_back(B);
  sort(vec.begin(), vec.end());
  return vec[0];
}

void erase(string str) {
  if (!exist[str]) return;
  exist[str] = 0;
  string nxt_node = "1";
  while (true) {
    string node =
        erase_recursive(nxt_node, str);  // 일단 str이 있는 노드를 찾아서 지우고
                                         // 거길 아래 노드로 채워야 함
    str = find_max(node + "2");
    if (!str.empty()) {  // 왼쪽 서브트리에서 꺼내온다면
      nodes[node] = str;
      nxt_node = node + "2";
    } else {
      str = find_min(node + "1");
      if (!str.empty()) {  // 오른쪽 서브트리에서 꺼내온다면
        nodes[node] = str;
        nxt_node = node + "1";
      } else {  // 지웠던 노드가 리프 노드인 경우
        nodes[node] = "";
        return;
      }
    }
  }
}

set<string> search_depth(const string& node, int depth, int k) {
  if (nodes[node].empty()) return {};
  if (depth == k) return {nodes[node]};
  auto A = search_depth(node + "2", depth + 1, k);
  auto B = search_depth(node + "1", depth + 1, k);
  for (const string& s : B) A.insert(s);
  return A;
}

set<string> search_leaf(const string& node) {
  if (nodes[node].empty()) return {};
  auto A = search_leaf(node + "2");
  auto B = search_leaf(node + "1");
  for (const string& s : B) A.insert(s);
  if (A.empty()) A.insert(nodes[node]);
  return A;
}

int main() {
  while (true) {
    string s;
    cin >> s;
    if (s == "+") {
      string a;
      cin >> a;
      if (!exist[a]) insert("1", a);
      exist[a] = 1;
    }
    if (s == "-") {
      string a;
      cin >> a;
      erase(a);
    }
    if (s == "depth") {
      int a;
      cin >> a;
      bool isPrint = false;
      for (const auto& x : search_depth("1", 1, a)) {
        cout << x << " ";
        isPrint = true;
      }
      if (!isPrint) cout << "NO";
      cout << "\n";
    }
    if (s == "leaf") {
      for (const auto& x : search_leaf("1")) cout << x << " ";
      cout << "\n";
    }
    if (s == "quit") break;
  }
}