#ifndef GRAPH_LIB
#define GRAPH_LIB

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class GraphNode {
private:
    std::string Label;
    std::vector<GraphNode> Neighbors;
    int Degree;
public:
    GraphNode() {
        this->Label = "";
        this->Neighbors = std::vector<GraphNode>();
        this->Degree = 0;
    };

    GraphNode(std::string label) {
        this->Label = label;
        this->Neighbors = std::vector<GraphNode>();
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

    void addNeighbor(GraphNode other) {
        this->Neighbors.push_back(other);
        this->Degree += 1;
    }

};

class Graph {
private:
    int V;
    int E;

};



#endif

