#pragma once

#include <QWidget>
#include <QGraphicsView>

#include "NodeGraphicsScene.h"

class NodeGraphWidget : public QWidget
{
public:
    NodeGraphWidget(QWidget* parent = nullptr);
    ~NodeGraphWidget();

    // Temporary Method
    void addDebugContent();
    QPoint getOrigin();

private:
    QGraphicsScene* m_GraphicsScene;
};
