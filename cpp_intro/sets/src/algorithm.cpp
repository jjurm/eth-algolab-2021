// cpp_intro/sets
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
    int q, a, b;
    cin >> q;
    set<int> s;
    REP(i,q) {
        cin >> a >> b;
        if (a == 0) {
            s.insert(b);
        } else {
            s.erase(b);
        }
    }
    if (s.size() == 0) {
        cout << "Empty";
    } else {
        for (int e : s) {
            cout << e << ' ';
        }
    }
    cout << endl;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
