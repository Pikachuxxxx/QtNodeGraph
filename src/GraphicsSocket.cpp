#include "GraphicsSocket.h"

GraphicsSocket::GraphicsSocket(QGraphicsItem* parent)
    : QGraphicsItem(parent)
{
    bgColor = QColor("#FFFF7700");
    outlineColor = QColor("#FF000000");

    pen = QPen(outlineColor);
    pen.setWidthF(outlineWidth);

    brush = QBrush(bgColor);

}

void GraphicsSocket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Painting circle
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawEllipse(-radius, -radius, 2 * radius, 2 * radius);
}
