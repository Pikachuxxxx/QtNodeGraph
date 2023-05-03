#pragma once

#include <QGraphicsScene>
#include <QPainter>

class NodeGraphicsScene : public QGraphicsScene
{
public:
    NodeGraphicsScene();
    ~NodeGraphicsScene();

    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    QColor m_BGColor;
    QColor m_LightColor;
    uint32_t m_SceneWidth = 64000;
    uint32_t m_SceneHeight = 64000;
    QPen m_LightPen;
    uint32_t m_GridSize = 50;
};
