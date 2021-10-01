// week_02/defensive_line
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

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)

using namespace std;

typedef long long int LL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;


void testcase() {
    int n, m, k, t, last = 0, sum = 0;
    cin >> n >> m >> k;

    // 1. phase: compute the list of valid intervals (using a sliding window), sorted by endpoint
    VI v;
    VPII intervals;
    REP(i, n) {
        cin >> t;
        v.push_back(t);
        sum += t;
        while (sum > k) sum -= v[last++];
        if (sum == k) intervals.push_back(make_pair(last, i));
    }
    if (intervals.empty()) {
        cout << "fail" << endl; // edge case
        return;
    }
    sort(intervals.begin(), intervals.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

    // 2. phase: map each interval beginning to the latest previous end of another interval
    int n_intervals = (int) intervals.size();
    VI prev_end_for_beginning_of(n_intervals, -1);

    // for this, we also need to sort the intervals by beginning
    VPII interval_beginnings; // { interval index, beginning_pos }
    REP(i, n_intervals) interval_beginnings.push_back(make_pair(i, intervals[i].first));
    sort(interval_beginnings.begin(), interval_beginnings.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

    int current_interval = 0;
    REP(i, n_intervals) {
        while (interval_beginnings[current_interval].second <= intervals[i].second &&
               current_interval < n_intervals) {
            prev_end_for_beginning_of[current_interval++] = i - 1;
            // (first few intervals will have the value -1, because there are no preceding interval ends)
        }
    }
    while (current_interval < n_intervals) prev_end_for_beginning_of[current_interval++] = n - 1;

    // 3. phase: get the largest disjoint subset of the intervals (largest in terms of sum of sizes of the intervals),
    // using dynamic programming

    // dt[ interval index ][ (# of available attackers) - 1 ] = max value of a legal strategy on intervals that end
    // before or at the end of interval at {interval index}
    VVI dt(n_intervals, VI(0));
    REP(i, n_intervals) {
        int prev_interval = prev_end_for_beginning_of[i];
        int max_attackers_before = prev_interval == -1 ? 0 : (int) dt[prev_interval].size();
        REP(j, min(max_attackers_before + 1, m)) {
            // for each entry in the table, either the solution will involve using the current interval (i) or not
            int current_size = (intervals[i].second - intervals[i].first + 1);
            dt[i].push_back(
                    max(
                            // using the interval i
                            // (adding the current interval size to the previously accumulated score, if any)
                            ((prev_interval != -1 && j >= 1) ? dt[prev_interval][j - 1] : 0)
                            + current_size,
                            // or not using the interval i (if legal)
                            (i >= 1 && ((int) dt[i - 1].size()) > j) ? dt[i - 1][j] : INT_MIN
                    )
            );
        }
    }

    if (((int) dt[n_intervals - 1].size()) < m) {
        cout << "fail" << endl;
    } else {
        cout << dt[n_intervals - 1][m - 1] << endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
