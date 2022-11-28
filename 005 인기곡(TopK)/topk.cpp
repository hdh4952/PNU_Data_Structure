#include <bits/stdc++.h>
using namespace std;

int n, k;
queue<pair<int, char>> answer, temp;

struct music {
    string title;
    char genre;
    int broadcast;
    double file_size;
    int download;
} musics[101];

bool cmp(const music& m1, const music& m2) {
    if(m1.broadcast != m2.broadcast) return m1.broadcast > m2.broadcast;
    if(m1.download  != m2.download)  return m1.download  > m2.download;
    return m1.file_size < m2.file_size;
}

void init() {
    cin >> n >> k;
    for(int i=0 ; i<n ; i++) {
        cin >> musics[i].title 
            >> musics[i].genre 
            >> musics[i].broadcast 
            >> musics[i].file_size
            >> musics[i].download;
    }
}

void compute() {
    sort(musics, musics + n, cmp);
    answer.push({0, musics[0].genre});
    for(int i=1 ; i<n ; i++) {
        while(!temp.empty() && answer.back().second != temp.front().second) {
            answer.push(temp.front());
            temp.pop();
        }
        if(answer.back().second != musics[i].genre) answer.push({i, musics[i].genre});
        else temp.push({i, musics[i].genre});
    }

    while(!temp.empty()) {
        answer.push(temp.front());
        temp.pop();
    }
}

void solve() {
    for(int i=1 ; i<k ; i++) answer.pop();
    int idx = answer.front().first;
    cout << musics[idx].title;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();
    compute();
    solve();
}