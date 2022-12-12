//
// Created by Iusaq on 11/27/2022.
//

#ifndef TEMAAA_MAINWINDOW_H
#define TEMAAA_MAINWINDOW_H

#include <QMainWindow>
#include "Graph.h"

void drawLineWithArrow(QPainter &painter, QPoint start, QPoint end);

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);

    void drawGraph(Graph *g);

    void paintEvent(QPaintEvent *);

    Graph getGraph();

    ~mainwindow() override;

private:

    Graph graph;

    Ui::mainwindow *ui;
};


#endif //TEMAAA_MAINWINDOW_H
