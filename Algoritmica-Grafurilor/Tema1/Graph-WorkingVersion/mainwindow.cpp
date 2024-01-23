#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    holdTimer = new QTimer(this);
    holdTimer->setInterval(100);
    connect(holdTimer, &QTimer::timeout, this, &MainWindow::timerTimeout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button()==Qt::RightButton)
    {
        holdTimer->start();
        vector<Node> nodes = g.getNodes();
        bool addNewNode = true;

        for (Node& n : nodes)
        {
            if (fabs(n.getPosition().x() - e->pos().x()) < 10 &&
                fabs(n.getPosition().y() - e->pos().y()) < 10)
            {
                addNewNode = false;
                break;
            }
        }
        if (addNewNode)
        {
            g.addNode(e->pos());
            update();
        }
        holdTimer->stop();
    }
    else if (e->button()==Qt::LeftButton)
    {
        holdTimer->start();
        vector<Node> nodes = g.getNodes();
        Node selectedNode;
        for(Node& n : nodes)
        {
            if(fabs(n.getPosition().x()- e->pos().x()) < 10 &&
                fabs(n.getPosition().y()-e->pos().y()) < 10 )
            {
                if(firstNode.getValue()==-1){
                    firstNode=n;
                    selectedNode=n;
                }
                else
                {
                    if(!(firstNode == n) && !g.arcExists(firstNode, n, true))
                        g.addArch(firstNode,n);
                    firstNode.setValue(-1);
                }
                break;
            }
        }
        if(!selectedNode.getPosition().isNull())
            firstNode = selectedNode;
    }
    holdTimer->stop();
    update();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    vector<Node> nodes = g.getNodes();
    for(Node& n: nodes)
    {
        QRect r(n.getPosition().x()-10,n.getPosition().y()-10,20,20);
        p.drawEllipse(r);
        QString s;
        s.setNum(n.getValue());
        p.drawText(r,Qt::AlignCenter,s);
    }
    vector<Arch> arches = g.getArches();
    for(Arch& a: arches)
    {
        int circle1X = a.getFirstNode().getPosition().x();
        int circle1Y = a.getFirstNode().getPosition().y();
        int circle2X = a.getSecondNode().getPosition().x();
        int circle2Y = a.getSecondNode().getPosition().y();

        double angle = std::atan2(circle2Y - circle1Y, circle2X - circle1X);

        int lineStartX = circle1X + static_cast<int>(10 * std::cos(angle));
        int lineStartY = circle1Y + static_cast<int>(10 * std::sin(angle));

        int lineEndX = circle2X - static_cast<int>(10 * std::cos(angle));
        int lineEndY = circle2Y - static_cast<int>(10 * std::sin(angle));

        p.drawLine(lineStartX, lineStartY, lineEndX, lineEndY);
    }
    if(g.getIsOriented()){
        for(Arch& a: arches)
        {
            QPointF firstPos = a.getFirstNode().getPosition();
            QPointF secondPos = a.getSecondNode().getPosition();

            double angle = atan2(secondPos.y() - firstPos.y(), secondPos.x() - firstPos.x());

            double arrowLength = 6.0;
            double secondCircleRadius = 10.0;

            QPointF arrowPointOnPerimeter1(secondPos.x() + secondCircleRadius * cos(angle),
                                           secondPos.y() + secondCircleRadius * sin(angle));

            QPointF arrowPointOnPerimeter2(secondPos.x() + secondCircleRadius * cos(angle + M_PI),
                                           secondPos.y() + secondCircleRadius * sin(angle + M_PI));

            double arrowAngle = M_PI / 6.0;

            QPointF arrowPoint1(arrowPointOnPerimeter2.x() - arrowLength * cos(angle + arrowAngle),
                                arrowPointOnPerimeter2.y() - arrowLength * sin(angle + arrowAngle));

            QPointF arrowPoint2(arrowPointOnPerimeter2.x() - arrowLength * cos(angle - arrowAngle),
                                arrowPointOnPerimeter2.y() - arrowLength * sin(angle - arrowAngle));

            p.drawLine(arrowPointOnPerimeter2, arrowPoint1);
            p.drawLine(arrowPointOnPerimeter2, arrowPoint2);
        }
    }
    if(firstNode.getValue() >= 0 ){
        QRect r(firstNode.getPosition().x()-15, firstNode.getPosition().y()-15,30,30);
        QPen pen;
        pen.setColor(Qt::blue);
        p.setPen(pen);
        p.drawEllipse(r);
        QString s;
        s.setNum(firstNode.getValue());
        p.drawText(r,Qt::AlignCenter,s);
    }
}

void MainWindow::on_radioButton_clicked()
{
    g.setIsOriented(true);
}

void MainWindow::timerTimeout()
{
    //select node
    //keep old coords
    //change coords by moving it
    //update coords
    //delete old arch
    //update arch
}

