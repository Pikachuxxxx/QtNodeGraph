#pragma once

#include <cstdint>

class Node;
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

private:
    Node* node;
    uint32_t index;
    SocketPos position;
    GraphicsSocket* grSocket;
};
