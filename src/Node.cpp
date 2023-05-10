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
        auto socket = new Socket(this, i, LEFT_BOTTOM);
        inputs.push_back(socket);
    }

    for (size_t i = 0; i < outputsCount; i++) {
        auto socket = new Socket(this, i, RIGHT_TOP);
        outputs.push_back(socket);
    }
}

Node::Node(NodeScene* scene, std::string nodeName, std::vector<std::string> inputsCount, std::vector<std::string> outputsCount)
    : scene(scene), title(nodeName)
{
    nodeContent = new NodeContentWidget;
    graphicsNode = new GraphicsNode(this);

    scene->addNode(this);
    scene->getGraphicsScene()->addItem(graphicsNode);

    for (size_t i = 0; i < inputsCount.size(); i++) {
        auto socket = new Socket(this, i, LEFT_BOTTOM, inputsCount[i]);
        inputs.push_back(socket);
    }

    for (size_t i = 0; i < outputsCount.size(); i++) {
        auto socket = new Socket(this, i, RIGHT_TOP, outputsCount[i]);
        outputs.push_back(socket);
    }
}

Node::~Node()
{

}

void Node::setPos(uint32_t x, uint32_t y)
{
    graphicsNode->setPos(x, y);
}

QPointF Node::getSocketPosition(uint32_t index, SocketPos pos)
{
    float x = 0, y = 0;
    if(pos == LEFT_TOP || pos == LEFT_BOTTOM) x = 0; else x = graphicsNode->getWidth();

    if(pos == LEFT_TOP || pos == RIGHT_TOP)
        y = graphicsNode->getTitleHeight() + graphicsNode->getEdgeSize() + index * socketSpacing + graphicsNode->getPadding();
    else if(pos == LEFT_BOTTOM || pos == RIGHT_BOTTOM)
        y = graphicsNode->getHeight() - graphicsNode->getEdgeSize() - index * socketSpacing - graphicsNode->getPadding();

    return QPointF(x, y);
}
