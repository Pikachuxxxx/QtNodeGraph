#pragma once

#include <string>

#include <QGraphicsItem>

#include "Socket.h"

class NodeScene;
class GraphicsNode;
class NodeContentWidget;

class Node
{
public:
    Node(NodeScene* scene, std::string nodeName, uint32_t inputsCount = 0, uint32_t outputsCount = 0);
    ~Node();

    QPointF getSocketPosition(uint32_t index, SocketPos pos);

    NodeScene* getScene() { return scene; }
    const std::string& getTitle() const { return title; }
    NodeContentWidget* getContent() { return nodeContent; }
    void setContent(NodeContentWidget* widget) { nodeContent = widget; }
    GraphicsNode* getGraphicsNode() { return graphicsNode; }
private:
    NodeScene* scene;
    std::string title;
    GraphicsNode* graphicsNode;
    NodeContentWidget* nodeContent;
    std::vector<Socket*> inputs;
    std::vector<Socket*> outputs;
    uint32_t socketSpacing = 24;

};
