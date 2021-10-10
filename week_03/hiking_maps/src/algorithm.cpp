// week_03/hiking_maps
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
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)

using namespace std;

typedef long long int LL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 Seg;

struct Triangle {
    // The points of each side are stored such that 'inner' side of the triangle is the one on the left
    const Seg side1, side2, side3;

    Triangle(const P &q1, const P &q2, const P &q3, const P &q4, const P &q5, const P &q6) :
            side1(CGAL::left_turn(q1, q2, q3) ? Seg(q1, q2) : Seg(q2, q1)),
            side2(CGAL::left_turn(q3, q4, q5) ? Seg(q3, q4) : Seg(q4, q3)),
            side3(CGAL::left_turn(q5, q6, q1) ? Seg(q5, q6) : Seg(q6, q5)) {}

    bool containsPoint(const P &p) {
        // p can be collinear or a left turn
        return (CGAL::orientation(side1.source(), side1.target(), p) != CGAL::RIGHT_TURN)
               && (CGAL::orientation(side2.source(), side2.target(), p) != CGAL::RIGHT_TURN)
               && (CGAL::orientation(side3.source(), side3.target(), p) != CGAL::RIGHT_TURN);
    }
};

P inputPoint() {
    int x, y;
    cin >> x >> y;
    return {x, y};
}

void testcase() {
    int m, n;
    cin >> m >> n;
    vector<P> points;
    vector<Triangle> triangles;
    REP(i, m) points.push_back(inputPoint());
    REP(i, n) triangles.emplace_back(inputPoint(), inputPoint(),
                                     inputPoint(), inputPoint(),
                                     inputPoint(), inputPoint());

    // For each triangle, list the legs that are fully contained in it
    vector<vector<int>> legsContainedInTriangle(n, vector<int>(0));
    vector<bool> prevPointContained(n, false);
    REP(j, n) {
        prevPointContained[j] = triangles[j].containsPoint(points[0]);
    }
    FOR(i, 1, m) {
        vector<bool> pointContained(n, false);
        REP(j, n) {
            pointContained[j] = triangles[j].containsPoint(points[i]);
            if (prevPointContained[j] && pointContained[j])
                legsContainedInTriangle[j].push_back(i - 1);
        }
        prevPointContained = pointContained;
    }

    // run a sliding window on the sequence of triangles
    int b = 0, nLegsCovered = 0, bestPrice = -1;
    vector<int> legCovered(m - 1, 0); // number of triangles (within b..e) that cover each leg
    FOR(e, 1, n + 1) {
        for (const int leg : legsContainedInTriangle[e-1]) {
            if (legCovered[leg]++ == 0) {
                ++nLegsCovered;
            }
        }
        while (nLegsCovered == m-1) {
            if (bestPrice == -1 || (e-b) < bestPrice) {
                bestPrice = e-b;
            }

            for (const int leg : legsContainedInTriangle[b++]) {
                if (--legCovered[leg] == 0) {
                    --nLegsCovered;
                }
            }
        }
    }

    cout << bestPrice << endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
