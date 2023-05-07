#include "Socket.h"

#include "Node.h"
#include "GraphicsNode.h"
#include "GraphicsSocket.h"

#include<iostream>

Socket::Socket(Node* node, uint32_t index, SocketPos position)
    : node(node), index(index), position(position)
{
    grSocket = new GraphicsSocket(node->getGraphicsNode());
    std::cout << "Socket position  (x : " << node->getSocketPosition(index, position).x() << ", y : " << node->getSocketPosition(index, position).y() << ")" << std::endl;
    grSocket->setPos(node->getSocketPosition(index, position));
}
