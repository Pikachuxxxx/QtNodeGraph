#pragma once

#include <cstdint>

class Node;
class GraphicsSocket;

enum SocketPos
{
    TOP_LEFT,
    BOTTOM_LEFT,
    MIDDLE_LEFT,
    TOP_RIGHT,
    MIDDLE_RIGHT,
    BOTTOM_RIGHT
};

class Socket
{
public:
    Socket(Node* node, uint32_t index = 0, SocketPos position = TOP_LEFT);
    ~Socket() {}

private:
    Node* node;
    uint32_t index;
    SocketPos position;
    GraphicsSocket* grSocket;
};
