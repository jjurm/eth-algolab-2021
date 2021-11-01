///1
#include <iostream>
#include <vector>
#include <limits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> Graph;
typedef boost::graph_traits<Graph>::edge_descriptor EdgeDesc;
typedef boost::graph_traits<Graph>::vertex_descriptor VertexDesc;
typedef boost::property_map<Graph, boost::edge_weight_t>::type WeightMap;

typedef std::vector<VertexDesc> VV;

int addTPEdges(const VV& TPNetwork, Graph& G) {
    int n = boost::num_vertices(G);
    std::vector<int> components(n);
    int comps = boost::strong_components(G, 
        boost::make_iterator_property_map(components.begin(), boost::get(boost::vertex_index, G)));

    int sizeNetwork = TPNetwork.size();

    std::vector<int> cost(comps, 0); 

    WeightMap weights = boost::get(boost::edge_weight, G);

    for (int i = 0; i < sizeNetwork; i++) {
        cost.at(components.at(TPNetwork.at(i)))++;
    }
    
    for (int i = 0; i < comps; i++) {
      //std::cerr << "Members of network: " << cost[i] << "\n";
    }

    for (int i = 0; i < sizeNetwork; i++) {
        int v = TPNetwork[i];
        int component = components[v];
        if (cost[component] > 1) {
            int hubVertex = n + component;
            EdgeDesc e1 = boost::add_edge(v, hubVertex, G).first;
            weights[e1] = 0;
            EdgeDesc e2 = boost::add_edge(hubVertex, v, G).first;
            weights[e2] = cost.at(component) - 1;
        }
    }
    
    return comps;
}

void testcase() {
    //std::cerr << "--------------------------------------------------\n";
    int n, m, k, T; std::cin >> n >> m >> k >> T;
    VV TPNetwork(T);
    for (int i = 0; i < T; i++) {
        int v; std::cin >> v;
        TPNetwork[i] = v;
    } 

    Graph G(n);
    WeightMap weights = boost::get(boost::edge_weight, G);

    for (int i = 0; i < m; i++) {
        int u, v, w; std::cin >> u >> v >> w;
        EdgeDesc e = boost::add_edge(v, u, G).first;
        weights[e] = w;
    }

    int extra = addTPEdges(TPNetwork, G);
    
    std::vector<int> distanceMap(n + extra);
    //std::cerr << "n:" << n << "\n";
    boost::dijkstra_shortest_paths(
        G, n-1, 
        boost::distance_map(boost::make_iterator_property_map(distanceMap.begin(), boost::get(boost::vertex_index, G)))
    );

    int min = INT_MAX;

    for (int i = 0; i < k; i++) {
        if (distanceMap.at(i) < min) {
            min = distanceMap.at(i);
        }
    }

    if (min > 1000000) {
        std::cout << "no\n";
    } else {
        std::cout << min << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}