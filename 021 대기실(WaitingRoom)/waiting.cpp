#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i <= b; i++)
using namespace std;

struct Guest {
  int enterTime;
  int id;
  int counselingTime;

  bool operator<(const Guest &p) const {
    if (this->counselingTime != p.counselingTime)
      return this->counselingTime < p.counselingTime;
    return this->id > p.id;
  }
};

int currentTime = 30;
priority_queue<Guest> WaitRoom;

void counseling() {
  auto [enterTime, id, counselingTime] = WaitRoom.top();
  WaitRoom.pop();
  if (counselingTime <= 10) {
    currentTime += counselingTime;
    cout << id << "\n";
    return;
  } else {
    currentTime += counselingTime / 2;
    counselingTime -= counselingTime / 2;
    WaitRoom.push({enterTime, id, counselingTime});
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N, t, ID, c;
  vector<Guest> p;
  cin >> N;
  REP(i, 1, N) {
    cin >> t >> ID >> c;
    p.push_back({t, ID, c});
  }

  sort(p.begin(), p.end(),
       [](Guest a, Guest b) { return a.enterTime < b.enterTime; });
  queue<Guest> q;
  for (auto person : p) q.push(person);
  while (!q.empty()) {
    Guest person = q.front();
    q.pop();
    if (person.enterTime <= currentTime)
      WaitRoom.push(person);
    else {
      while (!WaitRoom.empty() && person.enterTime > currentTime) counseling();
      if (WaitRoom.empty()) currentTime = person.enterTime;
      WaitRoom.push(person);
    }
  }

  while (!WaitRoom.empty()) counseling();
}