#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

typedef std::pair<int, int> boat_t;
typedef std::vector<std::pair<int, int>> VI;

void testcase() {
    int n; std::cin >> n;
    VI boats(n);
    
    for (int i = 0; i < n; i++) {
        int l, p; std::cin >> l >> p;
        boats[i] = boat_t(p, l); 
    }
    std::sort(boats.begin(), boats.end());
    // for (boat_t t : boats) {
    //   std::cerr << "(" << t.second << ", " << t.first << ") "; 
    // }
    // std::cerr << "\n";
    int sum = 1;
    int new_right = INT_MAX;
    int right = boats[0].first;

    for (int i = 1; i < n; i++) {
        for (; i < n && boats[i].first < right; i++);
        int j = i;
        if (i >= n) break;
        int prov = -1;
        for(; j < n && boats[j].first <= new_right; j++) {
            int tmp = std::max(boats[j].first, right + boats[j].second);
            if (tmp < new_right) {
              new_right = tmp;
              prov = j;
            }
        }  
        right = new_right;
        new_right = INT_MAX;
        i = prov;
        sum++;
    }

    std::cout << sum << "\n";

}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}