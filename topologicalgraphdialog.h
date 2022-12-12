//
// Created by Iusaq on 12/5/2022.
//

#ifndef TEMAAA_TOPOLOGICALGRAPHDIALOG_H
#define TEMAAA_TOPOLOGICALGRAPHDIALOG_H

#include <QDialog>
#include "Graph.h"


QT_BEGIN_NAMESPACE
namespace Ui { class TopologicalGraphDialog; }
QT_END_NAMESPACE

class TopologicalGraphDialog : public QDialog {
Q_OBJECT

public:
    explicit TopologicalGraphDialog(QWidget *parent = nullptr);

    void setGraph(Graph graph);

    void paintEvent(QPaintEvent *);

    ~TopologicalGraphDialog() override;

private:
    Ui::TopologicalGraphDialog *ui;

    Graph g;

};


#endif //TEMAAA_TOPOLOGICALGRAPHDIALOG_H
