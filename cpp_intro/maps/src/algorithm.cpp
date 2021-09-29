// cpp_intro/maps
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
    multimap<string, int> m;
    int n; cin >> n;
    int x; string b;
    REP(i,n) {
        cin >> x >> b;
        if (x == 0) {
            m.erase(b);
        } else {
            m.insert({b, x});
        }
    }
    cin >> b;
    auto res = m.equal_range(b);
    if (res.first == res.second) {
        cout << "Empty" << endl;
    } else {
        VI values;
        for (auto it = res.first; it != res.second; it++) {
            values.push_back(it->second);
        }
        sort(values.begin(), values.end());
        for (auto v : values) cout << v << ' ';
        cout << endl;
    }
}
int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
