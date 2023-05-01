#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
#include <stack>
#include <unordered_map>
#include "utils.hpp"
#include <iostream>


class Graph {
    protected:
        int num_vertices;
        int num_edges;

        virtual void dfs(int v, std::vector<int>& visited) = 0;  
    public:
        Graph(int num_vertices) {
            this->num_vertices =  num_vertices;
        }

        Graph(int num_vertices, int edges) {
            this->num_vertices = num_vertices;
            this->num_edges = edges;
        }

        virtual void insertEdge(int u, int v) = 0;
        virtual void insertEdge(int v, std::vector<int> vertexes) = 0;
        virtual void deleteEdge(int u, int v) = 0;
        virtual std::vector<int> getAdjacentVertices(int v) = 0;
        virtual std::unordered_map<int, int> outdegree() = 0;
        virtual std::unordered_map<int, int> degree() = 0;
        virtual Graph* getInducedSubgraph(std::vector<int> removedVertices) = 0;
        virtual void to_string() = 0;
        
        int connectedComponents() {

            std::vector<int> visited(this->num_vertices);
            
            int comp = 0;
            for (int i=0; i<this->num_vertices; i++) {
                if(!visited[i]) {
                    comp++;
                    dfs(i, visited);
                }
            }
            return comp;
        }
        
        bool hasEulerianCircuit() {
            std::unordered_map<int, int> odg = outdegree();
            for (int i=0; i<this->num_vertices; i++) {
                if (odg[i]&1) {
                    return false;
                }
            } 

            return true;
        }

        std::vector<int> eulerianCircuit() {
            if (!hasEulerianCircuit()) {
                return std::vector<int>(1);
            }

            std::unordered_map<int, int> outs = outdegree();
            std::stack<int> currentPath;
            std::vector<int> circuit;

            currentPath.push(0);
            int currentVertex = 0;

            while (!currentPath.empty()) {
                if (outs[currentVertex]) {
                    currentPath.push(currentVertex);

                    std::vector<int> adjacent = getAdjacentVertices(currentVertex);

                    int nextVertex = adjacent[0];

                    outs[currentVertex]--;
                    deleteEdge(currentVertex, nextVertex);

                    deleteEdge(nextVertex, currentVertex);
                    outs[nextVertex]--;

                    currentVertex = nextVertex;
                } else {
                    circuit.push_back(currentVertex);

                    currentVertex = currentPath.top();
                    currentPath.pop();
                }
            }

            return circuit;
        }
        
        
        bool checkHamiltonianRule() {
            std::vector<int> v;

            for (int i=0; i<this->num_vertices; i++) v.push_back(i);
            std::vector<std::vector<int>> subsets = utils::getSubsets(v, v.size());

            for (std::vector<int> ss: subsets) {
                std::cout << ss.size() << std::endl;
                if (ss.size() > 0 && ss.size() < this->num_vertices) {
                    Graph *inducedSubgraph = getInducedSubgraph(ss);

                    int numComponents = inducedSubgraph->connectedComponents();

                    std::cout << numComponents << std::endl;

                    if (numComponents > ss.size()) return false;
                }
            }

            return true;
        }
    
};

#endif
