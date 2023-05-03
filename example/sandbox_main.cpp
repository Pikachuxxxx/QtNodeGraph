#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>

#include <QtNodeGraph.h>

class NodeEditor : public NodeGraphWidget
{
public:
    NodeEditor()
    {}
    ~NodeEditor(){}
};

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Node Editor App");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    NodeEditor* ne = new NodeEditor;
    layout->addWidget(ne);

    QMainWindow w;
    w.resize(1280, 720);
    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    w.setCentralWidget(widget);
    w.setWindowTitle("Node Editor");
    w.show();

    ne->addDebugContent();

    return a.exec();
}
