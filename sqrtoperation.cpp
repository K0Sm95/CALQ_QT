#include "QVector"
#include "QtMath"
#include "sqrtoperation.h"

double SqrtOperation(QVector<double> values)
{
    double result = qSqrt(values[0]);
    return result;
}

