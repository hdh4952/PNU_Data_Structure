#include <bits/stdc++.h>
using namespace std;

void init(vector<int> &source);
int calculate(vector<int> source);

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  vector<int> source;  // store opening and closing parentheses as 0 and 1

  init(source);
  cout << calculate(source);
}

void init(vector<int> &source) {
  string line;  // input data

  while (cin >> line) {
    for (auto ch : line) {
      if (ch == '{') source.push_back(0);
      if (ch == '}') source.push_back(1);
    }
  }
}

int calculate(vector<int> source) {
  int sum = 0, depth = 0;

  for (auto i : source) {
    if (i == 0) depth++;
    if (i == 1) sum += depth--;
  }

  return sum;
}