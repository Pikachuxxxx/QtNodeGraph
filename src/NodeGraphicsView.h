#pragma once

#include <iostream>

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QApplication>

#include "GraphicsSocket.h"
#include "Socket.h"
#include "NodeEdge.h"
#include "GraphicsEdge.h"
#include "NodeScene.h"
#include "GraphicsCutLine.h"
#include "GraphicsNode.h"
#include "Node.h"

class NodeScene;
class Socket;

// INCOMPLETE
// [] 14    : Deleting Edges (bugs, deleting multiple sometimes causes crash)
// [] 15    : Cutting edges (paint won't work for GraphicsCutEdge, check the bounding rect of GraphicsCutEdge)
// [] 19/20 : Undo/Redo fix bugs and finish implementation
// [] 22/23 : Cut/Copy/Paste (Razix Alpha release)
// [-] 25   : File has changed (Razix Alpha release, implemented in razix itself not in this project!)

enum class DRAG_MODE
{
    NO_OP,
    EDGE_DRAG,
    EDGE_CUT
};

constexpr uint32_t EDGE_DRAG_THRESHOLD = 10; // pixels

class NodeGraphicsView : public QGraphicsView
{
public:
    NodeGraphicsView(NodeScene* scene, QWidget* parent = nullptr);
    ~NodeGraphicsView() {}

    void keyPressEvent(QKeyEvent* e) override
    {
        // Escape is used to stop dragging edge
        if (e->key() == Qt::Key_Escape) {
            if (m_Mode == DRAG_MODE::EDGE_DRAG) {
                m_Mode = DRAG_MODE::NO_OP;
                std::cout << "End dragging edge" << std::endl;

                // If it's not a socket end the m_DragEdge
                m_DragEdge->remove();
                delete m_DragEdge;
                m_DragEdge = nullptr;
            }
        }
        // Delete is used for deleting selected items (nodes and edges)
        else if (e->key() == Qt::Key_Delete) {
            deleteSelected();
        }
        else if (e->key() == Qt::Key_C)
        {
            auto& items = m_Scene->getGraphicsScene()->items();
            std::cout << "Items count : " << items.count() << std::endl;
        }
        else
            QGraphicsView::keyPressEvent(e);
    }

    // TODO: Implement functions for L/M/R press/release
    // TODO: Implement functions for edgeDragStart/End

    void mousePressEvent(QMouseEvent* event) override
    {
        setDragMode(QGraphicsView::RubberBandDrag);

        if (event->button() == Qt::LeftButton) {
            leftMousePress(event);
        }
        else if (event->button() == Qt::RightButton) {
            rightMousePress(event);
        }
        else if (event->button() == Qt::MiddleButton) {
            middleMousePress(event);
        }
        else
            QGraphicsView::mousePressEvent(event);

    }

