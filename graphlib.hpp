#ifndef GRAPH_LIB
#define GRAPH_LIB

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

class GraphNode {
private:
    std::string Label;
    std::unordered_map<GraphNode*, double> Neighbors;

public:
    GraphNode(std::string label = "") : Label(label) {}

    const std::string& getLabel() const { return Label; }
    void setLabel(const std::string& label) { Label = label; }

    int getDegree() const { return Neighbors.size(); }

    void addNeighbor(GraphNode* other, double weight = 0) {
        Neighbors[other] = weight;
    }

    void removeNeighbor(GraphNode* other) {
        Neighbors.erase(other);
    }

    const std::unordered_map<GraphNode*, double>& getNeighbors() const {
        return Neighbors;
    }

    bool isNeighbor(GraphNode* other) const {
        return Neighbors.find(other) != Neighbors.end();
    }
};

/////////////////////////////////////////////////////////////////////////////////

class Graph {
private:
    std::vector<std::unique_ptr<GraphNode>> Vertices;
    size_t E = 0;

public:
    Graph() = default;

    Graph(const std::vector<std::vector<int>>& adjM) {
        size_t V = adjM.size();
        Vertices.reserve(V);
        for (size_t i = 0; i < V; ++i) {
            Vertices.push_back(std::make_unique<GraphNode>(std::to_string(i)));
        }
        for (size_t i = 0; i < V; ++i) {
            for (size_t j = 0; j < V; ++j) {
                if (adjM[i][j]) {
                    Vertices[i]->addNeighbor(Vertices[j].get());
                    E++;
                }
            }
        }
    }

    size_t getV() const { return Vertices.size(); }
    size_t getE() const { return E; }

    std::vector<GraphNode*> getVertices() const {
        std::vector<GraphNode*> out;
        out.reserve(Vertices.size());
        for (auto& p : Vertices) out.push_back(p.get());
        return out;
    }

    void addVertex(const std::string& label = "") {
        Vertices.push_back(std::make_unique<GraphNode>(label));
    }

    void removeVertex(GraphNode* vertex) {
        if (!vertex) return;

        // remove incoming edges to vertex
        for (auto& v : Vertices) {
            if (v.get() == vertex) continue;
            if (v->isNeighbor(vertex)) {
                v->removeNeighbor(vertex);
                if (E > 0) E--;
            }
        }

        // find vertex index
        size_t idx = Vertices.size();
        for (size_t i = 0; i < Vertices.size(); ++i) {
            if (Vertices[i].get() == vertex) { idx = i; break; }
        }
        if (idx == Vertices.size()) return;

        // subtract its outgoing edges then erase
        size_t deg = Vertices[idx]->getDegree();
        if (E >= deg) E -= deg; else E = 0;
        Vertices.erase(Vertices.begin() + idx);
    }
};


#endif

