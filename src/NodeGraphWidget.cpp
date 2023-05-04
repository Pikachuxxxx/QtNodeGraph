#include "NodeGraphWidget.h"

#include <QVBoxLayout>
#include <QPen>
#include <QBrush>
#include <QGraphicsItem>

#include "Node.h"

NodeGraphWidget::NodeGraphWidget(QWidget* parent)
    : QWidget(parent)
{
    setGeometry(200, 200, 800, 600);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    m_Scene = new NodeScene;

    m_GraphicsView = new NodeGraphicsView(m_Scene->getGraphicsScene());
    layout->addWidget(m_GraphicsView);

    // addDebugContent();
    auto node = new Node(m_Scene, "Test Node");
}

NodeGraphWidget::~NodeGraphWidget()
{

}

void NodeGraphWidget::addDebugContent()
{
    QBrush greenBrush(Qt::green);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(1.0f);

    auto rect = m_Scene->getGraphicsScene()->addRect(QRect(getOrigin().x(), getOrigin().y(), 300, 300), outlinePen, greenBrush);
    rect->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    auto text = m_Scene->getGraphicsScene()->addText("Test text");
    text->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    text->setPos(getOrigin());
}

QPoint NodeGraphWidget::getOrigin()
{
    return QPoint(m_Scene->getGraphicsScene()->sceneRect().width() / 2, m_Scene->getGraphicsScene()->sceneRect().height() / 2);
}
