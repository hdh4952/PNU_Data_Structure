#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, k, id, idx, cdist, insertIdx;
  map<int, int> id_log;
  vector<pair<int, int>> cafe;

  cin >> n >> k;
  while (k--) {
    cin >> id;
    int check;
    if (id_log.find(id) == id_log.end())
      id_log[id] = check = 1;
    else
      check = ++id_log[id];

    if (check % 2 == 0) {  // 출입 기록이 짝수라면 퇴장
      for (int i = 0; i < cafe.size(); i++) {
        if (cafe[i].second == id) {
          cafe.erase(cafe.begin() + i);
          break;
        }
      }
      continue;
    }
    if (cafe.size() == n) {  // cafe가 만석일 경우
      id_log[id]++;
      continue;
    }
    if (cafe.empty()) {
      cafe.push_back({0, id});  // 아무도 없다면 1에 배정
      cout << id << " 1\n";
    } else if (cafe.size() == 1) {  // 한 명 있다면 반대편에 배정
      idx = cafe.front().first + n / 2;
      if (idx < n) {
        cafe.push_back({idx, id});
        cout << id << " " << idx + 1 << "\n";
      } else {
        cafe.insert(cafe.begin(), {idx % n, id});
        cout << id << " " << (idx % n) + 1 << "\n";
      }
    } else {
      int max_cdist = 0;
      for (int i = 0; i < cafe.size() - 1; i++) {
        cdist = cafe[i + 1].first - cafe[i].first;
        if (max_cdist < cdist) {
          max_cdist = cdist;
          insertIdx = i + 1;
          idx = cafe[i].first + cdist / 2;
        }
      }
      cdist = n - cafe.back().first + cafe.front().first;
      if (max_cdist < cdist) {
        idx = (cafe.back().first + cdist / 2) % n;
        if (cafe.front().first - (idx + 1) % n == cdist / 2)
          idx = min((idx + 1) % n, idx);
        if (idx < cafe.front().first)
          cafe.insert(cafe.begin(), {idx, id});
        else
          cafe.push_back({idx, id});
      } else
        cafe.insert(cafe.begin() + insertIdx, {idx, id});
      cout << id << " " << idx + 1 << "\n";
    }
  }
}