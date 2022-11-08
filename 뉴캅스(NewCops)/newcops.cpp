#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;

int K;                        // 창고 경계 꼭짓점의 개수
int cop1, cop2;               // 로봇의 현재 위치를 나타낸 시간
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
        if(i+1 == K/2) cop2 = cycle_time;
        cycle_time += time;
        passed_time.push_back(cycle_time);
        direction.push_back(check_gap(gap_x, gap_y));
    }
} // end of init

void compute() {
    int t;
    int t1 = cop1, t2 = cop2;
    int s1 = cop1, s2 = cop2;

    cin >> t;
    t1 = t % cycle_time;
    t2 = (cycle_time + t2 - t1) % cycle_time;
    if(min(abs(s1 - t1), abs(cycle_time - t1)) < abs(s2 - t1)) {
        cop1 = t1;
        cop2 = t2;
    }else {
        cop2 = t1;
        cop1 = t2;
    }
    
} // end of compute

void answer(int t) {
    t %= cycle_time;
    for(int now=0 ; now<K ; now++) {
        if(passed_time[now+1] <= t) continue;
        int gap_time = t - passed_time[now];
        int nx = house[now].X + (dx[ direction[now] ] * gap_time);
        int ny = house[now].Y + (dy[ direction[now] ] * gap_time);
        cout << nx << " " << ny << "\n";
        break;
    }
} // end of answer

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();
    compute();
    answer(cop1);
    answer(cop2);
} // end of main