#include "NodeGraphicsScene.h"

#include <vector>
#include <cmath>

#include <iostream>

NodeGraphicsScene::NodeGraphicsScene()
{
    m_BGColor = QColor("#ff00ff");
    m_LightColor = QColor("#2f2f2f");
    m_DarkColor = QColor("#111111");

    m_LightPen.setColor(m_LightColor);
    m_LightPen.setWidth(1.0f);

    m_DarkPen.setColor(m_DarkColor);
    m_DarkPen.setWidth(2.0f);

    // setSceneRect(-floor(m_SceneWidth/2), -floor(m_SceneHeight/2), m_SceneWidth, m_SceneHeight);
    setSceneRect(0, 0, m_SceneWidth, m_SceneHeight);
    setBackgroundBrush(m_BGColor);
}

NodeGraphicsScene::~NodeGraphicsScene()
{

}

QPoint NodeGraphicsScene::getOrigin()
{
    return QPoint(sceneRect().width() / 2, sceneRect().height() / 2);
}

void NodeGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);

    std::vector<QLine> lines_light;
    std::vector<QLine> lines_dark;

    int32_t top = int32_t(floor(rect.top()));
    int32_t bottom = int32_t(ceil(rect.bottom()));
    int32_t left = int32_t(floor(rect.left()));
    int32_t right = int32_t(ceil(rect.right()));

    int32_t first_left = left - (left % m_GridSize);
    int32_t first_top = top - (top % m_GridSize);

    for (int32_t x = first_left; x < right; x += m_GridSize){
        if(x % (m_GridSize * m_GridSquares) != 0) lines_light.push_back(QLine(x, top, x, bottom));
        else lines_dark.push_back(QLine(x, top, x, bottom));
    }

    for (int32_t y = first_top; y < bottom; y += m_GridSize){
        if(y % (m_GridSize * m_GridSquares) != 0) lines_light.push_back(QLine(left, y, right, y));
        else lines_dark.push_back(QLine(left, y, right, y));
    }

    painter->setPen(m_LightPen);
    painter->drawLines(lines_light.data(), lines_light.size());

    painter->setPen(m_DarkPen);
    painter->drawLines(lines_dark.data(), lines_dark.size());
}
