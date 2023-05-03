#pragma once

#include <QWidget>
#include <QGraphicsView>

#include "NodeGraphicsScene.h"
#include "NodeGraphicsView.h"

class NodeGraphWidget : public QWidget
{
public:
    NodeGraphWidget(QWidget* parent = nullptr);
    ~NodeGraphWidget();

    QPoint getOrigin();

private:
    NodeGraphicsScene* m_GraphicsScene;
    NodeGraphicsView* m_GraphicsView;

private:
    void addDebugContent();

};
