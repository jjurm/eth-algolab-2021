#include <iostream>
#include <vector>

#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::property<boost::vertex_distance_t, int>, boost::property<boost::edge_weight_t, int>> Graph;
typedef boost::property_map<Graph, boost::edge_weight_t>::type WeightMap;
typedef boost::graph_traits<Graph>::edge_descriptor EdgeDesc;
typedef boost::graph_traits<Graph>::vertex_descriptor VertexDesc;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;

void computeMinSpanning(Graph& G, std::vector<VertexDesc>& pred, VertexDesc& s) {
    //std::cerr << "Called min span tree" << std::endl;
    int n = boost::num_vertices(G);
    std::vector<int> indexMap(n);
    std::vector<int> distanceMap(n);
    boost::prim_minimum_spanning_tree(G, s, &pred[0], 
        boost::get(boost::vertex_distance, G), 
        boost::get(boost::edge_weight, G), 
        boost::get(boost::vertex_index, G), 
        boost::default_dijkstra_visitor());
}

void testcase() {
    int n, e, s, a, b; std::cin >> n >> e >> s >> a >> b;
    
    //std::cerr << "n: " << n << " e: " << e << " s: " << s << " a: " << a << " b: " << b << "\n";

    std::vector<Graph> graphs(s);
    std::vector<WeightMap> weights(s);

    for (int i = 0; i < s; i++) {
        graphs.at(i) = Graph(n);
        weights.at(i) = boost::get(boost::edge_weight, graphs.at(i));
    }
    
    //std::cerr << "Constructed graphs\n";

    for (int i = 0; i < e; i++) {
        int u, v; std::cin >> u >> v;
        for (int j = 0; j < s; j++) {
            int w; std::cin >> w;
            EdgeDesc e = boost::add_edge(u, v, graphs.at(j)).first;
            weights.at(j)[e] = w;
        }
    }

    std::vector<VertexDesc> startingPoints(s);
    for(int i = 0; i < s; i++) {
        int w; std::cin >> w;
        startingPoints.at(i) = w; 
    }
    

    Graph G(n);
    WeightMap weight = boost::get(boost::edge_weight, G);
    for (int j = 0; j < s; j++) {
        std::vector<VertexDesc> p(n);
        //std::cerr << "Calling min spanning tree\n";
        computeMinSpanning(graphs.at(j), p, startingPoints.at(j));
        //std::cerr << "Computed min spanning tree for " << j << " and starting point is " << startingPoints.at(j) << "\n";
        for (int i = 0; i < n; i++) {
            //std::cerr << "Pred of " << i << " is " << p[i] << "\n";
            if(p[i] != i) {
                if (boost::edge(p[i], i, G).second) {
                    EdgeDesc e = boost::edge(p[i], i, G).first;
                    EdgeDesc eW = boost::edge(p[i], i, graphs.at(j)).first;
                    int weightT = weights.at(j)[eW];
                    if (weightT < weight[e]) {
                        weight[e] = weightT;
                    }
                } else {
                    EdgeDesc e = boost::add_edge(p[i], i, G).first;
                    EdgeDesc eW = boost::edge(p[i], i, graphs.at(j)).first;
                    weight[e] = weights.at(j)[eW];
                    //std::cerr << "Weight of e is " << weights.at(j)[eW] << "\n";
                }
            } 
        }
    }
    
    EdgeIterator ei, end;

    //std::cerr << "\n";
    //std::cerr << "Graph G:\n";
    for (boost::tie(ei, end) = boost::edges(G); ei != end; ei++) {
        //std::cerr << *ei << " with weight " << weight[*ei] << "\n";
    }
    //std::cerr << "\n";

    std::vector<int> distances(n);
    boost::dijkstra_shortest_paths(G, a,
        boost::distance_map(boost::make_iterator_property_map(
            distances.begin(), boost::get(boost::vertex_index, G)
        ))
    );
    
    for (int i = 0; i < n; i++) {
      //std::cerr << "i: " << i << " d: " << distances[i] << "\n";
    }

    std::cout << distances[b] << "\n";
    //std::cerr << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    //std::cerr << "Number of testcases: " << t << "\n";
    while(t--) testcase();
}