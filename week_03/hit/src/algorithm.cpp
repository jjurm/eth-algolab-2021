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
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)

using namespace std;

typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long int LL;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 Ray;
typedef K::Segment_2 Seg;

void testcase(int n) {
    int64_t x, y, a, b, r, s, t, u;
    cin >> x >> y >> a >> b;
    Ray ray(P(x, y), P(a, b));
    bool hit = false;
    while (n--) {
        cin >> r >> s >> t >> u;
        if (hit == false) {
            Seg obstacle(P(r, s), P(t, u));
            if (CGAL::do_intersect(ray, obstacle)) {
                hit = true;
            }
        }
    }
    cout << (hit ? "yes" : "no") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;
        testcase(n);
    }
}
