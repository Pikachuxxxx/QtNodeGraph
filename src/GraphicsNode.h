#pragma once

#include <QGraphicsItem>
#include <QGraphicsTextItem>

class Node;

class GraphicsNode : public QGraphicsItem
{
public:
    GraphicsNode(Node* node, std::string title);
    ~GraphicsNode() {}

    QRectF boundingRect() const override { return QRectF(0,0,100,100); }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    Node* node;
    QColor titleColor;
    QGraphicsTextItem* titleItem;
};
