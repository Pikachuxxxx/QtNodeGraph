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
    for (auto& item : selectedItems) {
        if (dynamic_cast<GraphicsEdge*>(item)) {
            dynamic_cast<GraphicsEdge*>(item)->getEdge()->remove();
        }
        else if (dynamic_cast<GraphicsNode*>(item)) {
            dynamic_cast<GraphicsNode*>(item)->getNode()->remove();
        }
        selectedItems.erase(std::remove(selectedItems.begin(), selectedItems.end(), item), selectedItems.end());
        item = nullptr;
    }
}
