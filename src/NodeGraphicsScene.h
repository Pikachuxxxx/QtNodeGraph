#pragma once

#include <QGraphicsScene>
#include <QPainter>

class NodeGraphicsScene : public QGraphicsScene
{
public:
    NodeGraphicsScene();
    ~NodeGraphicsScene();

    QPoint getOrigin();
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    QColor m_BGColor;
    QColor m_LightColor;
    QColor m_DarkColor;

    uint32_t m_SceneWidth = 10000;
    uint32_t m_SceneHeight = 10000;
    QPen m_LightPen;
    QPen m_DarkPen;

    uint32_t m_GridSize = 20;
    uint32_t m_GridSquares = 5;
};
