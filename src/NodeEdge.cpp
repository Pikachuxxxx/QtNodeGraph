#include "NodeEdge.h"

#include "NodeScene.h"
#include "Socket.h"
#include "GraphicsEdge.h"

#include <iostream>

NodeEdge::NodeEdge(NodeScene* scene, Socket* startSocket, Socket* endSocket, EdgeType type)
    : m_Scene(scene), startSocket(startSocket), endSocket(endSocket)
{
    if (type == BEZIER)
        grEdge = new GraphicsEdgeBezier(this);
    else if (type == DIRECT)
        grEdge = new GraphicsEdgeDirect(this);

    scene->addEdge(this);
    scene->getGraphicsScene()->addItem(grEdge);

    if (startSocket)
        startSocket->setConnectedEdge(this);

    if (endSocket)
        endSocket->setConnectedEdge(this);
}

void NodeEdge::setStartSocket(Socket* socket)
{
    startSocket = socket; grEdge->updatePath();
    startSocket->setConnectedEdge(this);

}
void NodeEdge::setEndSocket(Socket* socket)
{
    endSocket = socket; grEdge->updatePath();
    endSocket->setConnectedEdge(this);

}

void NodeEdge::removeFromSockets()
{
    if (startSocket)
        startSocket->setConnectedEdge(nullptr);
    if (endSocket)
        endSocket->setConnectedEdge(nullptr);
    startSocket = nullptr;
    endSocket = nullptr;
}

void NodeEdge::remove()
{
    //grEdge->~GraphicsEdge();
    //m_Scene->getGraphicsScene()->removeItem(grEdge);

    delete grEdge;
    grEdge = nullptr;
    removeFromSockets();
    m_Scene->removeEdge(this);
}

void NodeEdge::select()
{
    grEdge->setSelected(true);
}
