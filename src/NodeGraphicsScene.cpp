#include "NodeGraphicsScene.h"

#include <vector>
#include <cmath>

NodeGraphicsScene::NodeGraphicsScene()
{
    m_BGColor = QColor("#393939");
    m_LightColor = QColor("#2f2f2f");

    m_LightPen.setColor(m_LightColor);
    m_LightPen.setWidth(1.0f);

    setSceneRect(m_SceneWidth/2, m_SceneHeight/2, m_SceneWidth, m_SceneHeight);
    setBackgroundBrush(m_BGColor);
}

NodeGraphicsScene::~NodeGraphicsScene()
{

}

void NodeGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    std::vector<QLine> lines_light;

    uint32_t top = uint32_t(floor(rect.top()));
    uint32_t bottom = uint32_t(ceil(rect.bottom()));
    uint32_t left = uint32_t(floor(rect.left()));
    uint32_t right = uint32_t(ceil(rect.right()));

    uint32_t first_left = left - (left % m_GridSize);
    uint32_t first_top = top - (top % m_GridSize);


    for (uint32_t x = first_left; x < right; x += m_GridSize)
        lines_light.push_back(QLine(x, top, x, bottom));

    for (uint32_t y = first_top; y < bottom; y += m_GridSize)
        lines_light.push_back(QLine(left, y, right, y));

    painter->setPen(m_LightPen);
    painter->drawLines(lines_light.data(), lines_light.size());
}
