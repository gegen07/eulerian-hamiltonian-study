#ifndef __ADJ_MATRIX_H__
#define __ADJ_MATRIX_H__

#include "graph.hpp"
#include "doubly-linked-list.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
#include <unordered_map>
#include <stack>

class AdjMatrix : public Graph {
    private:
        std::vector<std::vector<int>> adj;

    protected:
        void dfs(int v, std::vector<int>& visited) override {
            visited[v] = 1;
            for (int i=0; i<this->num_vertices; i++) {
                // std::cout << adj[v][i] << std::endl;
                if (adj[v][i]) {
                    v = i;
                    if (!visited[v]) dfs(v, visited);
                }
            }
        }
    public:
        AdjMatrix(int num_vertices) : Graph(num_vertices) {
            this->adj.resize(num_vertices, std::vector<int>(num_vertices));
        }

        ~AdjMatrix() {
        }

        void insertEdge(int u, int v) override {
            adj[u][v] += 1;
        }

        void insertEdge(int v, std::vector<int> vertexes) override {
            for (int u: vertexes) {
                insertEdge(v, u);
            }
        }

        void deleteEdge(int u, int v) override {
            adj[u][v]--;
        }

        std::vector<int> getAdjacentVertices(int v, int& op) override {
            std::vector<int> adjacents;

            for (int i=0; i<adj[v].size(); i++) {
                if (adj[v][i] > 0 && i != v) { adjacents.push_back(i); }
                op+=2;
            }

            return adjacents;
        }

        Graph* getInducedSubgraph(std::vector<int> removedVertices, int& op) override {

            Graph *inducedSubgraph = new AdjMatrix(this->num_vertices - removedVertices.size());

            std::unordered_map<int, bool> rmv;
            for (int i=0; i < this->num_vertices; i++) rmv[i] = false;
            for (int i=0; i < removedVertices.size(); i++) rmv[i] = true;

            std::vector<int> offset(this->num_vertices-removedVertices.size());
            if (rmv[0]) offset[0] = 1;
            for (int i=1; i<this->num_vertices; i++) {
                offset[i] = offset[i-1];
                if (rmv[i]) offset[i]+=1;
            }


            int new_size = this->num_vertices - removedVertices.size();
            int j=0;
            // std::cout << "induced subgraph created" << std::endl;
            for (int i=0; i<adj.size(); i++) {
                if (!rmv[i]) {
                    for (int k=0; k<adj[i].size(); k++) {
                        if (adj[i][k] >= 1 and !rmv[k]) {
                            inducedSubgraph->insertEdge(j, k-offset[k]);
                            // std::cout << j << " " << k << " " << offset[k] << std::endl;
                        }
                        op+=2;
                    }
                    j++;
                }
                op+=1;
            }

            return inducedSubgraph;
        }
        
        void to_string() override {
            for (int i =0; i<adj.size(); i++) {
                for (int j=0; j<adj[i].size(); j++) {
                    std::cout << adj[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

        std::unordered_map<int, int> outdegree() override {
            std::unordered_map<int, int> outs;

            for (int i=0; i < num_vertices; i++) {
                for (int j=0; j < num_vertices; j++) {
                    outs[i] += adj[i][j];
                }
            }

            return outs;
        }

        std::unordered_map<int, int> degree() override {
            std::unordered_map<int, int> outs;

            for (int i=0; i < num_vertices; i++) {
                for (int j=0; j < num_vertices; j++) {
                    outs[i] += adj[i][j];
                }
            }

            return outs;
        }


};

#endif
