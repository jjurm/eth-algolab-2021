// week_02/burning_coins
// by Juraj Micko

#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<string>
#include<utility>
#include<tuple>
#include<array>
#include<iterator>
#include<deque>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
#include<stack>
#include<queue>
#include<cmath>
#include<numeric>
#include<cassert>

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)

using namespace std;

typedef long long int LL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;


void testcase() {
    int n, x, score1, score2; cin >> n;
    int turn = n % 2;// 0 = adversary, 1 = me (starting backwards)
    VI v;
    REP(i,n) {
        cin >> x;
        v.push_back(x);
    }
    VVI dt(n + 1, VI(n + 1, 0));
    for (int i = n-1; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            if (turn) { // my turn
                score1 = dt[j][i-j+1] + v[j + (n-i-1)];
                score2 = dt[j+1][i-j] + v[j];
                dt[j][i-j] = max(score1, score2);
            } else { // adversary's turn
                score1 = dt[j][i-j+1];
                score2 = dt[j+1][i-j];
                dt[j][i-j] = min(score1, score2);
            }
        }
        turn = 1 - turn;
    }
    cout << dt[0][0] << endl;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
