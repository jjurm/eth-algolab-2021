// week_02/the_great_game
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


void dfs(int u, VVI& e, vector<bool>& visited, VI& out) {
    visited[u] = true;
    for (int v : e[u]) {
        if (visited[v]) continue;
        dfs(v, e, visited, out);
    }
    out.push_back(u);
}

void testcase() {
    // Holmes wants to speed up the red meeple and slow down the black one; Moriarty vice versa.
    // Each colour corresponds to separate game and its best strategy (for both players) does not depend on the state of
    // the other game. We are interested only in the number of turns each game will take.
    // The continuation of a game depends only on: the colour, the meeple's position, and who's turn it is.

    int n, m, r, b;
    cin >> n >> m >> r >> b; r--; b--;
    VVI e(n, VI(0));
    REP(i, m) {
        int u, v;
        cin >> u >> v;
        e[u-1].push_back(v-1);
    }

    // topological sort
    VI topo;
    vector<bool> visited(n, false);
    REP(i, n) if (!visited[i]) dfs(i, e, visited, topo);
    assert(topo[0] == n-1);

    // For each { vertex, maximizer/minimizer }, store { time (# of turns) it will take for the meeple to reach target }
    VVI dt(n, VI(2, 0));

    bool visited_r = false, visited_b = false; // for early cutting
    for (auto it = topo.cbegin() + 1; it < topo.cend(); it++) {
        REP(p, 2) {
            int best_time = -1;
            for (int v : e[*it]) {
                int potential_time = 1 + dt[v][1 - p];
                best_time = (best_time == -1)
                        ? potential_time
                        : (p ? min(potential_time, best_time) : max(potential_time, best_time));
            }
            dt[*it][p] = best_time;
        }
        if ((visited_r |= *it == r) && (visited_b |= *it == b)) break; // early cutting
    }

    // Finally, look at who's meeple is quicker (taking double turns and Holmes' first-turn advantage into account)
    cout << ( dt[r][1] / 2 >= (dt[b][1] + 1) / 2 ) << endl;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
