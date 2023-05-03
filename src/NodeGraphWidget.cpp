#include "NodeGraphWidget.h"

#include <QVBoxLayout>
#include <QPen>
#include <QBrush>
#include <QGraphicsItem>

NodeGraphWidget::NodeGraphWidget(QWidget* parent)
    : QWidget(parent)
{
    setGeometry(200, 200, 800, 600);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    m_GraphicsScene = new NodeGraphicsScene;

    QGraphicsView* view = new QGraphicsView;
    view->setScene(m_GraphicsScene);
    layout->addWidget(view);

    addDebugContent();
}

NodeGraphWidget::~NodeGraphWidget()
{

}

void NodeGraphWidget::addDebugContent()
{
    QBrush greenBrush(Qt::green);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(1.0f);

    auto rect = m_GraphicsScene->addRect(QRect(getOrigin().x(), getOrigin().y(), 300, 300), outlinePen, greenBrush);
    rect->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QPoint NodeGraphWidget::getOrigin()
{
    return QPoint(m_GraphicsScene->sceneRect().width() / 2, m_GraphicsScene->sceneRect().height() / 2);
}
