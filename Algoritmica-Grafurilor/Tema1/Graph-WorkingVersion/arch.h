#ifndef ARCH_H
#define ARCH_H

#include "node.h"

class Arch
{
    //refacem cu pointeri
    Node firstNode, secondNode;

public:
    Arch();
    Arch(Node n1, Node n2);

    Node getFirstNode();
    Node getSecondNode();
};

#endif // ARCH_H
