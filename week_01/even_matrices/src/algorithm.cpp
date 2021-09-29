// week_01/even_matrices
// by Juraj Micko
//
// O(n^3)

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
    int n,x;
    cin >> n;
    VVI sums(n+1, VI(n+1, 0));
    // dynamically build the table of [sums from the top left corner]
    FOR(i,1,n+1) {
        FOR(j,1,n+1) {
            cin >> x;
            sums[i][j] = (sums[i][j-1] + sums[i-1][j] + sums[i-1][j-1] + x) % 2;
        }
    }

    // r[i+1][j+1] contains the numbers of {even-sum, odd-sum} quadruples of the form (_,i,_,j)
    vector<VVI> r(n+1, VVI(n+1, VI(2, 0)));

    FOR(i2, 1, n+1) {
        // t[i1] contains the number of {even-sum, odd-sum} quadruples of the form (i1,i2,_,j)
        // (and is kept updated for each increment in i1)
        VVI t = VVI(i2, VI(2, 0));

        FOR(j, 1, n+1) {
            FOR(i1, 0, i2) {
                // All quadruples of the form (i1,i2,_,j-1) can be extended to (i1,i2,_,j), just the parity might have
                // changed.
                int swap = (sums[i1][j-1] + sums[i1][j] + sums[i2][j-1] + sums[i2][j]) % 2;
                t[i1] = {
                        t[i1][swap],
                        t[i1][1-swap],
                };

                // There is one more quadruple that we need to count: (i1, i2, j-1, j), and its parity happens to be
                // 'swap'.
                t[i1][swap]++;

                // Finally, add the counts to r[i2][j] (i.e. r[i2][j] is just t accumulated across the first dimension)
                r[i2][j][0] += t[i1][0];
                r[i2][j][1] += t[i1][1];
            }
        }
    }

    // Finally, sum all even quadruples
    int sum = 0;
    FOR(i,1,n+1) FOR(j,1,n+1) sum += r[i][j][0];
    cout << sum << endl;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
