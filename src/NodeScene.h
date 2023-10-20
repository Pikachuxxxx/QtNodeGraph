#pragma once
#include <QUndoStack>

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

    inline NodeGraphicsScene* getGraphicsScene() { return m_GraphicsScene; }

    inline QUndoStack* getUndoStack() { return m_GraphicsScene->getUndoStack(); }

    inline std::vector<Node*>     getNodes() { return m_Nodes; }
    inline std::vector<NodeEdge*> getEdges() { return m_Edges; }

private:
    NodeGraphicsScene*     m_GraphicsScene;
    std::vector<Node*>     m_Nodes;
    std::vector<NodeEdge*> m_Edges;
};
