// cpp_intro/dfs
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

int n,m,v,x,y,t;
VVI adj;
VI entry, finish;

void dfs(int v) {
    entry[v] = t; t++;
    sort(adj[v].begin(), adj[v].end());
    for (auto w : adj[v]) {
        if (entry[w] == -1) {
            dfs(w);
        }
    }
    finish[v] = t; t++;
}

void testcase() {
    cin >> n >> m >> v;
    adj = VVI(n, VI(0));
    REP(i,m) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    entry = VI(n,-1); finish = VI(n,-1);
    t=0;

    dfs(v);
    for (int d : entry) {
        cout << d << ' ';
    }
    cout << '\n';
    for (int d : finish) {
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
