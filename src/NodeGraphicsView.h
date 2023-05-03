#pragma once

#include <iostream>

#include <QGraphicsView>
#include <QMouseEvent>

#include "NodeGraphicsScene.h"

class NodeGraphicsView : public QGraphicsView
{
public:
    NodeGraphicsView(NodeGraphicsScene* scene, QWidget* parent = nullptr);
    ~NodeGraphicsView() {}

    void mousePressEvent(QMouseEvent* event) override
    {
        if(event->button() == Qt::RightButton){
            auto releaseEvent = new QMouseEvent(QMouseEvent::MouseButtonRelease, event->localPos(), event->screenPos(), Qt::LeftButton, Qt::NoButton, event->modifiers());
            QGraphicsView::mousePressEvent(releaseEvent);
            setDragMode(QGraphicsView::ScrollHandDrag);
            auto fakeEvent = new QMouseEvent(event->type(), event->localPos(), event->screenPos(), Qt::LeftButton, event->buttons() | Qt::LeftButton, event->modifiers());
            QGraphicsView::mousePressEvent(fakeEvent);
        }
        else
            QGraphicsView::mousePressEvent(event);

    }

    void mouseReleaseEvent(QMouseEvent* event) override
    {
        if(event->button() == Qt::RightButton){
            auto fakeEvent = new QMouseEvent(event->type(), event->localPos(), event->screenPos(), Qt::LeftButton, event->buttons() & ~Qt::LeftButton, event->modifiers());
            setDragMode(QGraphicsView::NoDrag);
            QGraphicsView::mouseReleaseEvent(fakeEvent);
        }
        else
            QGraphicsView::mouseReleaseEvent(event);
    }

private:

};
