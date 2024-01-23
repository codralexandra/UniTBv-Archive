#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include <QMouseEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *e);
    bool existsNodeAtCoordinates(std::vector<Node>& nodes, QPointF& clickCoordinates);
private slots:
    void on_radioButton_clicked();
    void timerTimeout();

private:
    Ui::MainWindow *ui;
    Graph g;
    Node firstNode;
    QTimer *holdTimer;

};
#endif // MAINWINDOW_H
