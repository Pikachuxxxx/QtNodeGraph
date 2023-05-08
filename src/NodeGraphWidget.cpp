#include "NodeGraphWidget.h"

#include <QVBoxLayout>
#include <QPen>
#include <QBrush>
#include <QGraphicsItem>

#include "Node.h"
#include "Socket.h"
#include "NodeEdge.h"

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

    addDebugContent();
}

NodeGraphWidget::~NodeGraphWidget()
{

}

void NodeGraphWidget::addDebugContent()
{
#if 0
    QBrush greenBrush(Qt::green);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(1.0f);

    auto rect = m_Scene->getGraphicsScene()->addRect(QRect(getOrigin().x(), getOrigin().y(), 300, 300), outlinePen, greenBrush);
    rect->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    auto text = m_Scene->getGraphicsScene()->addText("Test text");
    text->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    text->setPos(getOrigin());
#endif

    auto node = new Node(m_Scene, "Test_Node_0", 2, 3);
    auto node_2 = new Node(m_Scene, "Test_Node_1", 3, 0);
    node->setPos(getOrigin().x() - 350, getOrigin().y() - 250);
    node_2->setPos(getOrigin().x() + 50, getOrigin().y() - 75);

    auto edge = new NodeEdge(m_Scene, node->getOutputSocket(0), node_2->getInputSocket(1));
}

QPoint NodeGraphWidget::getOrigin()
{
    return QPoint(m_Scene->getGraphicsScene()->sceneRect().width() / 2, m_Scene->getGraphicsScene()->sceneRect().height() / 2);
}
