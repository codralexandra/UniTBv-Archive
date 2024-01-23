#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sortaretopologicav2.h"
#include "graph.h"
#include "node.h"
#include "fstream"
#include <QMouseEvent>
#include <qfiledialog.h>
#include "graphwindow.h"

class SortareTopologicaV2 : public QMainWindow
{
    Q_OBJECT

public:
    SortareTopologicaV2(QWidget *parent = nullptr);
    ~SortareTopologicaV2();

    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

private slots:
    void on_setOriented_clicked();
    void on_adjacencyMatrixButton_clicked();
    void on_checkCircuitsButton_clicked();
    void on_sortedButton_clicked();
    void on_sortedGraphButton_clicked();
    void on_treeCheckButton_clicked();
    void on_rootButton_clicked();

private:
    Ui::SortareTopologicaV2Class ui;
    Graph m_graph;
    Node* m_selectedNodeForArc;
    std::ofstream matrixFile;
    std::ofstream sortFile;
    std::ofstream depthFirstFile;
    bool m_nodeDragState;
    Node* m_draggedNode;
    QPoint m_lastMousePos;
    GraphWindow graphWindow;;
};
