#ifndef ALPHA_H
#define ALPHA_H
#include "function.h"


class alpha
{
public:
    alpha(function *f,QVector<float>x, QVector<float>y, bool is_positive, int number);

    function *f;

    QVector<float>x;
    QVector<float>y;
    bool is_positive;
    int number;

    float func(float a);
};

#endif // ALPHA_H
