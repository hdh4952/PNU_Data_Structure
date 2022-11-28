#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i <= b; i++)
using namespace std;

map<string, vector<string>> funcs;
vector<string> answer, prev_func;
bool DEADLOCK;

void make_funcs(int N) {
  REP(i, 1, N) {
    string func_name, str;
    vector<string> func;

    cin >> func_name;
    while (cin >> str) {
      if (str == "$") break;
      func.push_back(str);
    }
    funcs[func_name] = func;
  }
}

void func_call(string func_name) {
  if (find(prev_func.begin(), prev_func.end(), func_name) != prev_func.end()) {
    DEADLOCK = true;
    return;
  } else
    prev_func.push_back(func_name);

  vector<string> func = funcs[func_name];
  for (auto now : func) {
    if (DEADLOCK) return;
    if ("A" <= now && now <= "Z")
      func_call(now);
    else
      answer.push_back(func_name + "-" + now);
  }
  prev_func.pop_back();
}

int main() {
  int N, k[2];
  cin >> N >> k[0] >> k[1];

  make_funcs(N);
  func_call("M");

  if (DEADLOCK) {
    cout << "DEADLOCK";
    return 0;
  }

  REP(i, 0, 1) {
    if (k[i] > answer.size())
      cout << "NONE\n";
    else
      cout << answer[k[i] - 1] << "\n";
  }
}