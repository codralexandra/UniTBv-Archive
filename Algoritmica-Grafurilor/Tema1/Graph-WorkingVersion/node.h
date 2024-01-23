#ifndef NODE_H
#define NODE_H

#include <QPainter>

class Node
{
    int value;
    QPoint pos;
public:
    Node();
    Node(QPoint p,int val);

    void setValue(int val);
    void setCoord(QPoint p);

    QPoint getPosition();
    int getValue();

    bool operator==(Node n);
};

#endif // NODE_H
