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
    // TODO: Pass the Scoket to it instead of just GrpahicsNode because this way we can both use graphcis node to parent and socket can be used to draw dummy edges in grapihcs view as it can retrieve only graphics socket
    GraphicsSocket(Socket* socket, std::string colorHex = "#FFFF7700");
    ~GraphicsSocket() {}

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override
    {
        std::cout << "Socket Pressed" << std::endl;
    }

    QRectF boundingRect() const override { return QRectF(0, 0, 2 * (radius + outlineWidth), 2 * (radius + outlineWidth)).normalized(); }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    Socket* getSocket() { return m_Socket; }

private:
    Socket* m_Socket = nullptr;
    uint32_t radius = 6;
    float outlineWidth = 1.0f;
    QColor bgColor;
    QColor outlineColor;
    QPen pen;
    QBrush brush;
};
