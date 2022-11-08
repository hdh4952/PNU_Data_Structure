#include <bits/stdc++.h>
using namespace std;

vector< pair<int, int> > zsig;
int i, n, u, v, s, gap, firstSignal;
string q, line;

int main () {
    ifstream myfile ("zsignal.txt");

    if (myfile.is_open()) {
        myfile >> firstSignal;
        while ( myfile >> gap ) {
            s += gap;
            if(gap == 0) {
                myfile >> n;
                i += n;
                zsig.push_back({i, s});
            }else zsig.push_back({++i, s});
        }
        myfile.close();
    }

    while(cin >> q) {
        if(q == "T") {
            cin >> u;
            if(u < 1 || zsig.back().first < u) cout << "-1\n";
            else {
                for(pair<int, int> now : zsig) {
                    if(u <= now.first) {
                        cout << firstSignal + now.second << "\n";
                        break;
                    }
                }
            }
        }

        if(q == "M") {
            cin >> u >> v;
            if(zsig.back().first < v || zsig.back().first < u || u > v) cout << "-1\n";
            else {
                bool isFoundLeft = false;
                int minValue = 9999999, maxValue = -9999999;
                for(pair<int, int> now : zsig) {
                    if(!isFoundLeft && u <= now.first) isFoundLeft = true;
                    if(isFoundLeft) {
                        minValue = min(minValue, now.second);
                        maxValue = max(maxValue, now.second);
                        if(v <= now.first) break;
                    }
                }
                cout << firstSignal + minValue << " " << firstSignal + maxValue << "\n";
            }
        }
    }
} 