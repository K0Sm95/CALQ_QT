#include "QVector"
#include "multiplyoperation.h"

double MultiplyOperation(QVector<double> values)
{
    double result = values[0];
    for (int i = 1; i < values.size(); i++)
    {
        result *= values[i];
    }
    return result;
}

