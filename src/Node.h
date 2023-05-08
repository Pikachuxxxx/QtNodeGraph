#pragma once

#include <string>

#include <QGraphicsItem>

#include "Socket.h"

class NodeScene;
class GraphicsNode;
class NodeContentWidget;

// TODO: Remove NodeScene from the Node class and use utility methods in NodeScene class to add/create nodes
class Node
{
public:
    Node(NodeScene* scene, std::string nodeName, uint32_t inputsCount = 0, uint32_t outputsCount = 0);
    ~Node();

    QPointF getSocketPosition(uint32_t index, SocketPos pos);

    void setPos(uint32_t x, uint32_t y);
    NodeScene* getScene() { return scene; }
    const std::string& getTitle() const { return title; }
    NodeContentWidget* getContent() { return nodeContent; }
    void setContent(NodeContentWidget* widget) { nodeContent = widget; }
    GraphicsNode* getGraphicsNode() { return graphicsNode; }
    Socket* getInputSocket(uint32_t idx) { return inputs[idx]; }
    Socket* getOutputSocket(uint32_t idx) { return outputs[idx]; }

private:
    NodeScene* scene;
    std::string title;
    GraphicsNode* graphicsNode;
    NodeContentWidget* nodeContent;
    std::vector<Socket*> inputs;
    std::vector<Socket*> outputs;
    uint32_t socketSpacing = 24;

};
