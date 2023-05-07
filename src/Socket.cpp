#include "Socket.h"

#include "Node.h"
#include "GraphicsNode.h"
#include "GraphicsSocket.h"

Socket::Socket(Node* node, uint32_t index, SocketPos position)
    : node(node), index(index), position(position)
{
    grSocket = new GraphicsSocket(node->getGraphicsNode());
}
