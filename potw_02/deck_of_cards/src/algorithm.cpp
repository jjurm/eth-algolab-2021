// potw_02/deck_of_cards
// by Juraj Micko
//
// This is O(n log n). A better O(n) solution is using a sliding window: iterate through end points and keep track of
// a suitable start point for the current end point.

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
    int n,k,x; cin >> n >> k;
    VI acc = {0};
    REP(i,n) {
        cin >> x;
        acc.push_back(acc[i] + x);
    }
    VI best_js;
    REP(i,n) {
        int search_for = k + acc[i];
        auto begin = acc.cbegin() + i + 1;
        auto bound = lower_bound(begin, acc.cend(), search_for);

        if (bound == begin) {
            best_js.push_back(bound - acc.cbegin());
        } else if (bound == acc.cend()) {
            best_js.push_back(bound - 1 - acc.cbegin());
        } else {
            int d1 = abs(search_for - *(bound-1));
            int d2 = abs(search_for - *bound);
            if (d1 <= d2) {
                best_js.push_back(bound - 1 - acc.cbegin());
            } else {
                best_js.push_back(bound - acc.cbegin());
            }
        }
    }
    int min_i = -1;
    int min_diff = 0;
    REP(i,n) {
        int diff = abs(k - acc[best_js[i]] + acc[i]);
        if (min_i == -1 || diff < min_diff) {
            min_i = i;
            min_diff = diff;
        }
    }
    cout << min_i << ' ' << best_js[min_i] - 1 << endl;

}
int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
