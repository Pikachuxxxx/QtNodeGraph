#include "GraphicsCutLine.h"

#include <QPainter>

GraphicsCutLine::GraphicsCutLine(QGraphicsItem* parent /*= nullptr*/)
    : QGraphicsItem(parent)
{
    pen = QPen(Qt::white);
    pen.setWidth(1.0f);
    pen.setDashPattern({ 3, 3 });

    setZValue(2);
}

void GraphicsCutLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(Qt::NoBrush); 
    painter->setPen(pen);

    auto poly = QPolygon(linePoints);
    painter->drawPolygon(poly);
}
