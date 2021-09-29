// cpp_intro/bfs
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

int n,m,v,x,y;
VVI adj;
VI dist;
queue<int> q;

void testcase() {
    cin >> n >> m >> v;
    adj = VVI(n, VI(0));
    REP(i,m) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dist = VI(n,-1);

    q.push(v); dist[v] = 0;
    while (q.size() > 0) {
        int a = q.front(); q.pop();
        for (int b : adj[a]) {
            if (dist[b] == -1) {
                q.push(b);
                dist[b] = dist[a] + 1;
            }
        }
    }

    for (int d : dist) {
        cout << d << ' ';
    }
    cout << endl;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
