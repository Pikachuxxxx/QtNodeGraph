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
{
    m_Nodes.erase(std::remove(m_Nodes.begin(), m_Nodes.end(), node), m_Nodes.end());
}

void NodeScene::addEdge(NodeEdge* edge)
{
    m_Edges.push_back(edge);
}

void NodeScene::removeEdge(NodeEdge* edge)
{
    m_Edges.erase(std::remove(m_Edges.begin(), m_Edges.end(), edge), m_Edges.end());
}
