#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Harta.h"
#include "Graph.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QPointF>
#include <QResizeEvent>
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsView>
#include <QPen>
#include <QList>
#include <QVBoxLayout>

class Harta : public QMainWindow
{
    Q_OBJECT

public:
    Harta(QWidget *parent = nullptr);
    ~Harta();
    void paintEvent(QPaintEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    Ui::HartaClass ui;
    Graph graph;
    Node* m_selectedNodeForArc;
    Node* m_selectedNodeForArcSecond;
    std::pair<std::vector<Node*>,double> result;
    double MIN_LATITUDE;
    double MAX_LATITUDE;
    double MIN_LONGITUDE;
    double MAX_LONGITUDE;

    void readXMLFileAndFillGraph(const QString& filePath);
    void findMinMaxCoordinates(const QString& filePath);

protected:
    void resizeEvent(QResizeEvent* event) override;
};
