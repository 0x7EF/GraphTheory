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
    int Degree;

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
    int V;
    int E;

};



#endif

