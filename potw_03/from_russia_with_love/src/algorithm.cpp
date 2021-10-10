// potw_03/from_russia_with_love
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
#include<climits>

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)

using namespace std;

typedef long long int LL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;


void testcase() {
    int n, m, k, xi; cin >> n >> m >> k;
    VI x;
    REP(i, n) {
        cin >> xi;
        x.push_back(xi);
    }

    // the table stores in dt[j][i], what score can we guarantee for player k if started at the interval [i, i+j)
    // (i.e. there are j coins left)
    // key fact: for each j (coins left), we know exactly who's turn it is, so the complexity is only O(n^2).
    // base cases: there are 0 coins left
    VVI dt(1, VI(n + 1, 0));

    for (int j = 1; j <= n; j++) {
        dt.push_back(VI(n - j + 1));
        bool ks_turn = (n - j) % m == k; // indicator variable
        for (int i = 0; i <= n - j; i++) {
            int score1 = dt[j-1][i+1] + x[i] * ks_turn; // the left-most coin was taken
            int score2 = dt[j-1][i] + x[i+j-1] * ks_turn; // the right-most coin was taken
            dt[j][i] = !ks_turn ? min(score1, score2) : max(score1, score2);
        }
    }

    cout << dt[n][0] << endl;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
