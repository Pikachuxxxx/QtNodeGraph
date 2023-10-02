#include "NodeGraphicsView.h"

#include "NodeScene.h"

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
