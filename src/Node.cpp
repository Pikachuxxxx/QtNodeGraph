#include "Node.h"

#include "NodeScene.h"
#include "GraphicsNode.h"

Node::Node(NodeScene* scene, std::string nodeName)
    : scene(scene), title(nodeName)
{
    graphicsNode = new GraphicsNode(this, title);

    scene->addNode(this);
    scene->getGraphicsScene()->addItem(graphicsNode);
}

Node::~Node()
{

}
