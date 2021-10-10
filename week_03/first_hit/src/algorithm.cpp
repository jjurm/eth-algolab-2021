// week_03/first_hit
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
#include<random>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)

using namespace std;

typedef long long int LL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 Ray;
typedef K::Segment_2 Seg;
typedef boost::optional<boost::variant<P, Seg>> Intersection;


long round_down(const K::FT &input_val) {
    double num = floor(CGAL::to_double(input_val));
    while (num > input_val) num -= 1;
    while (num + 1 <= input_val) num += 1;
    return static_cast<long>(num);
}

struct IntersectVisitor : public boost::static_visitor<Intersection> {
    const Seg &obstacle;

    explicit IntersectVisitor(const Seg &obstacle) : obstacle(obstacle) {}

    Intersection operator()(Ray &ray) const {
        return CGAL::intersection(ray, obstacle);
    }

    Intersection operator()(Seg &seg) const {
        return CGAL::intersection(seg, obstacle);
    }
};

struct SmallerSegmentVisitor : public boost::static_visitor<Seg> {
    const P &ray_start;

    explicit SmallerSegmentVisitor(const P &ray_start) : ray_start(ray_start) {}

    Seg operator()(const P &intersection) const {
        return {ray_start, intersection};
    }

    Seg operator()(const Seg &intersection) const {
        P a = intersection.source(), b = intersection.target();
        return {ray_start,
                CGAL::has_smaller_distance_to_point(ray_start, a, b) ? a : b};
    }
};

struct PrintResultVisitor : public boost::static_visitor<> {
    void operator()(Ray &ray) {
        cout << "no" << endl;
    }

    void operator()(Seg &segment) {
        P result = segment.target();
        cout << round_down(result.x()) << " " << round_down(result.y()) << endl;
    }
} print_result;


void testcase(int n) {
    long x, y, a, b, r, s, t, u;
    cin >> x >> y >> a >> b;
    Ray ray(P(x, y), P(a, b));
    vector<Seg> obstacles;
    while (n--) {
        cin >> r >> s >> t >> u;
        obstacles.push_back(Seg(P(r, s), P(t, u)));
    }
    random_shuffle(obstacles.begin(), obstacles.end());

    boost::variant<Ray, Seg> ray_segment(ray);

    for (const auto &obstacle: obstacles) {
        Intersection inter = boost::apply_visitor(IntersectVisitor(obstacle), ray_segment);
        if (inter) {
            ray_segment = boost::apply_visitor(SmallerSegmentVisitor(ray.source()), *inter);
        }
    }

    boost::apply_visitor(print_result, ray_segment);
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
