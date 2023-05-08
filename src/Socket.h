#pragma once

#include <cstdint>

#include <QPointF>

class Node;
class NodeEdge;
class GraphicsSocket;

enum SocketPos
{
    LEFT_TOP,
    LEFT_BOTTOM,
    RIGHT_TOP,
    RIGHT_BOTTOM,
};

class Socket
{
public:
    Socket(Node* node, uint32_t index = 0, SocketPos position = LEFT_TOP);
    ~Socket() {}

    QPointF getPos();
    NodeEdge* getEdge() { return edge; }
    void setConnectedEdge(NodeEdge* edge) { this->edge = edge; }
    NodeEdge* getConnectedEdge() { return edge; }
    Node* getNode() { return node; }
private:
    Node* node;
    NodeEdge* edge; // Denotes the edge to which this socket is connected
    uint32_t index;
    SocketPos position;
    GraphicsSocket* grSocket;
};
