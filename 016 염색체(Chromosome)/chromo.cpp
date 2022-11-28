#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i < b; i++)
using namespace std;

list<char> DNA;
list<char>::iterator iter_first, iter_last;

void setting(int first, int last) {
  iter_first = DNA.begin();
  iter_last = DNA.begin();
  advance(iter_first, first);
  advance(iter_last, last);
}

void DNA_front(int first, int last) {
  setting(first, last);
  DNA.splice(DNA.begin(), DNA, iter_first, iter_last);
}

void DNA_back(int first, int last) {
  setting(first, last);
  DNA.splice(DNA.end(), DNA, iter_first, iter_last);
}

void DNA_cut(int first, int last) {
  setting(first, last);
  DNA.erase(iter_first, iter_last);
}

void DNA_double(int first, int last) {
  list<char> temp;
  setting(first, last);
  copy(iter_first, iter_last, back_inserter(temp));
  DNA.splice(iter_first, temp);
}

void DNA_flip(int first, int last) {
  list<char> temp;
  auto iter_last = DNA.begin();
  advance(iter_last, last);
  reverse(next(DNA.begin(), first), iter_last);
}

void DNA_report(int first, int last) {
  if (first >= DNA.size()) {
    cout << "NONE\n";
    return;
  }
  last = last < DNA.size() ? last : DNA.size();
  auto iter = DNA.begin();
  advance(iter, first);
  REP(i, 0, last - first) { cout << *iter++; }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  ifstream in("sapiens.txt");
  string s, order;
  int N, a, b;

  if (in.is_open()) {
    getline(in, s);
    while (!in.eof()) {
      getline(in, s);
      REP(i, 0, s.size()) DNA.push_back(s[i]);
    }
  } else
    return 0;

  cin >> N;
  REP(i, 0, N) {
    cin >> order >> a >> b;
    a--;
    if (order == "front") DNA_front(a, b);
    if (order == "back") DNA_back(a, b);
    if (order == "cut") DNA_cut(a, b);
    if (order == "double") DNA_double(a, b);
    if (order == "flip") DNA_flip(a, b);
    if (order == "report") DNA_report(a, b);
  }
}