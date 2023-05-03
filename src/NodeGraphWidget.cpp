#include "NodeGraphWidget.h"

#include <QVBoxLayout>

NodeGraphWidget::NodeGraphWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    m_GraphicsScene = new NodeGraphicsScene;

    QGraphicsView* view = new QGraphicsView;
    view->setScene(m_GraphicsScene);
    layout->addWidget(view);
}

NodeGraphWidget::~NodeGraphWidget()
{

}
