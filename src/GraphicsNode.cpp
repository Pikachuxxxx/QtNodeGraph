#include "GraphicsNode.h"

#include "Node.h"
#include "NodeScene.h"

GraphicsNode::GraphicsNode(Node* node, std::string title)
{
    this->setPos(node->getScene()->getOrigin().x(), node->getScene()->getOrigin().y());
    titleItem = new QGraphicsTextItem(this);
    titleItem->setPlainText(title.c_str());
    titleItem->setDefaultTextColor(Qt::white);
}

void GraphicsNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    
}
