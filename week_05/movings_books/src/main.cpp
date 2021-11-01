#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<int> VI;

void testcase() {
    int n, m; std::cin >> n >> m;
    VI friends_strength(n);
    for (int i = 0; i < n; i++) {
        std::cin >> friends_strength[i];
    }
    VI boxes_weight(m);
    for (int i = 0; i < m; i++) {
        std::cin >> boxes_weight[i];
    }

    std::sort(friends_strength.begin(), friends_strength.end());
    std::sort(boxes_weight.begin(), boxes_weight.end());

    if (friends_strength[n-1] < boxes_weight[m-1]) {
        std::cout << "impossible\n";
        return;
    }

    VI amount_carrying(n, 0);
    int currentWeight = boxes_weight[m-1];
    int left = n - 2;
    int nextCarrier = n - 1;

    while (friends_strength[left] >= currentWeight) left--;


    for (int i = m-1; i >= 0; i--) {
        if (boxes_weight[i] < currentWeight) {
            currentWeight = boxes_weight[i];
            int old_left = left;
            while (friends_strength[left] >= currentWeight) left--;
            if (old_left > left && nextCarrier == n - 1) {
              nextCarrier = old_left;
            } 
        }

        if (nextCarrier == n - 1) {
            amount_carrying[nextCarrier]++;
            nextCarrier--;
        } else {
            amount_carrying[nextCarrier]++;
            if (amount_carrying[nextCarrier] == amount_carrying[nextCarrier + 1]) {
                nextCarrier--;
            }
        }

        if (left == nextCarrier) {
            nextCarrier = n - 1;
        }
    }
    

    std::cout << amount_carrying[n-1] * 3 - 1 << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}