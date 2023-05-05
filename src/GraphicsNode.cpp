#include "GraphicsNode.h"

#include <QGraphicsProxyWidget>

#include "Node.h"
#include "NodeScene.h"
#include "NodeContentWidget.h"

GraphicsNode::GraphicsNode(Node* node)
    : node(node)
{
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    this->setPos(node->getScene()->getOrigin().x(), node->getScene()->getOrigin().y());
    titleItem = new QGraphicsTextItem(this);
    titleItem->setPlainText(node->getTitle().c_str());
    titleItem->setDefaultTextColor(Qt::white);
    titleItem->setTextWidth(width - 2 * padding);
    titleItem->setPos(padding, 0);

    penDefault = QPen(QColor("#7f000000")); // ARGB
    penDefault.setWidth(2);
    penSelected = QPen(QColor("#FFFFA637"));
    penSelected.setWidth(2);

    titleBrush = QBrush(QColor("#FF313131"));
    bgBrush = QBrush(QColor("#E3212121"));

    initContent();
}

void GraphicsNode::initContent()
{
    auto grContent = new QGraphicsProxyWidget(this);
    node->getContent()->setGeometry(QRect(edge_size, titleHeight + edge_size, width - 2 * edge_size, height - 2 * edge_size - titleHeight));
    grContent->setWidget(node->getContent());
}

void GraphicsNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Title
    auto path_title = QPainterPath();
    path_title.setFillRule(Qt::WindingFill);
    path_title.addRoundedRect(0, 0, width, titleHeight, edge_size, edge_size);
    path_title.addRect(0, titleHeight - edge_size, edge_size, edge_size);
    path_title.addRect(width - edge_size, titleHeight - edge_size, edge_size, edge_size);
    painter->setPen(Qt::NoPen);
    painter->setBrush(titleBrush);
    painter->drawPath(path_title.simplified());

    // Content
    auto path_content = QPainterPath();
    path_content.setFillRule(Qt::WindingFill);
    path_content.addRoundedRect(0, titleHeight, width, height - titleHeight, edge_size, edge_size);
    path_content.addRect(0, titleHeight, edge_size, edge_size);
    path_content.addRect(width - edge_size, titleHeight, edge_size, edge_size);
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgBrush);
    painter->drawPath(path_content.simplified());

    // Outline
    auto path_outline = QPainterPath();
    path_outline.addRoundedRect(0, 0, width, height, edge_size, edge_size);
    if(!isSelected())
        painter->setPen(penDefault);
    else
        painter->setPen(penSelected);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path_outline.simplified());
}
