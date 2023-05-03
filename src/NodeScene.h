#pragma once

#include "NodeGraphicsScene.h"

class NodeScene
{
public:
    NodeScene();
    ~NodeScene() {}

    NodeGraphicsScene* getGraphicsScene() { return m_GraphicsScene; }
private:
    NodeGraphicsScene* m_GraphicsScene;
};
