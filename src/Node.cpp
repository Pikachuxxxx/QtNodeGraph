#include "Node.h"

#include "NodeScene.h"
#include "GraphicsNode.h"
#include "NodeContentWidget.h"
#include "NodeEdge.h"

#include <QUndoCommand>

Node::Node(NodeScene* scene, std::string nodeName, uint32_t inputsCount, uint32_t outputsCount)
    : scene(scene), title(nodeName)
{
    nodeContent = new NodeContentWidget;
    graphicsNode = new GraphicsNode(this);

    scene->getUndoStack()->push(new AddNodeCommand(this, scene->getGraphicsScene()));

    scene->addNode(this);
    scene->getGraphicsScene()->addItem(graphicsNode);

    for (size_t i = 0; i < inputsCount; i++) {
        auto socket = new Socket(this, i, LEFT_BOTTOM);
        inputs.push_back(socket);
    }

    for (size_t i = 0; i < outputsCount; i++) {
        auto socket = new Socket(this, i, RIGHT_TOP);
        outputs.push_back(socket);
    }
}

Node::Node(NodeScene* scene, std::string nodeName, std::vector<std::string> inputsCount, std::vector<std::string> outputsCount)
    : scene(scene), title(nodeName)
{
    nodeContent = new NodeContentWidget;
    graphicsNode = new GraphicsNode(this);

    scene->getUndoStack()->push(new AddNodeCommand(this, scene->getGraphicsScene()));

    scene->addNode(this);
    scene->getGraphicsScene()->addItem(graphicsNode);

    for (size_t i = 0; i < inputsCount.size(); i++) {
        auto socket = new Socket(this, i, LEFT_BOTTOM, inputsCount[i]);
        inputs.push_back(socket);
    }

    for (size_t i = 0; i < outputsCount.size(); i++) {
        auto socket = new Socket(this, i, RIGHT_TOP, outputsCount[i]);
        outputs.push_back(socket);
    }
}

Node::~Node()
{

}

void Node::setPos(uint32_t x, uint32_t y)
{
    graphicsNode->setPos(x, y);
}
 
QPointF Node::getPos()
{
    return graphicsNode->pos();
}

QPointF Node::getSocketPosition(uint32_t index, SocketPos pos)
{
    if (!graphicsNode)
        return QPointF();

    float x = 0, y = 0;
    if (pos == LEFT_TOP || pos == LEFT_BOTTOM) x = 0; else x = graphicsNode->getWidth();

    if (pos == LEFT_TOP || pos == RIGHT_TOP)
        y = graphicsNode->getTitleHeight() + graphicsNode->getEdgeSize() + index * socketSpacing + graphicsNode->getPadding();
    else if (pos == LEFT_BOTTOM || pos == RIGHT_BOTTOM)
        y = graphicsNode->getHeight() - graphicsNode->getEdgeSize() - index * socketSpacing - graphicsNode->getPadding();

    return QPointF(x, y);
}

void Node::remove()
{
    //scene->getUndoStack()->push(new RemoveNodeCommand(scene->getGraphicsScene()));

    for (auto input : inputs) {
        if (input->hasEdge())
            input->getEdge()->remove();
    }

    for (auto output : outputs) {
        if (output->hasEdge())
            output->getEdge()->remove();
    }
    // Doing remove item instead of delete noice
    //graphicsNode->~GraphicsNode();
    //scene->getGraphicsScene()->removeItem(graphicsNode);
    delete graphicsNode;
    graphicsNode = nullptr;
    scene->removeNode(this);
}

void Node::add()
{
    for (auto input : inputs) {
        if (input->hasEdge())
            input->getEdge()->add();
    }

    for (auto output : outputs) {
        if (output->hasEdge())
            output->getEdge()->add();
    }

    graphicsNode = new GraphicsNode(this);

    scene->addNode(this);
    scene->getGraphicsScene()->addItem(graphicsNode);
}

AddNodeCommand::AddNodeCommand(Node* node, QGraphicsScene* scene)
    : mNode(node), mGraphicsScene(scene)
{
    mNode = node;
    mInitialPosition = node->getPos();
    mGraphicsScene->update();

    setText("Added node");
}

void AddNodeCommand::undo()
{
    //mNode->remove();
    //mGraphicsScene->update();
}

void AddNodeCommand::redo()
{
    //mNode->add();
    //mNode->setPos(mInitialPosition.x(), mInitialPosition.y());
    //mGraphicsScene->clearSelection();
    //mGraphicsScene->update();
}

RemoveNodeCommand::RemoveNodeCommand(QGraphicsScene* scene)
    : mGraphicsScene(scene)
{
    QList<QGraphicsItem*> list = scene->selectedItems();
    if(list.size() > 0 )
    list.first()->setSelected(false);

    mNode = static_cast<GraphicsNode*>(list.first())->getNode();
    mInitialPosition = mNode->getPos();
    mGraphicsScene->update();

    setText("Removed node");
}

void RemoveNodeCommand::undo()
{
    mNode->add();
    mNode->setPos(mInitialPosition.x(), mInitialPosition.y());
    mGraphicsScene->clearSelection();
    mGraphicsScene->update();
}

void RemoveNodeCommand::redo()
{
    mNode->remove();
    mGraphicsScene->update();
}

MoveNodeCommand::MoveNodeCommand(Node* node, QPointF oldPos, QGraphicsScene* scene)
    : mNode(node), mOldPosition(oldPos), mNewPosition(node->getPos()), mGraphicsScene(scene)

{
    setText("Moved node");
}

void MoveNodeCommand::undo()
{
    mNode->setPos(mOldPosition.x(), mOldPosition.y());
    mGraphicsScene->update();

    setText("Moved undo");
}

void MoveNodeCommand::redo()
{
    mNode->setPos(mNewPosition.x(), mNewPosition.y());
    mGraphicsScene->update();
}

bool MoveNodeCommand::mergeWith(const QUndoCommand* other)
{
    const MoveNodeCommand* moveCommand = static_cast<const MoveNodeCommand*>(other);
    Node* item = moveCommand->mNode;

    if (item != mNode)
        return false;

    mNewPosition = item->getPos();

    return true;
}
