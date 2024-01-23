#include "node.h"

Node::Node()
{
    value =-1;

}

void Node::setValue(int val){
    value=val;
}

void Node::setCoord(QPoint p){
    pos=p;
}

QPoint Node::getPosition(){
    return pos;
}

int Node::getValue(){
    return value;
}

bool Node::operator==(Node n){
    return this->pos == n.pos;
}


