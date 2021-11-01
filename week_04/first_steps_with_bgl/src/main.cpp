#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <vector>

using graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS,
  boost::no_property,
  boost::property<boost::edge_weight_t, int>>;
  
typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;

int max_distance(graph& G) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);
  
  boost::dijkstra_shortest_paths(G, 0, 
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G)))
    );
  
  int max = -1;
  for (int i = 0; i < n; i++) {
    if (dist_map[i] > max) {
      max = dist_map[i];
    }
  }
  
  return max;
} 
  
int kruskal(graph& G) {
  std::vector<edge_desc> mst;
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  weight_map weights = boost::get(boost::edge_weight, G);
  
  int weight = 0;
  for (auto it = mst.begin(); it != mst.end(); it++) {
    weight += weights[*it];
  }
  
  return weight;
}

void testcase() {
  int n, m;
  std::cin >> n >> m;
  
  graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  
  for (int i = 0; i < m; i++) {
    int u, v, w; std::cin >> u >> v >> w;
    edge_desc e = boost::add_edge(u, v, G).first;
    weights[e] = w;
  }
  
  std::cout << kruskal(G) << " " << max_distance(G) << "\n";
}

int main() {
  int t;
  std::cin >> t;
  
  for (; t > 0; t--) {
    testcase();
  }
}