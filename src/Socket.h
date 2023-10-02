#pragma once

#include <cstdint>
#include <string>

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
    Socket(Node* node, uint32_t index = 0, SocketPos position = LEFT_TOP, std::string colorHex = "#FFFF7700");
    ~Socket() {}

    QPointF getPos();
    inline SocketPos getSocketPos() { return position; }
    inline NodeEdge* getEdge() { return edge; }
    inline void setConnectedEdge(NodeEdge* edge) { this->edge = edge; }
    inline NodeEdge* getConnectedEdge() { return edge; }
    inline Node* getNode() { return node; }
private:
    Node* node;
    NodeEdge* edge; // Denotes the edge to which this socket is connected
    uint32_t index;
    SocketPos position;
    GraphicsSocket* grSocket;
};
