#include "mainwindow.h"
#include <alpha.h>
#include <function.h>
#include "./ui_mainwindow.h"
#include <math.h>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->res,SIGNAL(clicked()),this,SLOT(res()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::res(){

    QVector<float>x;
    QVector<float> h;
    QVector<float> res;

    float accuracy = ui->toch_e->value();
    float z = 0.1;

    int num_func = 0;
    int num_meth = 0;



    if(ui->function1->isChecked()){
        num_func = 1;
    }
    if(ui->function2->isChecked()){
        num_func = 2;
    }
    if(ui->function3->isChecked()){
        num_func = 3;
    }
    if(ui->function4->isChecked()){
        num_func = 4;
    }

    if(ui->method1->isChecked()){
        num_meth = 1;
    }
    if(ui->method2->isChecked()){
        num_meth = 2;
    }
    if(ui->method3->isChecked()){
        num_meth = 3;
    }


    if(num_func < 3){
        x.append(ui->x1->value());
        x.append(ui->x2->value());

        h.append(ui->h1->value());
        h.append(ui->h2->value());
    }
    else {
        x.append(ui->x1->value());
        x.append(ui->x2->value());
        x.append(ui->x3->value());
        x.append(ui->x4->value());

        h.append(ui->h1->value());
        h.append(ui->h2->value());
        h.append(ui->h3->value());
        h.append(ui->h4->value());
    }


    function *f = new function(num_func);

    if(num_meth == 1){
        float k = 0;
        float ak = 0;
        QVector<float>xk;

        for(int i = 0; i < x.length(); i++){
            xk << 0;
        }

        while (true) {
            for (int i = 0; i < x.length(); ++i) {

                alpha *a = new alpha(f,x,h,true,i+1);
                ak = find_minimum(a);
                xk[i] = round((x[i]+ak*h[i]) * 1000) / 1000;
            }

            if(xk != x){
                k++;
                x = xk;
                for(int i = 0; i < x.length(); i++){
                    xk[i] = 0;
                }
            }
            else{
                if (norma(h) <= accuracy){
                    break;
                }
                else{
                    h = mul(h, z);
                }
            }
        }

        res = x;
    }
    else if(num_meth == 2){
        while (true) {
            QVector<float>grad_mtx = grad(f,x);

            if(norma(grad_mtx) < accuracy){
                break;
            }

            alpha *a = new alpha(f,x,grad_mtx,false,0);
            float min_a = find_minimum(a);

            for (int i = 0; i < x.length(); ++i) {
                x[i] -= min_a * grad_mtx[i];
            }
        }

        res= x;
    }
    else if (num_meth == 3) {
        while (true) {
            QVector<float>grad_mtx = grad(f,x);

            if(norma(grad_mtx) < accuracy){
                break;
            }

            QVector<QVector<float>>gessa_mtx = gessa(f,x);
            QVector<QVector<float>>envers_matrix_mtx = envers_matrix(gessa_mtx);

            if(envers_matrix_mtx.length() == 0){
                break;
            }

            QVector<float>p = mul(mul(envers_matrix_mtx, -1.0), grad_mtx);

            alpha *a = new alpha(f,x,p,true,0);

            float min_a = find_minimum(a);

            for (int i = 0; i < x.length(); ++i) {
                x[i] += min_a * p[i];
            }
        }

        res= x;
    }


    if(num_func < 3){
        ui->x1->setValue(res[0]);
        ui->x2->setValue(res[1]);
    }
    else {
       ui->x1->setValue(res[0]);
       ui->x2->setValue(res[1]);
       ui->x3->setValue(res[2]);
       ui->x4->setValue(res[3]);
    }


    ui->function->setValue(f->func(res));

    delete f;
}

float MainWindow::find_minimum(alpha *alp){

    float h=0.1;    //шаг
    float a=0;
    float b = 0;
    float k = 0;
    float res = 0;
    QVector<float>point;
    point << 1.0;
    float accuracy = 0.001;
    bool is_finished = false;

    if(alp->func(point[0]) > alp->func(point[0] + h)){
        a = point[0];
        point.append(point[0] + h);
        k = 2;
    }
    else {
        if(alp->func(point[0] - h) >= alp->func(point[0])){
            a=point[0] - h;
            b=point[0] + h;
            is_finished = true;
        }
        else{
            b = point[0];
            point.append(point[0] - h);
            h = -h;
            k = 2;
        }
    }
    while (!is_finished) {
        int k2 = 1;
        for (int j=0;j<k-1;j++) {
            k2 = k2 * 2;
        }
        //xk=z+k2*h;
        point.append(point[0] + (k2 * h));

        if(alp->func(point[k - 1]) > alp->func(point[k])){
            if(h>0){
                a=point[k - 2];
            }
            else{
                b = point[k];
            }
            k += 1;
        }
        else {
            if(h>0){
                b = point[k];
            }
            else {
                a = point[k];
            }
            is_finished = true;
        }
    }

    //---------------------------------------------------------------------


    float step = 1;
    QList <float> febon;      //лист чисел фебоначи
    febon << 1.0 << 1.0;
    int chet;               //число фебоначи
    k=0;
    float x1=0;
    float x2=0;
    float fx1=0;
    float fx2=0;

    for (int i=0;i<1;i++) {
        if(step == 1){
            float chislo = 0;             //новое число фебоначи
            float Fn = ((b-a)/(2 * 0.001)) ;
            for (chet=2;chislo < Fn ;chet++) {
                 chislo = febon[chet - 1] + febon[chet - 2];
                 febon << chislo;
            }
            chet--;
            step++;
        }
        else if (step == 2) {
            k=0;
            step++;
        }
        else if (step == 3) {
            x1=a+(febon[chet-2])*(b-a)/(febon[chet]);
            x2=a+(febon[chet-1])*(b-a)/(febon[chet]);
            step++;
        }
        else if (step == 4) {

            fx1 = alp->func(x1);
            fx2 = alp->func(x2);

            step++;
        }
        else if (step == 5) {
            if(fx1<=fx2){
                b=x2;
                x2=x1;
                x1=a+(febon[chet-k-3])*(b-a)/(febon[chet-k-1]);
            }
            else {
                a=x1;
                x1=x2;
                x2=a+(febon[chet-k-2])*(b-a)/(febon[chet-k-1]);
               }
            step++;
        }
        else if (step == 6) {
            if(k == chet - 3){
                x2=x1+0.0001;

                fx1 = alp->func(x1);
                fx2 = alp->func(x2);

                //------------------------

                if(fx1 <= fx2){
                    b=x2;
                }
                else{
                    a=x1;
                }
                step = 7;
            }
            else{
                k=k+1;
                step = 4;
            }

        }
        else if (step == 7) {
            res = (a+b)/(2);
            i++;
        }

        i--;
    }

    return res;
}

