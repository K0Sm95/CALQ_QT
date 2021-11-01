#include "QVector"
#include "binaryoperations.h"

double sumOperation(QVector<double> values)
{
    double result = values.first();
    for (int i = 1; i < values.size(); i++)
    {
        result += values[i];
    }
    return result;
}

double subtractOperation(QVector<double> values)
{
    double result = values.first();
    for (int i = 1; i < values.size(); i++)
    {
        result -= values[i];
    }
    return result;
}

double multiplyOperation(QVector<double> values)
{
    double result = values.first();
    for (int i = 1; i < values.size(); i++)
    {
        result *= values[i];
    }
    return result;
}

double divideOperation(QVector<double> values)
{
    double result = values.first();
    for (int i = 1; i < values.size(); i++)
    {
        result /= values[i];
    }
    return result;
}
