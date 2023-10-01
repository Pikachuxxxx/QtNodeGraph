#pragma once

#include <QGraphicsItem>
#include <QPen>
#include <QPainter>

class NodeEdge;

class GraphicsEdge : public QGraphicsItem
{
public:
    GraphicsEdge(NodeEdge* edge, QGraphicsItem* parent = nullptr);
    ~GraphicsEdge() {}

    virtual void updatePath() = 0;

    QRectF boundingRect() const override; //{ return QRectF(0, 0, 10000, 10000); }
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setDestPos(QPointF pos) { destPos = pos; updatePath(); }
protected:
    NodeEdge* edge;
    QPen pathPen;
    QPen pathDragPen;
    QPen penSelected;
    QPainterPath path;
    QPointF destPos;

};

//------------------------------------------------------------------------------
class GraphicsEdgeDirect : public GraphicsEdge
{
public:
    GraphicsEdgeDirect(NodeEdge* edge, QGraphicsItem* parent = nullptr);
    ~GraphicsEdgeDirect() = default;

    virtual void updatePath() override;
};
//------------------------------------------------------------------------------
class GraphicsEdgeBezier : public GraphicsEdge
{
public:
    GraphicsEdgeBezier(NodeEdge* edge, QGraphicsItem* parent = nullptr);
    ~GraphicsEdgeBezier() = default;

    virtual void updatePath() override;
};
//------------------------------------------------------------------------------
