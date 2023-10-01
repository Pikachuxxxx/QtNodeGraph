#include "GraphicsEdge.h"

#include "Node.h"
#include "NodeScene.h"
#include "GraphicsNode.h"
#include "NodeEdge.h"
#include "Socket.h"

#include <QPainterPath>

#include <iostream>

GraphicsEdge::GraphicsEdge(NodeEdge* edge, QGraphicsItem* parent)
    :edge(edge)
{
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    pathPen = QPen("#FFFFFF");
    pathDragPen = QPen("#000000");
    pathDragPen.setStyle(Qt::DashLine);
    penSelected = QPen("#FFFFA637");
    pathPen.setWidthF(2.5f);
    penSelected.setWidthF(2.5f);
    pathDragPen.setWidthF(2.0f);

    this->setZValue(-1);

    auto sourcePos = edge->getStartSocket()->getPos();
    sourcePos += edge->getStartSocket()->getNode()->getGraphicsNode()->pos();
    destPos = sourcePos;
}

QRectF GraphicsEdge::boundingRect() const
{
    return this->shape().boundingRect();
}

QPainterPath GraphicsEdge::shape() const
{
    QPainterPath path;
    auto sourcePos = edge->getStartSocket()->getPos();
    sourcePos += edge->getStartSocket()->getNode()->getGraphicsNode()->pos();

    QPointF destinationPos;
    if(edge->getEndSocket()) {
        destinationPos = edge->getEndSocket()->getPos();
        destinationPos += edge->getEndSocket()->getNode()->getGraphicsNode()->pos();
    }
    else
        destinationPos = destPos;

    auto dist = (destinationPos.x() - sourcePos.x()) * 0.5f;
    if(sourcePos.x() > destinationPos.y()) dist *= -1;

    path = QPainterPath(sourcePos);
    path.cubicTo(sourcePos.x() + dist, sourcePos.y(), destinationPos.x() - dist, destinationPos.y(), destinationPos.x(), destinationPos.y());
    return path;
}

void GraphicsEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    updatePath();

    if(edge->getEndSocket()) {
        if(!isSelected())
            painter->setPen(pathPen);
        else
            painter->setPen(penSelected);
    }
    else
        painter->setPen(pathDragPen);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);
}
//------------------------------------------------------------------------------
GraphicsEdgeDirect::GraphicsEdgeDirect(NodeEdge* edge, QGraphicsItem* parent)
    : GraphicsEdge(edge, parent)
{

}

void GraphicsEdgeDirect::updatePath()
{
    auto sourcePos = edge->getStartSocket()->getPos();
    sourcePos += edge->getStartSocket()->getNode()->getGraphicsNode()->pos();

    QPointF destinationPos;
    if(edge->getEndSocket()) {
        destinationPos = edge->getEndSocket()->getPos();
        destinationPos += edge->getEndSocket()->getNode()->getGraphicsNode()->pos();
    }
    else
        destinationPos = destPos;

    path = QPainterPath(sourcePos);
    path.lineTo(destinationPos);
}
//------------------------------------------------------------------------------
GraphicsEdgeBezier::GraphicsEdgeBezier(NodeEdge* edge, QGraphicsItem* parent)
    : GraphicsEdge(edge, parent)
{

}

void GraphicsEdgeBezier::updatePath()
{
    auto sourcePos = edge->getStartSocket()->getPos();
    sourcePos += edge->getStartSocket()->getNode()->getGraphicsNode()->pos();

    QPointF destinationPos;
    if(edge->getEndSocket()) {
        destinationPos = edge->getEndSocket()->getPos();
        destinationPos += edge->getEndSocket()->getNode()->getGraphicsNode()->pos();
    }
    else
        destinationPos = destPos;

    auto dist = (destinationPos.x() - sourcePos.x()) * 0.5f;
    if(sourcePos.x() > destinationPos.y()) dist *= -1;

    path = QPainterPath(sourcePos);
    path.cubicTo(sourcePos.x() + dist, sourcePos.y(), destinationPos.x() - dist, destinationPos.y(), destinationPos.x(), destinationPos.y());
}
//------------------------------------------------------------------------------
