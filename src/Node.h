#pragma once

#include <QGraphicsItem>

#include <string>

class NodeScene;
class GraphicsNode;

class Node
{
public:
    Node(NodeScene* scene, std::string nodeName = "Undefined Node");
    ~Node();

    NodeScene* getScene() { return scene; }
private:
    NodeScene* scene;
    std::string title;
    GraphicsNode* graphicsNode;
};
