#include "Node.h"

#include "NodeScene.h"
#include "GraphicsNode.h"
#include "NodeContentWidget.h"
#include "Socket.h"

Node::Node(NodeScene* scene, std::string nodeName, uint32_t inputsCount, uint32_t outputsCount)
    : scene(scene), title(nodeName)
{
    nodeContent = new NodeContentWidget;
    graphicsNode = new GraphicsNode(this);

    scene->addNode(this);
    scene->getGraphicsScene()->addItem(graphicsNode);

    for (size_t i = 0; i < inputsCount; i++) {
        auto socket = new Socket(this);
        inputs.push_back(socket);
    }
}

Node::~Node()
{

}
