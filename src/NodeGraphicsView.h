#pragma once

#include <iostream>

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>

#include "GraphicsSocket.h"
#include "Socket.h"
#include "NodeEdge.h"
#include "GraphicsEdge.h"

class NodeScene;
class Socket;

enum class DRAG_MODE
{
    NO_OP,
    EDGE
};

constexpr uint32_t EDGE_DRAG_THRESHOLD = 10; // pixels

class NodeGraphicsView : public QGraphicsView
{
public:
    NodeGraphicsView(NodeScene* scene, QWidget* parent = nullptr);
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
                    edgeDragStart(item);
                    // Draw an edge here
                    m_DragEdge = new NodeEdge(m_Scene, static_cast<GraphicsSocket*>(item)->getSocket(), nullptr);
                    return;
                }
            }
            if(m_Mode == DRAG_MODE::EDGE){
                if (edgeDragEnd(item))
                    return;
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
            // Works for a continious drag of mouse and released on the socket (2nd type of drawing edges from socket)
            // press on socket this won't work cause dist is very less when released, if we make a long drag dist is more and this alternate form will work,
            // in this case socket press won't work as well as release will cause edgeDragEnd
            if(m_Mode == DRAG_MODE::EDGE) {
                auto m_newLMBReleaseScenePos = mapToScene(event->pos());
                auto dist = m_newLMBReleaseScenePos - m_lastLMBClickScenePos;
                if( dist.x() * dist.x() + dist.y() * dist.y() >  EDGE_DRAG_THRESHOLD * EDGE_DRAG_THRESHOLD) {
                    if (edgeDragEnd(item)) return;
                }
            }

            QGraphicsView::mouseReleaseEvent(event);
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

    void mouseMoveEvent(QMouseEvent* event) override
    {
        if(m_Mode == DRAG_MODE::EDGE) {
            auto pos = mapToScene(event->pos());
            m_DragEdge->getGraphicsEdge()->setDestPos(pos);
            // Manualllry trigger repaint
            m_DragEdge->getGraphicsEdge()->update();
        }

        QGraphicsView::mouseMoveEvent(event);
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

    void leftMousePress(QMouseEvent* event)
    {

    }
    void rightMousePress(QMouseEvent* event)
    {

    }
    void middleMousePress(QMouseEvent* event)
    {

    }

    void leftMouseRelease(QMouseEvent* event)
    {

    }
    void rightMouseRelease(QMouseEvent* event)
    {

    }
    void middleMouseRelease(QMouseEvent* event)
    {

    }

    void edgeDragStart(QGraphicsItem* item)
    {
        m_Mode = DRAG_MODE::EDGE;
        std::cout << "Start dragging edge" << std::endl;
        std::cout << "\t assign start socket" << std::endl;
    }
    bool edgeDragEnd(QGraphicsItem* item)
    {
        m_Mode = DRAG_MODE::NO_OP;
        std::cout << "End dragging edge" << std::endl;
        if(dynamic_cast<GraphicsSocket*>(item))
        {
            std::cout << "\t assign end socket" << std::endl;
            m_DragEdge->setEndSocket(dynamic_cast<GraphicsSocket*>(item)->getSocket());
            m_DragEdge->getStartSocket()->setConnectedEdge(m_DragEdge);
            m_DragEdge->getEndSocket()->setConnectedEdge(m_DragEdge);
            m_DragEdge->getGraphicsEdge()->update();
            return true;
        }

        // If it's not a socket end the m_DragEdge
        m_DragEdge->remove();
        delete m_DragEdge;
        m_DragEdge = nullptr;

        return false;
    }

private:
    float zoomInFactor = 1.25f;
    float zoom = 10.0f;
    float zoomStep = 1.0f;
    float zoomRangeMin = 0.0f;
    float zoomRangeMax = 10.0f;
    float zoomFactor = 1.0f;
    DRAG_MODE m_Mode = DRAG_MODE::NO_OP;
    QPointF m_lastLMBClickScenePos;
    NodeScene* m_Scene;
    //------------------------------
    NodeEdge* m_DragEdge = nullptr;
};
