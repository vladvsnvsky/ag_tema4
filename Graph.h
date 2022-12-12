//
// Created by Iusaq on 11/27/2022.
//

#ifndef TEMAAA_GRAPH_H
#define TEMAAA_GRAPH_H

#include <vector>
#include <list>
#include <QPoint>

struct Node{
    int info;
    std::vector<Node*> link;
    bool permanent = false;
    bool temporary = false;

    QPoint coord;
};

struct Edge{
    Node* start;
    Node* end;
};

class Graph {
    std::vector<Node> m_nodes;
    std::vector<QPoint> m_positions;
    std::vector<Edge> m_edges;

    std::list<Node*> topSorted;

    bool cyclic = false;

    Node *s = nullptr;

public:

    Graph();

    bool isCyclic();

    const std::vector<Node> &getNodes() const;

    void topologicalSort();

    const std::vector<Edge> &getEdges() const;

    const std::vector<QPoint> &getMPositions() const;

    void addPosition(QPoint pos);

    std::list<Node*> getTopologicalOrder();

    void recursiveTopologicalSort();

    void visit(Node* n);

    [[maybe_unused]] void addEdge(Node *start, Node *end);

    void showTopologicalOrder();

    void showTopologicalOrder(char *fileSource);

    void printRoots(char *fileSource);

    void DFS();

    void readGraph(char* fileSource);
};


#endif //TEMAAA_GRAPH_H
