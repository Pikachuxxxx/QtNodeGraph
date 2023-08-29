#include "NodeScene.h"

NodeScene::NodeScene()
{
    m_GraphicsScene = new NodeGraphicsScene;
}

void NodeScene::addNode(Node* node)
{
    m_Nodes.push_back(node);
}

void NodeScene::removeNode(Node* node)
{}

void NodeScene::addEdge(NodeEdge* edge)
{
    m_Edges.push_back(edge);
}

void NodeScene::removeEdge(NodeEdge* edge)
{}
