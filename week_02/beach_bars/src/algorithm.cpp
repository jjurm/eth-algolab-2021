// week_02/beach_bars
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
    int n, t; cin >> n;
    VI x;
    REP(i, n) {
        cin >> t;
        x.push_back(t);
    }
    sort(x.begin(), x.end());
    auto last = x.begin();
    int max_count = 0, min_distance = -1, count = 1;
    VI r;
    for (auto first = x.begin(); first < x.end(); first++, count++) {
        while (*last < *first - 200) {
            last++; // the last parasol must be within reach
            count--;
        }
        int distance = (*first - *last + 1) / 2;
        if (count > max_count || (count == max_count && distance < min_distance)) {
            r.clear();
            max_count = count;
            min_distance = distance;
            r.push_back(*first - distance);
            if ((*first - *last) % 2)
                r.push_back(*first - distance + 1);
        } else if (count == max_count && distance == min_distance) {
            r.push_back(*first - distance);
            if ((*first - *last) % 2)
                r.push_back(*first - distance + 1);
        }
    }
    cout << max_count << ' ' << min_distance << "\n";
    for (int ri : r) cout << ri << ' ';
    cout << endl;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
