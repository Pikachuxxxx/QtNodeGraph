#include "NodeScene.h"

NodeScene::NodeScene()
{
    m_GraphicsScene = new NodeGraphicsScene;
}

void NodeScene::addNode(Node* node)
{
    m_Nodes.push_back(node);
}
