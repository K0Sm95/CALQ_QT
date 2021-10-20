#ifndef OPERATION_H
#define OPERATION_H

#include "QVector"

class Operation
{
public:
    Operation(){}
    virtual ~Operation(){}
    virtual double handle(QVector<double> values) = 0;
};

#endif // OPERATION_H
