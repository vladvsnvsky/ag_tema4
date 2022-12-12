//
// Created by Iusaq on 11/27/2022.
//

#include <iostream>
#include <fstream>
#include <stack>
#include "Graph.h"

[[maybe_unused]] void Graph::addEdge(Node *a, Node *b) {
    Edge x;
    x.start = a;
    x.end = b;
    this->m_edges.push_back(x);
    a->link.push_back(b);
}
QPoint findAvailablePosition(std::vector<QPoint> positions);

bool positionIsAvailable(int x, int y);

void Graph::readGraph(char *fileSource) {
    std::ifstream fin(fileSource);
    int nrNodes;
    fin >> nrNodes;
    this->m_nodes.resize(nrNodes);
    srand(time(NULL));
    for (int i = 0; i < nrNodes; i++) {
        m_nodes[i].info = i;
        m_nodes[i].coord = findAvailablePosition(this->getMPositions());
        this->addPosition(m_nodes[i].coord);
    }
    int nrOfEdges;
    fin >> nrOfEdges;
    int start, end;
    for (int edge = 0; edge < nrOfEdges; edge++) {
        fin >> start >> end;
        m_nodes[start].link.push_back(&m_nodes[end]);
        Edge newEdge;
        newEdge.start = &m_nodes[start];
        newEdge.end = &m_nodes[end];
        m_edges.push_back(newEdge);
    }
}

Graph::Graph() {}


void Graph::topologicalSort() {
    std::vector<bool> perm(this->m_nodes.size(), false);
    std::stack<Node *> stack;

    for (Node n: this->m_nodes) {
        if (n.permanent == false) {
            stack.push(&n);
            n.temporary = true;
            while (!stack.empty()) {
                Node *current = stack.top();
                for (Node *c: current->link) {
                    if (c->temporary == false) {
                        stack.push(c);
                        c->temporary = true;
                        break;
                    }
                }
                if (current->info == stack.top()->info) {
                    this->topSorted.push_front(&this->m_nodes[current->info]);
                    current->permanent = true;
                    stack.pop();
                }
            }
        }
    }

    for(size_t index = 0; index<this->m_edges.size(); index ++){
        if(m_edges[index].start->info>m_edges[index].end->info)
            this->m_edges.erase(m_edges.begin()+index);
    }

}

void Graph::visit(Node *n) {
    if (n->permanent == true)
        return;
    if (n->temporary == true) {
        std::cout << "Cycle found!!";
        std::exit(100);
    }
    n->temporary = true;
    for (Node *l: n->link) {
        visit(l);
    }
    n->temporary = false;
    n->permanent = true;
    this->topSorted.push_front(&this->m_nodes[n->info]);
}

void Graph::recursiveTopologicalSort() {
    for (Node n: this->m_nodes) {
        if (n.permanent == false)
            visit(&n);
    }
    for (auto elem: this->topSorted)
        std::cout << elem->info << " ";
}

std::list<Node *> Graph::getTopologicalOrder() {
    if (this->topSorted.size() == 0)
        this->topologicalSort();
    return this->topSorted;
} //WORKS

void Graph::showTopologicalOrder() {
    for (auto n: this->topSorted) {
        std::cout << n->info << " ";
    }
} //WORKS

void Graph::showTopologicalOrder(char *fileSource) {
    std::ofstream fout(fileSource);
    if (!cyclic)
        for (auto n: this->topSorted) {
            fout << n->info << " ";
        }
    else {
        fout << "Graph has cycles!";
    }
}

void Graph::DFS() {
    std::vector<bool> visited(this->m_nodes.size(), false);
    for (auto &n: this->m_nodes) {
        std::vector<bool> currentPath(visited.size(), false);
        if (visited[n.info] == false) {
            std::stack<Node *> stack;
            stack.push(&n);
            currentPath[n.info] = true;
            while (!stack.empty()) {
                Node *current = stack.top();
                stack.pop();
                if (visited[current->info] == false) {
                    std::cout << current->info << ' ';
                    visited[current->info] = true;
                }
                for (auto &c: current->link) {
                    if (visited[c->info] == false) {
                        if (currentPath[c->info] == true) {
                            std::cout << "Graph is not acyclic!";
                            this->cyclic = true;
                        }
                        stack.push(c);
                        currentPath[c->info] = true;
                        break;
                    }
                }
            }
        }
    }
}

bool Graph::isCyclic() {
    return this->cyclic;
}

const std::vector<Edge> &Graph::getEdges() const {
    return m_edges;
}

const std::vector<QPoint> &Graph::getMPositions() const {
    return m_positions;
}

void Graph::addPosition(QPoint pos) {
    this->m_positions.push_back(pos);

}

void Graph::printRoots(char *fileSource) {
    std::ofstream fout(fileSource);
    std::list<Node*>::iterator it;
    std::list<Node*>::iterator prev;
    it = this->topSorted.begin();

    fout<<"Roots: "<<(*it)->info<<' ';

    prev = it;
    it++;

    for(it; it!=this->topSorted.end(); it++){
        if((*prev)->info>(*it)->info && (*it)->link.size())
            fout<<(*it)->info<<' ';
        prev = it;
    }
}

const std::vector<Node> &Graph::getNodes() const {
    return m_nodes;
}


bool positionIsAvailable(int xa, int ya, std::vector<QPoint> &positions){
    for(auto it: positions){
        int xb = it.x();
        int yb = it.y();
        int distance = sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
        if(distance < 100)
            return false;
    }
    return true;
}

QPoint findAvailablePosition(std::vector<QPoint> positions){
    int x,y;
    do {
        x = rand() % 300;
        y = rand() % 300;
    }while(!positionIsAvailable(x,y,positions));

    QPoint res(x,y);
    return res;
}



