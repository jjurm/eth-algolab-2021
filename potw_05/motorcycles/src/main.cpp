#include <iostream>
#include <vector>
#include <CGAL/Gmpq.h>
#include <algorithm>
#include <tuple>

using G = CGAL::Gmpq;
using T = std::tuple<long, int, G>;

G calcSlope(long x, long y1, long y2) {
  G slope(y2 - y1, x);
  return slope;
}

void testcase() {
  //std::cerr << "-----------------------------------------------------------\n";
  int n; 
  std::cin >> n;
  
  std::vector<T> bikers(n);
  for (int i = 0; i < n; i++) {
    long y1, x, y2; std::cin >> y1 >> x >> y2;
    //std::cerr << "In is y1: " << y1 << " x: " << x << " y2: " << y2 << "\n";
    bikers[i] = T(y1, i, calcSlope(x, y1, y2));
  }
  
  std::sort(bikers.begin(), bikers.end());
  
  std::vector<bool> sol(n, true);
  G best = std::get<2>(bikers[0]);
  //std::cerr << "Start with " << best << "\n";
  for (int i = 1; i < n; i++) {
    //std::cerr << "y0: " << std::get<0>(bikers[i]) << "\n";
    auto slope = std::get<2>(bikers[i]);
    auto absBest = CGAL::abs(best);
    auto absSlope = CGAL::abs(slope);
    if (absBest > absSlope || (absBest == absSlope && slope > best)) {
      //std::cerr << "Found new best slope: " << absSlope << " instead of " << absBest << "\n";
      best = slope;
    } else if (slope < best) {
      //std::cerr << "Biker " << std::get<1>(bikers[i]) << " stops driving\n";
      sol[std::get<1>(bikers[i])] = false;
    }
  }
  
  best = std::get<2>(bikers.back());
  //std::cerr << "Start with " << best << "\n";
  for (int i = n-2; i >= 0; i--) {
    auto slope = std::get<2>(bikers[i]);
    auto absBest = CGAL::abs(best);
    auto absSlope = CGAL::abs(slope);
    if (absBest >= absSlope) {
      //std::cerr << "Found new best slope: " << absSlope << " instead of " << absBest << "\n";
      best = slope;
    } else if (slope > best) {
      //std::cerr << "Biker " << std::get<1>(bikers[i]) << " stops driving\n";
      sol[std::get<1>(bikers[i])] = false;
    }
  }
  
  for (int i = 0; i < n; i++) {
    if (sol[i]) {
      std::cout << i << " ";
    }
  }
  
  std::cout << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  int t;
  std::cin >> t;
  for (; t > 0; t--) {
    testcase();
  }
}