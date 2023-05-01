#include "lib/graph-adj-list.hpp"
#include "lib/graph-adj-matrix.hpp"
#include "lib/graph-incidency-matrix.hpp"
#include "lib/graph.hpp"
#include <ios>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

std::vector<std::vector<int>> read_input() {
    std::ifstream file;
    
    file.open("./generators/graph-15.txt");
    
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


Graph * createAdjMatrixFromFile(std::string filename) {
    std::vector<std::vector<int>> graph = read_input();
    int num_vertices = graph.size();

    Graph* adj = new AdjMatrix(num_vertices);

    for (int i=0; i<graph.size(); i++) adj->insertEdge(i, graph[i]);

    return NULL;
}

Graph * createAdjListFromFile(std::string filename) {
    std::vector<std::vector<int>> graph = read_input();
    int num_vertices = graph.size();

    Graph* adj = new AdjList(num_vertices);

    for (int i=0; i<graph.size(); i++) adj->insertEdge(i, graph[i]);

    return adj;
}

Graph * createIncMatrixFromFile(std::string filename) {
    std::vector<std::vector<int>> graph = read_input();
    int num_vertices = graph.size();
    int num_edges = 0;
   
    for (int i=0; i<graph.size(); i++) num_edges += graph[i].size();

    return NULL; // TODO
}


int main() {
    // std::vector<std::vector<int>> graph = read_input();

    // for (int i=0; graph.size(); i++) {
    //     for (int j=0; j<graph[i].size(); j++) {
    //         std::cout << graph[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // Graph *g = new IncMatrix(3, 4);

    // Graph *g = new AdjList(3);

    // g->insertEdge(0, {1, 2});
    // g->insertEdge(1, {0, 2});
    // g->insertEdge(2, {0, 1});
    // // g->insertEdge(3, 0);

    // g->to_string();

    Graph * g = createAdjListFromFile("./generators/graph-15.txt");

    std::vector<int> circuit = g->eulerianCircuit();

    for (int i=circuit.size()-1; i >= 0; i--) {
        std::cout << circuit[i];

        if (i) std::cout << " - ";
    }
    std::cout << std::endl;

    bool check = g->checkHamiltonianRule();

    if (check) {
        std::cout << "É hamiltoniano" << std::endl;
    } else {
        std::cout << "Inconclusivo" << std::endl;
    }

    return 0;
}