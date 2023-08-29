#include "NodeEdge.h"

#include "NodeScene.h"
#include "Socket.h"
#include "GraphicsEdge.h"

NodeEdge::NodeEdge(NodeScene* scene, Socket* startSocket, Socket* endSocket, EdgeType type)
    : m_Scene(scene), startSocket(startSocket), endSocket(endSocket)
{
    if(type == BEZIER)
        grEdge = new GraphicsEdgeBezier(this);
    else if(type == DIRECT)
        grEdge = new GraphicsEdgeDirect(this);

    scene->addEdge(this);
    scene->getGraphicsScene()->addItem(grEdge);
}

void NodeEdge::setStartSocket(Socket* socket)
{
    startSocket = socket; grEdge->updatePath();
}
void NodeEdge::setEndSocket(Socket* socket)
{
    endSocket = socket; grEdge->updatePath();
}

void NodeEdge::removeFromSockets()
{
    if(startSocket)
        startSocket->setConnectedEdge(nullptr);
    if(endSocket)
        endSocket->setConnectedEdge(nullptr);
    startSocket = nullptr;
    endSocket = nullptr;
}

void NodeEdge::remove()
{
    removeFromSockets();
    m_Scene->getGraphicsScene()->removeItem(grEdge);
    delete grEdge;
    grEdge = nullptr;
}
