///1
#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <climits>
#include <algorithm>

typedef std::pair<long, long> movement_t;
typedef std::vector<movement_t> VM;
typedef std::vector<VM> VMM;
typedef std::vector<long> VL;

long D, T;

bool sortForTime(const movement_t& a, const movement_t& b) {
    if (a.second == b.second) return a.first > b.first;
    return a.second < b.second;
}

void printVector(const VM& vec) {
    for (auto it = vec.begin(); it != vec.end(); it++) {
        ////std::cerr << "(" << it->first << ", " << it->second << ")";
    }
    ////std::cerr << "\n";
}

void calcAllMoves(int n, int offset, const VM& movements, VMM& moves) {
    int max = std::pow(2, n);
    for (int i = 0; i < max; i++) {
        long T2 = T, D2 = D;
        int size = 0;
        for (int j = 0; j < n; j++) {
            int last = (i >> j) & 1;
            if (last == 1) {
                ////std::cerr << 1;
                T2 -= movements[offset + j].second;
                D2 -= movements[offset + j].first;
                size++;
            } else {
                ////std::cerr << 0;
            }
            
        }
        ////std::cerr << "\n";
        
        if (T2 > 0) {
            moves[size].push_back(movement_t(D2, T2));
        }
    }
}

void prepMoves(VMM& vec) {
    ////std::cerr << "Sorting and removing...\n";
    for (VM& v : vec) {
        if (v.size() <= 1) {
          continue;
        }
        std::sort(v.begin(), v.end(), sortForTime);

        long min = v.back().first;
        std::vector<bool> keepElement(v.size(), true);
        for (int i = v.size() - 2; i >= 0; i--) {
            if (v[i].first >= min) {
                keepElement[i] = false;
            } else {
                min = v[i].first;
            }
        }

        int i = 0;
        for (int j = 0; j < (int) v.size(); j++) {
            if (keepElement[j]) {
                v[i] = v[j];
                i++;
            }
        }
        v.resize(i);
    }
}

void testcase() {
    ////std::cerr << "------------------------------------------\n";
    int n, m; std::cin >> n >> m >> D >> T;
    VM movements(n);
    VL potions(m);
    VL best(n + 1, LONG_MAX);

    for (int i = 0; i < n; i++) {
        long d, t; std::cin >> d >> t;
        movements[i] = movement_t(d, t);
    }

    for (int i = 0; i < m; i++) {
        long s; std::cin >> s;
        potions[i] = s;
    }

    int firstHalfSize = (n + 1)/2;
    int secondHalfSize = n - firstHalfSize;

    VMM firstHalf(firstHalfSize + 1), secondHalf(secondHalfSize + 1);

    calcAllMoves(firstHalfSize, 0, movements, firstHalf);
    calcAllMoves(secondHalfSize, firstHalfSize, movements, secondHalf);

    prepMoves(firstHalf);
    prepMoves(secondHalf);

    ////std::cerr << "Sorted vectors\n";

    for (int i = 0; i <= firstHalfSize; i++) {
        for (const movement_t& mI : firstHalf[i]) {
            for (int j = 0; j <= secondHalfSize; j++) {
                const VM& mJs = secondHalf[j];
                auto upper = std::upper_bound(mJs.begin(), mJs.end(), T - mI.second, [](const long val, const movement_t& elem){
                    return val < elem.second;
                });

                if (upper == mJs.end()) {
                    break;
                }

                int mUsed = i + j;
                long bestLocal = best[mUsed];
                bestLocal = std::min(bestLocal, mI.first + upper->first - D);
                
                best[mUsed] = bestLocal;
            }
            
        }
    }

    long bestPot = LONG_MAX;
    for (int i = 1; i <= n; i++) {
        if (best[i] <= 0) {
            std::cout << "0\n";
            return;
        } else {
            long needed = (best[i] - 1)/i + 1;
            auto lower_it = std::lower_bound(potions.begin(), potions.end(), needed);
            if (lower_it != potions.end()) {
                bestPot = std::min(bestPot, lower_it - potions.begin() + 1);
            }
        }
    }

    if (bestPot == LONG_MAX) {
        std::cout << "Panoramix captured\n";
    } else {
        std::cout << bestPot << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}