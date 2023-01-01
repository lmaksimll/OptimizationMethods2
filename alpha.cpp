#include "alpha.h"

alpha::alpha(function *f,QVector<float>x, QVector<float>y, bool is_positive, int number)
{
    this->f=f;
    this->x=x;
    this->y=y;
    this->is_positive=is_positive;
    this->number=number;
}

float alpha::func(float a){

    QVector<float>argument;
    int sign = -1;
    float res = 0;

    if(this->is_positive){
        sign = 1;
    }

    for (int i = 0; i < this->x.length(); ++i) {
        if(this->number == 0){
            argument.append(this->x[i] + sign*a*this->y[i]);
        }
        else{
            if(i==this->number - 1){
                 argument.append(this->x[i] + sign*a*this->y[i]);
            }
            else {
                argument.append(this->x[i]);
            }
        }
    }

    res = this->f->func(argument);

    return res;
}
