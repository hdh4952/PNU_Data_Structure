#include <bits/stdc++.h>
#define TIME_POINT 5
#define X first
#define Y second
using namespace std;

int K;                        // 창고 경계 꼭짓점의 개수
int cycle_time;               // 한 바퀴 도는 데 걸리는 시간
int dx[] = {1, -1,  0, 0};    // x 좌표 이동
int dy[] = {0,  0, 1, -1};    // y 좌표 이동
vector<pair<int, int>> house; // 창고의 {x, y} 좌표
vector<int> passed_time,      // 좌표마다 경과 시간
            direction;        // 좌표마다 움직이는 방향

int check_gap(int x, int y) {
    if(x > 0) return 0;
    if(x < 0) return 1;
    if(y > 0) return 2;
    if(y < 0) return 3;
    return -1;
}

void init() {
    int x, y;

    cin >> K;
    for(int i=0 ; i<K ; i++) {
        cin >> x >> y;
        house.push_back({x, y});
    }
    house.push_back({house[0].X, house[0].Y});
    passed_time.push_back(0);

    for(int i=0 ; i<K ; i++) {
        int gap_x = house[i+1].X - house[i].X;
        int gap_y = house[i+1].Y - house[i].Y;
        int time = abs(gap_x + gap_y);
        cycle_time += time;
        passed_time.push_back(cycle_time);
        direction.push_back(check_gap(gap_x, gap_y));
    }
} // end of init

void answer() {
    int t;

    for(int i=0 ; i<TIME_POINT ; i++) {
        cin >> t;
        t %= cycle_time;
        for(int now=0 ; now<K ; now++) {
            if(passed_time[now+1] <= t) continue;
            int gap_time = t - passed_time[now];
            int nx = house[now].X + (dx[ direction[now] ] * gap_time);
            int ny = house[now].Y + (dy[ direction[now] ] * gap_time);
            cout << nx << " " << ny << "\n";
            break;
        }
    }
} // end of answer

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();
    answer();
} // end of main