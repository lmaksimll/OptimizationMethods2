#include "function.h"
#include <algorithm>
#include <iostream>


function::function(int num)
{

    this->num=num;
}

float function::h = 0.001;

float function::func(QVector<float>x){

    float res = 0;

    if(this->num==1){
        res= 4 * ((x[0] - 5) * (x[0] - 5)) + ((x[1] - 6) * (x[1] - 6));
    }
    else if(this->num==2){
        res = (((x[0] * x[0]) + x[1] - 11) * ((x[0] * x[0]) + x[1] - 11))
                + ((x[0] + (x[1] * x[1]) - 7) * (x[0] + (x[1] * x[1]) - 7));
    }
    else if(this->num==3){
        res = 100 * ((x[1] - (x[0] * x[0])) * (x[1] - (x[0] * x[0])))
                + ((1 - x[0]) * (1 - x[0]))
                + 90 * ((x[3] - (x[2] *x[2])) * (x[3] - (x[2] *x[2])))
                + ((1 - x[2]) *(1 - x[2]))
                + 10.1 * (((x[1] - 1) * (x[1] - 1)) + ((x[3] - 1) * (x[3] - 1)))
                + 19.8 * (x[1] - 1) * (x[3] - 1);
    }
    else if(this->num==4){
        res = ((x[0] + 10 * x[1]) *(x[0] + 10 * x[1]))
                + (5 * ((x[2] - x[3]) * (x[2] - x[3])))
                + ((x[1] - 2 * x[2]) * (x[1] - 2 * x[2]) * (x[1] - 2 * x[2]) * (x[1] - 2 * x[2]))
                + (10 * ((x[0] - x[3]) *(x[0] - x[3]) * (x[0] - x[3]) * (x[0] - x[3])));
    }

    return res;
}

float function::dif1(QVector<float>x,int var_num){

    QVector<float>arguments;
    float a=0, b=0, res=0;

    for (int i = 0; i < x.length(); ++i) {
        arguments.append(x[i]);
    }

    arguments[var_num-1] += this->h;
    a = this->func(arguments);

    arguments[var_num-1] -= (this->h)*2;
    b = this->func(arguments);

    res = (a-b)/(2 * this->h);

    return res;
}

float function::dif2(QVector<float>x,int var_num1,int var_num2){

    QVector<float>arguments;
    float a=0, b=0, res=0;

    for (int i = 0; i < x.length(); ++i) {
        arguments.append(x[i]);
    }

    arguments[var_num1-1] += this->h;
    a = this->dif1(arguments,var_num2);

    arguments[var_num1-1] -= (this->h)*2;
    b = this->dif1(arguments,var_num2);

    res = (a-b)/(2 * this->h);

    return res;
}
