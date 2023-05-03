#include <QApplication>
#include <QMainWindow>

#include <QtNodeGraph.h>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QMainWindow mainwindow;
    mainwindow.resize(1280, 720);
    mainwindow.show();

    return a.exec();
}