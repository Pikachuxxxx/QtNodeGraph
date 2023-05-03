#pragma once

#include <QWidget>
#include <QGraphicsView>

#include "NodeGraphicsScene.h"

class NodeGraphWidget : public QWidget
{
public:
    NodeGraphWidget(QWidget* parent = nullptr);
    ~NodeGraphWidget();

private:
    QGraphicsScene* m_GraphicsScene;
};
