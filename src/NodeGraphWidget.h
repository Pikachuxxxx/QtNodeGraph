#pragma once

#include <QWidget>
#include <QGraphicsView>

#include "NodeGraphicsView.h"
#include "NodeScene.h"

class NodeGraphWidget : public QWidget
{
public:
    NodeGraphWidget(QWidget* parent = nullptr);
    ~NodeGraphWidget();

    QPoint getOrigin();

private:
    NodeScene* m_Scene;
    NodeGraphicsView* m_GraphicsView;

private:
    void addDebugContent();

};
