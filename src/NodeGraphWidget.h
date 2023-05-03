#pragma once

#include <QWidget>
#include <QGraphicsView>

#include "NodeGraphicsScene.h"

class NodeGraphWidget : public QWidget
{
public:
    NodeGraphWidget(QWidget* parent = nullptr);
    ~NodeGraphWidget();

    QPoint getOrigin();

private:
    QGraphicsScene* m_GraphicsScene;

private:
    void addDebugContent();

};
