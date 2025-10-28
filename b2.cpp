#include <bits/stdc++.h>
using namespace std;
const double INF = 1e9;

int main() {
    int t;
    cin >> t;

    while (t--) {
        vector<string> frnd;
        string s;

        while (cin >> s) {
            frnd.push_back(s);
            if (frnd.size() == s.size()) break;
        }

        int n = frnd.size();
        int maxc = 0, p = 0;

        for (int i = 0; i < n; i++) {
            int c = 0;

            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (frnd[i][j] != 'Y') continue;

                for (int k = 0; k < n; k++) {
                    if (frnd[i][k] == 'Y' && frnd[j][k] == 'Y') {
                        c++;
                        break;
                    }
                }
            }

            if (c > maxc) {
                maxc = c;
                p = i;
            }
        }

        cout << p << " " << maxc << endl;
    }

    return 0;
}
