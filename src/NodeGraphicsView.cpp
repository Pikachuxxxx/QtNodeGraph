#include "NodeGraphicsView.h"

#include "NodeScene.h"
#include "GraphicsNode.h"
#include "Node.h"

NodeGraphicsView::NodeGraphicsView(NodeScene* scene, QWidget* parent)
    :QGraphicsView(parent), m_Scene(scene)
{
    setScene(scene->getGraphicsScene());

    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Enable selection using mouse
    setDragMode(QGraphicsView::RubberBandDrag);
}

void NodeGraphicsView::deleteSelected()
{
    auto& selectedItems = m_Scene->getGraphicsScene()->selectedItems();
    for (auto item : selectedItems) {
        // If it's a graphics edge
        if (dynamic_cast<GraphicsEdge*>(item)) {
            dynamic_cast<GraphicsEdge*>(item)->getEdge()->remove();
        }
        // If it's a graphics node
        else if (dynamic_cast<GraphicsNode*>(item)) {
            dynamic_cast<GraphicsNode*>(item)->getNode()->remove();
        }
    }
}
