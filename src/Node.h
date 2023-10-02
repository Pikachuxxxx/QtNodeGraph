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
    // TODO: Use a array for input and output counts that take the node colors/types in future
    Node(NodeScene* scene, std::string nodeName, uint32_t inputsCount = 0, uint32_t outputsCount = 0);
    Node(NodeScene* scene, std::string nodeName, std::vector<std::string> inputsCount, std::vector<std::string> outputsCount);
    ~Node();

    QPointF getSocketPosition(uint32_t index, SocketPos pos);

    void remove();

    void setPos(uint32_t x, uint32_t y);
    inline NodeScene* getScene() { return scene; }
    inline const std::string& getTitle() const { return title; }
    inline NodeContentWidget* getContent() { return nodeContent; }
    inline void setContent(NodeContentWidget* widget) { nodeContent = widget; }
    inline GraphicsNode* getGraphicsNode() { return graphicsNode; }
    inline Socket* getInputSocket(uint32_t idx) { return inputs[idx]; }
    inline Socket* getOutputSocket(uint32_t idx) { return outputs[idx]; }

private:
    NodeScene* scene;
    std::string title;
    GraphicsNode* graphicsNode;
    NodeContentWidget* nodeContent;
    std::vector<Socket*> inputs;
    std::vector<Socket*> outputs;
    uint32_t socketSpacing = 24;
};
