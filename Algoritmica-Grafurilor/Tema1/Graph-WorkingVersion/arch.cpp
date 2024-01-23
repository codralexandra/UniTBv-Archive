#include "arch.h"

Arch::Arch()
{
}

Arch::Arch(Node n1, Node n2){
    firstNode=n1;
    secondNode=n2;
}

Node Arch::getFirstNode(){
    return firstNode;
}

Node Arch::getSecondNode(){
    return secondNode;
}

