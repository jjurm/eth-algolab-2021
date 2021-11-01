#include <iostream>
#include <vector>
#include <set>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef std::vector<std::set<std::string>> VSS;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor VertexDesc;


void constructGraph(const VSS& cV, int f, Graph& G) {
    int n = cV.size();
    int c = cV.at(0).size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            std::vector<std::string> res;
            std::set_intersection(
                cV.at(i).begin(), cV.at(i).end(), cV.at(j).begin(), cV.at(j).end(), 
                std::inserter(res, res.begin()));
            if (res.size() > f) {
                boost::add_edge(i, j, G);
            }
        }
    }
}

void testcase() {
    int n, c , f; std::cin >> n >> c >> f;
    VSS cV(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < c; j++) {
            std::string ch; std::cin >> ch;
            cV.at(i).insert(ch);
        }
    }

    Graph G(n);
    constructGraph(cV, f, G);

    std::vector<VertexDesc> matching(n);
    boost::edmonds_maximum_cardinality_matching(G,
        boost::make_iterator_property_map(matching.begin(), boost::get(boost::vertex_index, G))
    );

    int size = boost::matching_size(
        G,
        boost::make_iterator_property_map(matching.begin(), boost::get(boost::vertex_index, G))
    );

    if (size == n/2) {
        std::cout << "not optimal\n";
    } else {
        std::cout << "optimal\n";
    }
    
    
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}