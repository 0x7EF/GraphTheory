#ifndef GRAPH_LIB
#define GRAPH_LIB

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

class GraphNode {
private:
    std::string Label;
    std::unordered_map<GraphNode*, double> Neighbors;
    size_t Degree;

public:
    GraphNode(std::string label="") {
        this->Label = label;
        this->Neighbors = {};
        this->Degree = 0;
    }

    std::string getLabel() {
        return this->Label;
    }

    void setLabel(std::string label) {
        this->Label = label;
    }
    
    int getDegree() {
        return this->Degree;
    }

    void addNeighbor(GraphNode *other, double weight=0) {
        this->Neighbors[other] = weight;
        this->Degree += 1;
    }
    
    void removeNeighbor(GraphNode *other) {
        if (this->Neighbors.find(other) != this->Neighbors.end()) { 
            this->Neighbors.erase(other);
            this->Degree -= 1;
        }
    }
    
    std::unordered_map<GraphNode*, double> getNeighbors() {
        return this->Neighbors;
    }

    bool isNeighbor(GraphNode *other) {
        return (this->Neighbors.find(other) != this->Neighbors.end());    
    }


};

class Graph {
private:
    size_t V;
    size_t E;
    std::vector<GraphNode*> Vertices;

public:
    Graph() {
        this->V = 0;
        this->E = 0;
        this->Vertices = {};
    }

    Graph(std::vector<GraphNode*> nodes) {
        this->V = nodes.size();
        for (size_t i = 0; i < nodes.size(); ++i) {
            this->Vertices.push_back(nodes[i]);
            this->E += nodes[i]->getDegree();
        }
    }

    size_t getV() {
        return this->V;
    }

    size_t getE() {
        return this->E;
    }

    std::vector<GraphNode*> getVertices() {
        return this->Vertices;
    }

    void addVertex(GraphNode* vertex) {
        this->V += 1;
        this->E += vertex->getDegree();
        this->Vertices.push_back(vertex);
    }
    
    void removeVertex(GraphNode* vertex) {
        auto it = std::find(this->Vertices.begin(), this->Vertices.end(), vertex);
        if (it == this->Vertices.end()) {
            return;
        }

        this->Vertices.erase(it);
        this->V -= 1;
        this->E -= vertex->getDegree();
        for (size_t i = 0; i < this->Vertices.size(); ++i) {
            if (this->Vertices[i]->isNeighbor(vertex)) {
                this->Vertices[i]->removeNeighbor(vertex);
                this->E -= 1;
            }
        }
    }
};



#endif

