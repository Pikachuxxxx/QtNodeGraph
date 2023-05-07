#pragma once

#include <QGraphicsItem>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPainter>

class GraphicsSocket : public QGraphicsItem
{
public:
    GraphicsSocket(QGraphicsItem* parent = nullptr);
    ~GraphicsSocket() {}

    QRectF boundingRect() const override { return QRectF(-radius - outlineWidth, -radius - outlineWidth, 2 * (radius + outlineWidth), 2 * (radius + outlineWidth)).normalized(); }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    uint32_t radius = 6;
    float outlineWidth = 1.0f;
    QColor bgColor;
    QColor outlineColor;
    QPen pen;
    QBrush brush;

};