    void mouseReleaseEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton) {
            leftMouseRelease(event);
        }
        else if (event->button() == Qt::RightButton) {
            rightMouseRelease(event);
        }
        else if (event->button() == Qt::MiddleButton) {
            middleMouseRelease(event);
        }
        else
            QGraphicsView::mouseReleaseEvent(event);
    }

    void mouseMoveEvent(QMouseEvent* event) override
    {
        if (m_Mode == DRAG_MODE::EDGE_DRAG) {
            auto pos = mapToScene(event->pos());
            m_DragEdge->getGraphicsEdge()->setDestPos(pos);
            // Manually trigger repaint
            m_DragEdge->getGraphicsEdge()->update();
        }

        if (m_Mode == DRAG_MODE::EDGE_CUT) {
            auto pos = mapToScene(event->pos());
            m_Cutline->addPoint(QPoint(pos.x(), pos.y()));
            m_Cutline->update();

            //auto bbr = m_Cutline->boundingRect();

            //std::cout << bbr.x() <<  " " << bbr.y() << " " << bbr.width() << " " << bbr.height() << "\n";
        }

        QGraphicsView::mouseMoveEvent(event);
    }

    void wheelEvent(QWheelEvent* event) override
    {
        float zoomOutFactor = 1.0f / zoomInFactor;

        if (event->angleDelta().y() > 0) {
            zoomFactor = zoomInFactor;
            zoom += zoomStep;
        }
        else {
            zoomFactor = zoomOutFactor;
            zoom -= zoomStep;
        }

        bool clamped = false;
        if (zoom < zoomRangeMin) {
            zoom = zoomRangeMin;
            clamped = true;
        }
        else if (zoom > zoomRangeMax) {
            zoom = zoomRangeMax;
            clamped = true;
        }

        if (!clamped)
            scale(zoomFactor, zoomFactor);
    }

    void leftMousePress(QMouseEvent* event)
    {
        auto item = itemAt(event->pos());

        m_lastLMBClickScenePos = mapToScene(event->pos());

        if (dynamic_cast<GraphicsNode*>(item))
            m_NodeOldPos = item->pos();

        if (dynamic_cast<GraphicsSocket*>(item))
        {
            std::cout << "[Node Graphics View] Socket was clicked!" << std::endl;
            if (m_Mode == DRAG_MODE::NO_OP) {
                // Draw an edge here
                edgeDragStart(dynamic_cast<GraphicsSocket*>(item));
                m_DragEdge = new NodeEdge(m_Scene, static_cast<GraphicsSocket*>(item)->getSocket(), nullptr);
                return;
            }
        }
        if (m_Mode == DRAG_MODE::EDGE_DRAG) {
            if (edgeDragEnd(dynamic_cast<GraphicsSocket*>(item)))
                return;
        }

        // Cut edges using cut line
        if (!item) {
            if (event->modifiers() & Qt::ControlModifier) {
                m_Mode = DRAG_MODE::EDGE_CUT;
                setDragMode(QGraphicsView::NoDrag);
                QApplication::setOverrideCursor(Qt::CrossCursor);
                auto fakeEvent = new QMouseEvent(QEvent::MouseButtonRelease, event->localPos(), event->screenPos(), Qt::LeftButton, Qt::NoButton, event->modifiers());
                QGraphicsView::mousePressEvent(fakeEvent);
                return;
            }
        }

        QGraphicsView::mousePressEvent(event);
    }

    void rightMousePress(QMouseEvent* event)
    {
        //QApplication::restoreOverrideCursor();
        //QApplication::setOverrideCursor(Qt::ArrowCursor);

        // Panning the canvas using RMB
        auto releaseEvent = new QMouseEvent(QMouseEvent::MouseButtonRelease, event->localPos(), event->screenPos(), Qt::LeftButton, Qt::NoButton, event->modifiers());
        QGraphicsView::mousePressEvent(releaseEvent);
        setDragMode(QGraphicsView::ScrollHandDrag);
        auto fakeEvent = new QMouseEvent(event->type(), event->localPos(), event->screenPos(), Qt::LeftButton, event->buttons() | Qt::LeftButton, event->modifiers());
        QGraphicsView::mousePressEvent(fakeEvent);
    }

    void middleMousePress(QMouseEvent* event)
    {

    }

    void leftMouseRelease(QMouseEvent* event)
    {
        auto item = itemAt(event->pos());

        if (dynamic_cast<GraphicsNode*>(item) && item->pos() != m_NodeOldPos)
            m_Scene->getUndoStack()->push(new MoveNodeCommand(dynamic_cast<GraphicsNode*>(item)->getNode(), m_NodeOldPos, m_Scene->getGraphicsScene()));


        // Works for a continuous drag of mouse and released on the socket (2nd type of drawing edges from socket)
        // press on socket this won't work cause dist is very less when released, if we make a long drag dist is more and this alternate form will work,
        // in this case socket press won't work as well as release will cause edgeDragEnd
        if (m_Mode == DRAG_MODE::EDGE_DRAG) {
            auto m_newLMBReleaseScenePos = mapToScene(event->pos());
            auto dist = m_newLMBReleaseScenePos - m_lastLMBClickScenePos;
            if (dist.x() * dist.x() + dist.y() * dist.y() > EDGE_DRAG_THRESHOLD * EDGE_DRAG_THRESHOLD) {
                if (edgeDragEnd(dynamic_cast<GraphicsSocket*>(item)))
                    return;
            }
        }

        if (m_Mode == DRAG_MODE::EDGE_CUT) {
            m_Mode = DRAG_MODE::NO_OP;
            cutIntersectingEdges();
            m_Cutline->clearLinePoints();
            m_Cutline->update();
            //QApplication::setOverrideCursor(Qt::ArrowCursor);
            QApplication::restoreOverrideCursor();

            return;
        }

        QGraphicsView::mouseReleaseEvent(event);
    }

    void rightMouseRelease(QMouseEvent* event)
    {
        // Panning the canvas using RMB
        auto fakeEvent = new QMouseEvent(event->type(), event->localPos(), event->screenPos(), Qt::LeftButton, event->buttons() & ~Qt::LeftButton, event->modifiers());
        setDragMode(QGraphicsView::NoDrag);
        QGraphicsView::mouseReleaseEvent(fakeEvent);
    }

    void middleMouseRelease(QMouseEvent* event)
    {

    }

    void edgeDragStart(GraphicsSocket* grSocket)
    {
        m_Mode = DRAG_MODE::EDGE_DRAG;
        std::cout << "Start dragging edge" << std::endl;
        std::cout << "\t assign start socket" << std::endl;

        m_LastStartSocket = grSocket->getSocket();
        m_PreviousEdge = m_LastStartSocket->getConnectedEdge();
    }

    // TODO: Add option for user to use single edge input/output nodes

    bool edgeDragEnd(GraphicsSocket* grSocket)
    {
        m_Mode = DRAG_MODE::NO_OP;
        std::cout << "End dragging edge" << std::endl;

        if (grSocket)
        {
            if (grSocket->getSocket() != m_LastStartSocket) {

                // If the previous socket is null, the final socked might have a previous edge so mark that as previous edge
                if (!m_PreviousEdge)
                    m_PreviousEdge = grSocket->getSocket()->getConnectedEdge();

                std::cout << "\t assign end socket" << std::endl;

                // Also even if we have previous edge the current socket can have a edge already so remove that too
                if (grSocket->getSocket()->hasEdge())
                    grSocket->getSocket()->getConnectedEdge()->remove();


                // Delete old edge
                if (m_PreviousEdge) {
                    m_PreviousEdge->remove();
                    delete m_PreviousEdge;
                    m_PreviousEdge = nullptr;
                }

                m_DragEdge->setStartSocket(m_LastStartSocket);
                m_DragEdge->setEndSocket(grSocket->getSocket());
                m_DragEdge->getStartSocket()->setConnectedEdge(m_DragEdge);
                m_DragEdge->getEndSocket()->setConnectedEdge(m_DragEdge);
                m_DragEdge->getGraphicsEdge()->update();
                return true;
            }
        }

        // If it's not a socket end the m_DragEdge
        m_DragEdge->remove();
        delete m_DragEdge;
        m_DragEdge = nullptr;


        return false;
    }

    void deleteSelected();
    void cutIntersectingEdges();

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
    NodeEdge* m_PreviousEdge = nullptr;
    Socket* m_LastStartSocket = nullptr;
    GraphicsCutLine* m_Cutline = nullptr;
    QPointF m_NodeOldPos;
};
