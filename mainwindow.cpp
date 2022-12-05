//
// Created by Iusaq on 11/27/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

QPoint findAvailablePosition(std::vector<QPoint *> &positions);

bool positionIsAvailable(int x, int y, std::vector<QPoint *> &positions);

mainwindow::mainwindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);

    graph.readGraph("D:\\FACULTATE\\Facultate\\An_2_sem_1\\AG\\temaaa\\date.txt");

    graph.DFS();

    update();
}

mainwindow::~mainwindow() {
    delete ui;
}

void drawLineWithArrow(QPainter &painter, QPoint start, QPoint end) {

    painter.setRenderHint(QPainter::Antialiasing, true);

    qreal arrowSize = 10; // size of head
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);

    QLineF line(start, end);

    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                          cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                          cos(angle + M_PI - M_PI / 3) * arrowSize);

    QPolygonF arrowHead;
    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;
    line.setLength(line.length() - 15);
    painter.drawLine(line);
    painter.drawPolygon(arrowHead);
}


void mainwindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(Qt::red);

    std::vector<QPoint *> positions;

    auto nodesList = graph.getTopologicalOrder();

    float x, y;
    for (auto &it: nodesList) {

        QRect nodeToDraw(it->coord.x(), it->coord.y(), 30, 30);

        painter.drawEllipse(nodeToDraw);
        painter.drawText(nodeToDraw, Qt::AlignCenter, QString::number(it->info));
    }

    for (auto it: graph.getEdges()) {
        QPoint start = it.start->coord;
        start.setX(start.x() + 15);
        start.setY(start.y() + 15);
        QPoint end = it.end->coord;
        end.setX(end.x() + 15);
        end.setY(end.y() + 15);
        drawLineWithArrow(painter, start, end);
    }
}

//
//bool positionIsAvailable(int xa, int ya, std::vector<QPoint *> &positions) {
//    for (auto it: positions) {
//        int xb = it->x();
//        int yb = it->y();
//        int distance = sqrt(((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb)));
//        if(distance<100)
//            return false;
//    }
//    return true;
//}
//
//QPoint findAvailablePosition(std::vector<QPoint *> &positions) {
//    int x, y;
//    do {
//        x = rand() % 300;
//        y = rand() % 300;
//    } while (!positionIsAvailable(x, y, positions));
//
//    QPoint res(x, y);
//    return res;
//}
