#include "Socket.h"

#include "Node.h"
#include "NodeEdge.h"
#include "GraphicsNode.h"
#include "GraphicsSocket.h"

#include<iostream>

Socket::Socket(Node* node, uint32_t index, SocketPos position, bool multiEdges, std::string colorHex, const std::string& name)
    : node(node), index(index), position(position), m_SupportsMultipleEdges(multiEdges), name(name)
{
    grSocket = new GraphicsSocket(this, colorHex);
    grSocket->setPos(node->getSocketPosition(index, position));
}

QPointF Socket::getPos()
{
    // return grSocket->pos();
    return node->getSocketPosition(index, position);
}

void Socket::removeEdges()
{
    for (auto edge : edges)
        edge->remove();
}

void Socket::removeEdge(NodeEdge* edge)
{
    if (std::find(edges.begin(), edges.end(), edge) != edges.end())
        edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
}
