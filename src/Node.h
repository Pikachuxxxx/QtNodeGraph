#pragma once

#include <QGraphicsItem>

#include <string>

class NodeScene;
class GraphicsNode;
class NodeContentWidget;

class Node
{
public:
    Node(NodeScene* scene, std::string nodeName = "Undefined Node");
    ~Node();

    NodeScene* getScene() { return scene; }
    const std::string& getTitle() const { return title; }
    NodeContentWidget* getContent() { return nodeContent; }
    void setContent(NodeContentWidget* widget) { nodeContent = widget; }
private:
    NodeScene* scene;
    std::string title;
    GraphicsNode* graphicsNode;
    NodeContentWidget* nodeContent;
};
