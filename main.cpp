#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    mainwindow w(nullptr);

    w.resize(1000,1000);

    w.show();

    return QApplication::exec();
}
