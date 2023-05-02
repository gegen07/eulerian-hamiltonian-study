#ifndef __ADJ_LIST_H__
#define __ADJ_LIST_H__

#include "graph.hpp"
#include "doubly-linked-list.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
#include <unordered_map>
#include <stack>

class AdjList : public Graph {
    private:
        DoublyLinkedList* adj;

        void dfs(int v, std::vector<int>& visited) override {
            visited[v] = 1;
            int op;
            for (int i=0; i<adj[v].size(); i++) {
                int v = adj[v].access(i, op);
                if (!visited[v]) {
                    dfs(v, visited);
                }
            }
        }
    public:
        AdjList(int num_vertices): Graph(num_vertices) {
            adj = new DoublyLinkedList[num_vertices];
            for(int i=0; i < this->num_vertices; i++) {
                this->adj[i] = DoublyLinkedList();
            }
        }

        ~AdjList() {
            delete adj;
        }

        void insertEdge(int u, int v) override {
            adj[u].insert(v, adj[u].size());
        }

        void insertEdge(int v, std::vector<int> vertexes) override {
            for (int u: vertexes) {
                insertEdge(v, u);
            }
        }

        void deleteEdge(int u, int v) override {
            adj[u].removeItem(v);
        }

        std::vector<int> getAdjacentVertices(int v, int& op) override {
            std::vector<int> adjacents(adj[v].size());

            for (int i=0; i<adj[v].size(); i++) {
                int x = adj[v].access(i, op);
                adjacents[i] = x;
            }

            return adjacents;
        }

        Graph* getInducedSubgraph(std::vector<int> removedVertices, int& op) override {
            Graph* inducedSubgraph = new AdjList(this->num_vertices - removedVertices.size());

            int v=0;
            for (int i=0; i<this->num_vertices; i++) {
                if (i!=removedVertices[v]) {
                    for (int j=0; j<this->adj[i].size(); j++) 
                        inducedSubgraph->insertEdge(v, adj[i].access(j, op));
                }
            }

            return inducedSubgraph;
        }

        std::unordered_map<int, int> outdegree() override {
            std::unordered_map<int, int> outs;

            for (int i=0; i < num_vertices; i++) {
                outs[i] = adj[i].size();
            }

            return outs;
        }
        std::unordered_map<int, int> degree() override {
            std::unordered_map<int, int> outs;

            for (int i=0; i < num_vertices; i++) {
                outs[i] = adj[i].size();
            }

            return outs;
        }

        void to_string() override {}
};

#endif
