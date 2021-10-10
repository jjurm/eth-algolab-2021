// week_03/antenna
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
#include<CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)

using namespace std;

typedef long long int LL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Point_2<K> P;
typedef CGAL::Min_circle_2<CGAL::Min_circle_2_traits_2<K>> Min_circle;


long round_up(const K::FT &input_val) {
    double num = floor(CGAL::to_double(input_val));
    while (num + 1 >= input_val) num -= 1;
    while (num < input_val) num += 1;
    return static_cast<long>(num);
}

void testcase(int n) {
    long x, y;
    vector<P> points;
    while(n--) {
        cin >> x >> y;
        points.push_back(P(x, y));
    }
    Min_circle min_circle(points.begin(), points.end(), true);
    cout << round_up(CGAL::sqrt(min_circle.circle().squared_radius())) << endl;
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
