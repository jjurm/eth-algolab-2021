#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>
#include <algorithm>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_index_t, int>> graph;
typedef boost::property_map<graph, boost::edge_index_t>::type PM;
typedef boost::graph_traits<graph>::edge_iterator edge_iter;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor v_desc;

bool cmp(const edge_desc& e1, const edge_desc& e2) {
    if (e1.m_source != e2.m_source) return e1.m_source < e2.m_source;
    else return e1.m_target < e2.m_target;
}

void testcase() {
    int n, m; std::cin >> n >> m;
    graph G(n);

    for (int i = 0; i < m; i++) {
        int u, v; std::cin >> u >> v;
        if (u > v) {
          boost::add_edge(v, u, G);
        } else {
          boost::add_edge(u, v, G);
        }
        
        //std::cerr << "Added edge: " << e << " with u: " << u << " and v: " << v << "\n";
    }

    PM property_map = boost::get(boost::edge_index, G);
    int n_comp = boost::biconnected_components(G, 
        property_map
    );
    
    //std::cerr << "There are/is " << n_comp << " component(s\n";

    std::vector<std::vector<edge_desc>> components(n_comp);
    edge_iter ei, end;
    boost::tie(ei, end) = boost::edges(G);

    for (; ei != end; ei++) {
        int comp = property_map[*ei];
        //std::cerr << *ei << " belongs to comp: " << comp << "\n";
        components.at(comp).push_back(*ei);
    }

    std::vector<edge_desc> bridges;

    for (int i = 0; i < n_comp; i++) {
        if(components[i].size() == 1) {
            bridges.push_back(components[i][0]);
        }
    }

    std::sort(bridges.begin(), bridges.end(), cmp);
    
    std::cout << bridges.size() << "\n";
    
    for (auto bi = bridges.begin(); bi != bridges.end(); bi++) {
        std::cout << (*bi).m_source << " " << (*bi).m_target << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t;
    std::cin >> t;
    for (; t > 0; t--) {
        testcase();
    }
}