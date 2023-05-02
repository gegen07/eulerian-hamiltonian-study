#ifndef __INC_MATRIX_H__
#define __INC_MATRIX_H__

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
#include <map>

class IncMatrix : public Graph {
    private:
        std::vector<std::vector<int>> adj;
        std::map<std::pair<int, int>, int> edges;


        void dfs(int v, std::vector<int>& visited) override {
            visited[v] = 1;
            for (int i=0; i<adj[v].size(); i++) {
                if (adj[v][i] > 0) {
                    for (int j=0; j<num_vertices; j++) {
                        if (adj[j][i] > 0 and j != v) { dfs(j, visited); }
                    }
                }
            }
        }
    public:
        IncMatrix(int num_vertices, int num_edges): Graph(num_vertices, num_edges) {
            this->adj.resize(num_vertices, std::vector<int>(num_edges));
        }

        ~IncMatrix() {
        }

        void insertEdge(int u, int v) override {
            if (this->num_edges>=0) {
                this->num_edges--;
                adj[u][this->num_edges] += 1;
                adj[v][this->num_edges] += 1;
                edges[{std::max(u,v), std::min(u,v)}] = this->num_edges;
            }
        }

        void insertEdge(int v, std::vector<int> vertexes) override {
            for (int u: vertexes) {
                insertEdge(v, u);
            }
        }

        void deleteEdge(int u, int v) override {
            int edge = this->edges[{std::max(u,v), std::min(u,v)}];
            adj[u][edge]--;
            adj[v][edge]--;
        }

        std::vector<int> getAdjacentVertices(int v, int& op) override {
            std::vector<int> adjacents;

            for (int i=0; i<adj[0].size(); i++) {
                for (int j=0; j<num_vertices; j++) {
                    if (adj[v][i] and adj[j][i] > 0 and j != v) { adjacents.push_back(j); }
                    op+=3;
                }
            }

            return adjacents;
        }

        Graph* getInducedSubgraph(std::vector<int> removedVertices, int& op) override {
            Graph* inducedSubgraph = new IncMatrix(this->num_vertices - removedVertices.size(), this->adj[0].size());

            int v=0;
            for (int i=0; i<this->num_vertices; i++) {
                if (i!=removedVertices[v]) {
                    inducedSubgraph->insertEdge(v, adj[i]);
                }
            }

            return inducedSubgraph;
        }

        std::unordered_map<int, int> outdegree() override {
            std::unordered_map<int, int> outs;

            for (int i=0; i < num_vertices; i++) {
                for (int j=0; j < adj[0].size(); j++) {
                    if (adj[i][j] > 0) outs[i] += 1;
                }
            }

            return outs;
        }

        std::unordered_map<int, int> degree() override {
            std::unordered_map<int, int> outs;

            for (int i=0; i < num_vertices; i++) {
                for (int j=0; j < adj[0].size(); j++) {
                    if (adj[i][j] > 0) outs[i] += 1;
                }
            }

            return outs;
        }

        void to_string() override {
            for (int i=0; i < num_vertices; i++) {
                for (int j=0; j < adj[0].size(); j++) {
                    std::cout << adj[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }


};

#endif
