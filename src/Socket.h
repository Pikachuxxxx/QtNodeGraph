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

enum SocketType
{
    INPUT,
    OUTPUT
};

class Socket
{
public:
    Socket(Node* node, uint32_t index = 0, SocketPos position = LEFT_TOP, std::string colorHex = "#FFFF7700", const std::string& name = "socket_name");
    ~Socket() {}

    QPointF getPos();
    inline SocketPos getSocketPos() { return position; }
    inline bool hasEdge() { return edge ? true : false; }
    inline NodeEdge* getEdge() { return edge; }
    inline void setConnectedEdge(NodeEdge* edge) { this->edge = edge; }
    inline NodeEdge* getConnectedEdge() { return edge; }
    inline Node* getNode() { return node; }
    inline const std::string& getSocketName() { return name; }

private:
    Node* node = nullptr;
    NodeEdge* edge = nullptr; // Denotes the edge to which this socket is connected
    uint32_t index;
    SocketPos position;
    SocketType type;
    GraphicsSocket* grSocket = nullptr;
    std::string name;
};
