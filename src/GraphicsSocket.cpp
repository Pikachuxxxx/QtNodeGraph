#include "GraphicsSocket.h"

#include "Socket.h"
#include "Node.h"
#include "GraphicsNode.h"

GraphicsSocket::GraphicsSocket(Socket* socket, std::string colorHex)
    : QGraphicsItem(socket->getNode()->getGraphicsNode()), m_Socket(socket)
{
    // this->setPos(node->getScene()->getOrigin().x(), node->getScene()->getOrigin().y());
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    bgColor = QColor(colorHex.c_str());
    outlineColor = QColor("#FF000000");

    pen = QPen(outlineColor);
    pen.setWidthF(outlineWidth);

    brush = QBrush(bgColor);

    this->setZValue(5);
}

void GraphicsSocket::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    // Painting circle
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawEllipse(-radius, -radius, 2 * radius, 2 * radius);
    // painter->drawRect(-radius, -radius, 2 * radius, 2 * radius);
    // Paint the name
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(QColor("#FFFFFF")));
    // Calculate this based on the type of the socket and also adjust the width of the node
    QFontMetrics fm = painter->fontMetrics();

    auto spos = m_Socket->getSocketPos();
    if (spos == LEFT_TOP || spos == LEFT_BOTTOM)
        painter->drawText(8, 0, m_Socket->getSocketName().c_str());
    else
        painter->drawText(-8 - fm.horizontalAdvance(m_Socket->getSocketName().c_str()), 0, m_Socket->getSocketName().c_str());
}
