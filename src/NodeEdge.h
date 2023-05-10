#pragma once

class NodeScene;
class Socket;
class GraphicsEdge;

enum EdgeType
{
    BEZIER,
    DIRECT
};

class NodeEdge
{
public:
    NodeEdge(NodeScene* scene, Socket* startSocket, Socket* endSocket, EdgeType type = BEZIER);
    ~NodeEdge() {}

    void updatePositions();

    Socket* getStartSocket() const {return startSocket;}
    void setStartSocket(Socket* socket);
    Socket* getEndSocket() const {return endSocket;}
    void setEndSocket(Socket* socket);

    void removeFromSockets();
    void remove();

private:
    NodeScene* m_Scene;
    GraphicsEdge* grEdge;
    Socket* startSocket;
    Socket* endSocket;
};
