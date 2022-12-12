#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include "topologicalgraphdialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    mainwindow w(nullptr);
    TopologicalGraphDialog q(nullptr);

    w.resize(1000,1000);
    q.resize(600,600);

    w.show();
    q.setGraph(w.getGraph());
    q.show();

    return QApplication::exec();
}