QVector<float>MainWindow::grad(function *f, QVector<float>x){

    QVector<float>res;
    for (int i = 1; i < x.length()+1; ++i) {
        res.append(f->dif1(x,i));
    }
    return res;
}

QVector<QVector<float>>MainWindow::gessa(function *f,QVector<float>x){

    QVector<QVector<float>>res;


    for (int i = 1; i < x.length() + 1; ++i) {
        QVector<float>*tmp = new QVector<float>;
        res.append(*tmp);
        for (int j = 1; j < x.length() + 1; ++j) {
            res[i-1].append(f->dif2(x,i,j));
        }
    }
     return res;
}

float MainWindow::norma(QVector<float>f){
    float res = 0;

    for (int i = 0; i < f.length(); ++i) {
        res += f[i]*f[i];
    }

    res= sqrt(res);
    return res;
}

float MainWindow::det(QVector<QVector<float>>f){

    float res = 0;
    float sub_det;

    if(f.length() == 2){
        res = f[0][0] * f[1][1] - f[0][1] * f[1][0];
        return res;
    }

    for (int col = 0; col < f.length(); ++col) {
        QVector<QVector<float>>temp;
        for (int i = 0; i < f.length()-1; ++i) {
            QVector<float>*tmp = new QVector<float>;
            temp.append(*tmp);
            for (int j = 0; j < f.length(); ++j) {
                temp[i].append(f[i+1][j]);
            }
        }

        for (int i = 0; i < temp.length(); ++i) {
            temp[i].removeAt(col);
        }

        int sign=1;

        for (int i = 0; i < col%2; ++i) {
            sign *= -1;
        }
        sub_det = det(temp);
        res += sign * f[0][col] * sub_det;
    }

    return res;
}

QVector<QVector<float>>MainWindow::minor(QVector<QVector<float>>f){

    QVector<QVector<float>>res;
    if(f.length() == 2){
        QVector<float>tmp1;
        tmp1 << f[1][1] << f[1][0];
        res.append(tmp1);

        QVector<float>tmp2;
        tmp2 << f[0][1] << f[0][0];
        res.append(tmp2);

        return res;
    }

    for (int row = 0; row < f.length(); ++row) {
        QVector<float>*tmp = new QVector<float>;
        res.append(*tmp);
        for (int col = 0; col < f.length(); ++col) {
            QVector<QVector<float>>temp;

            for(int i=0; i<f.length(); i++){
                if(i != row){
                    QVector <float> *ttmp = new QVector<float>;
                    for(int j=0; j<f.length(); j++){
                        ttmp->append(f[i][j]);
                    }
                    temp.append(*ttmp);
                }
            }

            for (int i = 0; i < temp.length(); ++i) {
                temp[i].removeAt(col);
            }

            res[row].append(det(temp));
        }
    }

    return res;
}

QVector<QVector<float>>MainWindow::mul(QVector<QVector<float>>f,float b){

    QVector<QVector<float>>res;

    for (int i = 0; i < f.length(); ++i) {
        QVector<float>*tmp = new QVector<float>;
        res.append(*tmp);
        for (int j = 0; j < f.length(); ++j) {
            res[i].append(f[i][j]);
        }
    }

    for (int i = 0; i < f.length(); ++i) {
        for (int j = 0; j < f.length(); ++j) {
           res[i][j] *= b;
        }
    }

    return res;
}

QVector<float>MainWindow::mul(QVector<float>f,float b){
    QVector<float>res;

    for (int i = 0; i < f.length(); i++) {
        res.append(f[i] * b);
    }
    return res;
}

QVector<float>MainWindow::mul(QVector<QVector<float>>f,QVector<float>b){

    QVector<float>res;

    float temp;

    for (int i = 0; i < f.length(); ++i) {
        temp = 0;
        for (int j = 0; j < f.length(); ++j) {
            temp += f[i][j] * b[j];
        }

        res.append(temp);
    }

    return res;
}

QVector<QVector<float>>MainWindow::envers_matrix(QVector<QVector<float>>f){

    QVector<QVector<float>>res;

    QVector<QVector<float>>minor_f = minor(f);

    float d = det(f);

    if(d==0){
        return res;
    }

    for (int row = 0; row < f.length(); ++row) {
        int sign_row=1;

        for (int i = 0; i < row%2; ++i) {
            sign_row *= -1;
        }

        for (int col = 0; col < f.length(); ++col) {
            int sign_col=1;

            for (int i = 0; i < col%2; ++i) {
                sign_col *= -1;
            }
            minor_f[row][col] *= sign_col * sign_row;
        }
    }

    //чичас венусь...
    //Вернулись))

    res=mul(minor_f,(1/d));
    return res;

}









