// week_01/dominoes
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
    int n,x,m=1,c=0;
    cin >> n;
    REP(i,n) {
        cin >> x;
        if (m > 0) {
            c++;
            m = max(m, x);
            m--;
        }
    }
    cout << c << endl;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
