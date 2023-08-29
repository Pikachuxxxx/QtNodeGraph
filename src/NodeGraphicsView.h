#pragma once

#include <iostream>

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>

#include "NodeGraphicsScene.h"
#include "GraphicsSocket.h"

enum class DRAG_MODE
{
    NO_OP,
    EDGE
};

class NodeGraphicsView : public QGraphicsView
{
public:
    NodeGraphicsView(NodeGraphicsScene* scene, QWidget* parent = nullptr);
    ~NodeGraphicsView() {}

    // TODO: Implement functions for L/M/R press/release
    // TODO: Implement functions for edgeDragStart/End

    void mousePressEvent(QMouseEvent* event) override
    {
        if(event->button() == Qt::LeftButton){
            auto item = itemAt(event->pos());

            m_lastLMBClickScenePos = mapToScene(event->pos());

            if(dynamic_cast<GraphicsSocket*>(item))
            {
                std::cout << "[Node Graphics View] Socket was clicked!" << std::endl;
                if(m_Mode == DRAG_MODE::NO_OP){
                    m_Mode = DRAG_MODE::EDGE;
                    std::cout << "Start dragging edge" << std::endl;
                    std::cout << "\t assign start socket" << std::endl;
                    return;
                }
            }
            // TODO: Move this to moveReleaseEvent
            if(m_Mode == DRAG_MODE::EDGE){
                m_Mode = DRAG_MODE::NO_OP;
                std::cout << "End dragging edge" << std::endl;

                if(dynamic_cast<GraphicsSocket*>(item))
                {
                    std::cout << "\t assign end socket" << std::endl;
                    return;
                }
            }
            QGraphicsView::mousePressEvent(event);
        }
        else if(event->button() == Qt::RightButton){
            // Panning the canvas using RMB
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
        if(event->button() == Qt::LeftButton){

            auto item = itemAt(event->pos());
            if(m_Mode == DRAG_MODE::EDGE) {

                auto m_newLMBReleaseScenePos = mapToScene(event->pos());
                auto dis = m_newLMBReleaseScenePos - m_lastLMBClickScenePos;
                if(m_lastLMBClickScenePos) {

                }
                else {
                    m_Mode = DRAG_MODE::NO_OP;

                    std::cout << "End dragging edge" << std::endl;

                    if(dynamic_cast<GraphicsSocket*>(item))
                    {
                        std::cout << "\t assign end socket" << std::endl;
                        return;
                    }
                }
            }

            QGraphicsView::mouseReleaseEvent(event);

            // TODO: Reset mode to NO_OP as soon as the mouse is relesed, socket connection works like drag drop
        }
        else if(event->button() == Qt::RightButton){
            // Panning the canvas using RMB
            auto fakeEvent = new QMouseEvent(event->type(), event->localPos(), event->screenPos(), Qt::LeftButton, event->buttons() & ~Qt::LeftButton, event->modifiers());
            setDragMode(QGraphicsView::NoDrag);
            QGraphicsView::mouseReleaseEvent(fakeEvent);
        }
        else
            QGraphicsView::mouseReleaseEvent(event);
    }

    void wheelEvent(QWheelEvent* event) override
    {
        float zoomOutFactor = 1.0f / zoomInFactor;

        if(event->angleDelta().y() > 0){
            zoomFactor = zoomInFactor;
            zoom += zoomStep;
        } else{
            zoomFactor = zoomOutFactor;
            zoom -= zoomStep;
        }

        bool clamped = false;
        if(zoom < zoomRangeMin) {
            zoom = zoomRangeMin;
            clamped = true;
        }
        else if(zoom > zoomRangeMax){
            zoom = zoomRangeMax;
            clamped = true;
        }

        if(!clamped)
            scale(zoomFactor, zoomFactor);
    }

    void leftMousePress(QMouseEvent* event);
    void rightMousePress(QMouseEvent* event);
    void middleMousePress(QMouseEvent* event);

    void leftMouseRelease(QMouseEvent* event);
    void rightMouseRelease(QMouseEvent* event);
    void middleMouseRelease(QMouseEvent* event);

    void edgeDragStart();
    void edgeDragEnd();

private:
    float zoomInFactor = 1.25f;
    float zoom = 10.0f;
    float zoomStep = 1.0f;
    float zoomRangeMin = 0.0f;
    float zoomRangeMax = 10.0f;
    float zoomFactor = 1.0f;
    DRAG_MODE m_Mode = DRAG_MODE::NO_OP;
    QPointF m_lastLMBClickScenePos;
};
