#pragma once

#include <iostream>

#include <QGraphicsItem>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPainter>

class GraphicsSocket : public QGraphicsItem
{
public:
    GraphicsSocket(std::string colorHex = "#FFFF7700", QGraphicsItem* parent = nullptr);
    ~GraphicsSocket() {}

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override
    {
        std::cout << "Socket Pressed" << std::endl;
    }

    QRectF boundingRect() const override { return QRectF(0, 0, 2 * (radius + outlineWidth), 2 * (radius + outlineWidth)).normalized(); }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    uint32_t radius = 6;
    float outlineWidth = 1.0f;
    QColor bgColor;
    QColor outlineColor;
    QPen pen;
    QBrush brush;
};
