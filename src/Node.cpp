#include "Node.h"

#include "NodeScene.h"
#include "GraphicsNode.h"
#include "NodeContentWidget.h"

Node::Node(NodeScene* scene, std::string nodeName, uint32_t inputsCount, uint32_t outputsCount)
    : scene(scene), title(nodeName)
{
    nodeContent = new NodeContentWidget;
    graphicsNode = new GraphicsNode(this);

    scene->addNode(this);
    scene->getGraphicsScene()->addItem(graphicsNode);

    for (size_t i = 0; i < inputsCount; i++) {
        auto socket = new Socket(this, i, TOP_LEFT);
        inputs.push_back(socket);
    }

    for (size_t i = 0; i < outputsCount; i++) {
        auto socket = new Socket(this, i, TOP_RIGHT);
        outputs.push_back(socket);
    }
}

Node::~Node()
{

}

QPointF Node::getSocketPosition(uint32_t index, SocketPos pos)
{
    float x = 0, y = 0;
    if(pos == TOP_LEFT || pos == BOTTOM_LEFT) x = 0; else x = graphicsNode->getWidth();
    y = graphicsNode->getTitleHeight() + index * 20;

    return QPointF(x, y);
}
