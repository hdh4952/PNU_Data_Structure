#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> s, h, w, sum_h, sum_w;
int max_h, max_w;

int main() {
    int tmp, i=0;

    while(true) {
        cin >> tmp;
        if(tmp == 0) break;
        s.push_back(tmp);
    }
    
    for(int i=0 ; i<s.size() ; i+=2) {
        w.push_back(s[i]);
        h.push_back(s[i+1]);
    }

    reverse(h.begin(), h.end());

    sum_w.push_back(w[0]);
    sum_h.push_back(h[0]);
    for(int i=1 ; i<w.size() ; i++) {
        sum_w.push_back(w[i] + sum_w[i-1]);
        sum_h.push_back(h[i] + sum_h[i-1]);
    }

    max_w = sum_w.back();
    max_h = sum_h.back();

    reverse(sum_h.begin(), sum_h.end());
    sum_h.push_back(0);

    int x, y;
    while(cin >> x >> y) {
        if(max_w < x || max_h < y) {
            cout << "out\n";
            continue;
        }
        for(int i=0 ; i<sum_w.size() ; i++) {
            if(x < sum_w[i]) {
                if(y < sum_h[i]) cout << "in\n";
                if(y == sum_h[i]) cout << "on\n";
                if(y > sum_h[i]) cout << "out\n";
                break;
            }
            if(x == sum_w[i]) {
                if(y < sum_h[i+1]) cout << "in\n";
                if(sum_h[i+1] <= y && y <= sum_h[i]) cout << "on\n";
                if(y > sum_h[i]) cout << "out\n";
                break;
            }
        }
    }    
}