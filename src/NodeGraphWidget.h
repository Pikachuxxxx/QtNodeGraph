#pragma once

#include <QGraphicsView>
#include <QWidget>

#include "NodeGraphicsView.h"
#include "NodeScene.h"

class NodeGraphWidget : public QWidget
{
public:
    NodeGraphWidget(NodeGraphicsView* graphicsView = nullptr, QWidget* parent = nullptr);
    ~NodeGraphWidget();

    QPoint getOrigin();

private:
    NodeScene*        m_Scene;
    NodeGraphicsView* m_GraphicsView;

private:
    void addDebugContent();
};
