#include "QVector"
#include "sumoperation.h"

double SumOperation(QVector<double> values)
{
    double result = values[0];
    for (int i = 1; i < values.size(); i++)
    {
        result += values[i];
    }
    return result;
}
