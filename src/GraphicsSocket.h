#pragma once

#include <iostream>

#include <QGraphicsItem>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPainter>

class Socket;

class GraphicsSocket : public QGraphicsItem
{
public:
    GraphicsSocket(Socket* socket, std::string colorHex = "#FFFF7700");
    ~GraphicsSocket() { prepareGeometryChange(); }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override
    {
        std::cout << "Socket Pressed" << std::endl;

        QGraphicsItem::mousePressEvent(event);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override
    {
        std::cout << "Mouse hovering on Socket" << std::endl;

        QGraphicsItem::mouseMoveEvent(event);
    }

    QRectF boundingRect() const override { return QRectF(-(radius + outlineWidth), -(radius + outlineWidth), 2 * (radius + outlineWidth), 2 * (radius + outlineWidth)); }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    Socket* getSocket() { return m_Socket; }

private:
    Socket* m_Socket = nullptr;
    uint32_t radius = 6;
    float outlineWidth = 1.0f;
    QColor bgColor;
    QColor outlineColor;
    QPen pen;
    QPen penHovered;
    QBrush brush;
    bool hover = false;
};
