#include "Node.h"

#include "NodeScene.h"
#include "GraphicsNode.h"
#include "NodeContentWidget.h"

Node::Node(NodeScene* scene, std::string nodeName)
    : scene(scene), title(nodeName)
{
    nodeContent = new NodeContentWidget;
    graphicsNode = new GraphicsNode(this);

    scene->addNode(this);
    scene->getGraphicsScene()->addItem(graphicsNode);
}

Node::~Node()
{

}
