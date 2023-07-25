#include "GraphicsSocket.h"

GraphicsSocket::GraphicsSocket(std::string colorHex, QGraphicsItem* parent)
    : QGraphicsItem(parent)
{
    // this->setPos(node->getScene()->getOrigin().x(), node->getScene()->getOrigin().y());
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    bgColor = QColor(colorHex.c_str());
    outlineColor = QColor("#FF000000");

    pen = QPen(outlineColor);
    pen.setWidthF(outlineWidth);

    brush = QBrush(bgColor);

    this->setZValue(5);
}

void GraphicsSocket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Painting circle
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawEllipse(-radius, -radius, 2 * radius, 2 * radius);
    // painter->drawRect(-radius, -radius, 2 * radius, 2 * radius);
}
