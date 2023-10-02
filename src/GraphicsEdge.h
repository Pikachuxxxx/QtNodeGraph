#pragma once

#include <QGraphicsItem>
#include <QPen>
#include <QPainter>

class NodeEdge;

class GraphicsEdge : public QGraphicsItem
{
public:
    GraphicsEdge(NodeEdge* edge, QGraphicsItem* parent = nullptr);

    virtual void updatePath() = 0;

    QRectF boundingRect() const override; //{ return QRectF(0, 0, 10000, 10000); }
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    void setDestPos(QPointF pos) { destPos = pos; updatePath(); }

    inline NodeEdge* getEdge() { return edge; }
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
    ~GraphicsEdgeDirect() { prepareGeometryChange(); };

    virtual void updatePath() override;
};
//------------------------------------------------------------------------------
class GraphicsEdgeBezier : public GraphicsEdge
{
public:
    GraphicsEdgeBezier(NodeEdge* edge, QGraphicsItem* parent = nullptr);
    ~GraphicsEdgeBezier() { };

    virtual void updatePath() override;
};
//------------------------------------------------------------------------------
