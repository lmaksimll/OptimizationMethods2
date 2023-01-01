#ifndef FUNCTION_H
#define FUNCTION_H
#include <QVector>


class function
{

static float h;

public:
    function(int num);

    int num;

    float func(QVector<float>x);

    float dif1(QVector<float>x,int var_num);

    float dif2(QVector<float>x,int var_num1,int var_num2);

};




#endif // FUNCTION_H
