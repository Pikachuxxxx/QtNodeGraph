#pragma once

#include "NodeGraphicsScene.h"

#include <vector>

class Node;

class NodeScene
{
public:
    NodeScene();
    ~NodeScene() {}

    void addNode(Node* node);

    QPoint getOrigin() { return m_GraphicsScene->getOrigin(); }

    NodeGraphicsScene* getGraphicsScene() { return m_GraphicsScene; }
private:
    NodeGraphicsScene* m_GraphicsScene;
    std::vector<Node*> m_Nodes;
};
