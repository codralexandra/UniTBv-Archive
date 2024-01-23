#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "graph.h"
#include "node.h"
#include "costbox.h"
#include "graphwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <qmessagebox.h>
#include <qdebug.h>
#include <QPainterPath>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
    uint32_t openTextBox();
    void drawHighlightedEdges(QPainter& painter, const std::vector<Arch>& hightlightedArches);

public slots:
    void on_primButton_clicked();
    void on_kruskalButton_clicked();
  

private:
    Ui::MainWindowClass ui;
    Graph m_graph;
    Node* m_selectedNodeForArc;
    bool m_nodeDragState;
    Node* m_draggedNode;
    QPoint m_lastMousePos;
    std::vector<Arch> highlightedArches;
    GraphWindow* graphWindow;
};
