#pragma once

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QPen>

class Node;
class MoveNodeCommand;

class GraphicsNode : public QGraphicsItem
{
public:
    GraphicsNode(Node* node);
    ~GraphicsNode() { prepareGeometryChange(); }

    void initSockets();
    void initContent();

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override
    {
        hovered = true;
        update();
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override
    {
        hovered = false;
        update();
    }

    QRectF boundingRect() const override { return QRectF(0, 0, width, height).normalized(); }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }
    uint32_t getTitleHeight() const { return titleHeight; }
    uint32_t getEdgeSize() const { return edge_size; }
    uint32_t getPadding() const { return padding; }

    inline Node* getNode() { return node; }

private:
    Node* node;
    QColor titleColor;
    QGraphicsTextItem* titleItem;
    uint32_t width = 180;
    uint32_t height = 240;
    uint32_t edge_size = 8;
    uint32_t titleHeight = 24;
    uint32_t padding = 5;
    QPen penDefault;
    QPen penSelected;
    QPen penHovered;
    QBrush titleBrush;
    QBrush bgBrush;
    QPointF m_NodeOldPos;
    bool hovered = false;
};
