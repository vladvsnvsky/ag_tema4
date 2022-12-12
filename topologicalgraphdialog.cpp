//
// Created by Iusaq on 12/5/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TopologicalGraphDialog.h" resolved

#include "topologicalgraphdialog.h"
#include "ui_TopologicalGraphDialog.h"
#include <QPainter>
#include <QPainterPath>
#include "mainwindow.h"



TopologicalGraphDialog::TopologicalGraphDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::TopologicalGraphDialog) {

    ui->setupUi(this);

    update();
}


void TopologicalGraphDialog::paintEvent(QPaintEvent *){
    g.topologicalSort();

    QPainter painter(this);

    painter.setPen(Qt::red);

    std::vector<QPoint *> positions;

    auto nodesList = g.getTopologicalOrder();

    float x, y;

    for (auto &it: nodesList) {

        QRect nodeToDraw(it->coord.x(), it->coord.y(), 30, 30);

        painter.drawEllipse(nodeToDraw);
        painter.drawText(nodeToDraw, Qt::AlignCenter, QString::number(it->info));
    }

    for (auto it: g.getEdges()) {
        QPoint start = it.start->coord;
        start.setX(start.x() + 15);
        start.setY(start.y() + 15);
        QPoint end = it.end->coord;
        end.setX(end.x() + 15);
        end.setY(end.y() + 15);
        drawLineWithArrow(painter, start, end);
    }
}



TopologicalGraphDialog::~TopologicalGraphDialog() {
    delete ui;
}

void TopologicalGraphDialog::setGraph(Graph graph) {
    this->g=graph;
}


