#include "NodeGraphicsView.h"

NodeGraphicsView::NodeGraphicsView(NodeGraphicsScene* scene, QWidget* parent)
    :QGraphicsView(parent)
{
    setScene(scene);

    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}
