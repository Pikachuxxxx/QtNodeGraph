#include "Socket.h"

#include "Node.h"
#include "GraphicsNode.h"
#include "GraphicsSocket.h"

#include<iostream>

Socket::Socket(Node* node, uint32_t index, SocketPos position)
    : node(node), index(index), position(position)
{
    grSocket = new GraphicsSocket(node->getGraphicsNode());
    grSocket->setPos(node->getSocketPosition(index, position));
}

QPointF Socket::getPos()
{
    // return grSocket->pos();
    return node->getSocketPosition(index, position);
}
