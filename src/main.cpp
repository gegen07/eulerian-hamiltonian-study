#include "lib/graph-adj-list.hpp"
#include "lib/graph-adj-matrix.hpp"
#include "lib/graph-incidency-matrix.hpp"
#include "lib/graph.hpp"
#include <ios>
#include <iostream>
#include <ostream>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>


struct stat {
    int op;
    long vertices;
    long edges;
}; 

std::vector<std::vector<int>> read_input(std::string filename) {
    std::ifstream file;
    
    file.open(filename);
    
    std::vector<std::vector<int>> graph;

    if (file.is_open()) {
        std::string line;
        while(getline(file, line)) {
            std::vector<int> edges;
            
            std::stringstream ss(line);
            std::string s;
            while (getline(ss, s, ',')) {
                edges.push_back(std::stoi(s));
            }  

            graph.push_back(edges);
        }
        file.close();
    }

    return graph;
}


Graph * createAdjMatrixFromFile(std::string filename, struct stat& stats) {
    std::vector<std::vector<int>> graph = read_input(filename);
    int num_vertices = graph.size();

    stats.vertices = num_vertices;

    int edges = 0;
    for (int i=0; i<graph.size(); i++) edges += graph[i].size();
    
    stats.edges = edges;

    Graph* adj = new AdjMatrix(num_vertices);

    for (int i=0; i<graph.size(); i++) adj->insertEdge(i, graph[i]);

    return adj;
}

Graph * createAdjListFromFile(std::string filename, struct stat& stats) {
    std::vector<std::vector<int>> graph = read_input(filename);
    int num_vertices = graph.size();

    stats.vertices = num_vertices;

    int edges = 0;
    for (int i=0; i<graph.size(); i++) edges += graph[i].size();
    
    stats.edges = edges;

    Graph* adj = new AdjList(num_vertices);

    for (int i=0; i<graph.size(); i++) adj->insertEdge(i, graph[i]);

    return adj;
}

Graph * createIncMatrixFromFile(std::string filename, struct stat& stats) {
    std::vector<std::vector<int>> graph = read_input(filename);

    std::set<std::pair<int, int>> gSet;

    for (int i=0; i<graph.size(); i++) {
        for (int j=0; j<graph[i].size(); j++) {
            gSet.insert({std::max(i, graph[i][j]), std::min(i, graph[i][j])});
        }
    }

    int num_vertices = graph.size();
    int num_edges = gSet.size();

    stats.vertices = num_vertices;
    stats.edges = num_edges;
    
    Graph* g = new IncMatrix(num_vertices, num_edges);

    for (auto p: gSet) {
        g->insertEdge(p.first, p.second);
    }

    return g;
}

void save_stats_eulerian() { 
    std::vector<struct stat> stats;

    for (int i=3; i<50; i++) {
        struct stat st;

        std::string s = "./generators/eulerian/graph-" + std::to_string(i) + ".txt";
        Graph * g = createAdjMatrixFromFile(s, st);

        int op;

        std::vector<int> circuit = g->eulerianCircuit(st.op); 

        for (int i=circuit.size()-1; i >= 0; i--) {
            std::cout << circuit[i];

            if (i) std::cout << " - ";
        }

        std::cout << std::endl;

        stats.push_back(st);
    }

    std::ofstream out("adjacency_matrix_eulerian.csv");

    out << "v,e,op" << std::endl;
    for (stat s: stats) {
        out << s.vertices << "," << s.edges << "," << s.op << std::endl;
    }
}

void save_stats_hamiltonian() {
    std::vector<struct stat> stats;

    for (int i=14; i<15; i++) {
        struct stat st;

        std::cout << i << std::endl;

        std::string s = "./generators/hamiltonian/graph-" + std::to_string(i) + ".txt";
        Graph * g = createAdjMatrixFromFile(s, st);

        int op;

        bool check = g->checkHamiltonianRule(st.op);

        if (check) {
            std::cout << "É hamiltoniano" << std::endl;
        } else {
            std::cout << "Inconclusivo" << std::endl;
        }

        std::cout << std::endl;

        stats.push_back(st);
    }

    std::ofstream out("../analysis/adjacency_matrix_hamiltonian.csv");

    out << "v,e,op" << std::endl;
    for (stat s: stats) {
        out << s.vertices << "," << s.edges << "," << s.op << std::endl;
    }
}


int main() {    
    save_stats_hamiltonian();

    return 0;
}