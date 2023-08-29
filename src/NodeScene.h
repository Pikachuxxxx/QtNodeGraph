#pragma once

#include "NodeGraphicsScene.h"

#include <vector>

class Node;
class NodeEdge;

class NodeScene
{
public:
    NodeScene();
    ~NodeScene() {}

    void addNode(Node* node);
    void removeNode(Node* node);

    void addEdge(NodeEdge* edge);
    void removeEdge(NodeEdge* edge);

    QPoint getOrigin() { return m_GraphicsScene->getOrigin(); }

    NodeGraphicsScene* getGraphicsScene() { return m_GraphicsScene; }
private:
    NodeGraphicsScene* m_GraphicsScene;
    std::vector<Node*> m_Nodes;
    std::vector<NodeEdge*> m_Edges;

};
