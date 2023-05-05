#pragma once

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QPen>

class Node;

class GraphicsNode : public QGraphicsItem
{
public:
    GraphicsNode(Node* node);
    ~GraphicsNode() {}

    void initContent();

    QRectF boundingRect() const override { return QRectF(0,0,2*edge_size + width,2*edge_size+height).normalized(); }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    Node* node;
    QColor titleColor;
    QGraphicsTextItem* titleItem;
    uint32_t width = 180;
    uint32_t height = 240;
    uint32_t edge_size = 10;
    uint32_t titleHeight = 24;
    uint32_t padding = 5;
    QPen penDefault;
    QPen penSelected;
    QBrush titleBrush;
    QBrush bgBrush;


};
