#include "QtMath"
#include "unaryoperations.h"

double sqrtOperation(double value)
{
    return qSqrt(value);
}

double squareOperation(double value)
{
    return value * value;
}

double absOperation(double value)
{
    return qAbs(value);
}

double sinOperation(double value)
{
    return qSin(value);
}

double cosOperation(double value)
{
    return qCos(value);
}
