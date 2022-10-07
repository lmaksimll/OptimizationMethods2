#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

    float Predel[2];
    float zero[2][4];
    float res = 0;

    zero[0][0] = ui->x1->value();
    zero[0][1] = ui->x2->value();
    zero[0][2] = ui->x3->value();
    zero[0][3] = ui->x4->value();

    zero[1][0] = ui->h1->value();
    zero[1][1] = ui->h2->value();
    zero[1][2] = ui->h3->value();
    zero[1][3] = ui->h4->value();

    if(ui->function1->isChecked()){
        qDebug()<<"1 функция";
        Med_devisa(1,zero,Predel);

        if(ui->method1->isChecked()){
           qDebug()<<"1 метод";

        }
        else if(ui->method2->isChecked()){
           qDebug()<<"2 метод";

        }
        else if(ui->method3->isChecked()){
           qDebug()<<"3 метод";

        }
        else {
            qDebug()<<"метод не выбран";
        }
    }

}

float MainWindow::Gaysa_Zedele(){

    int step = 1;
    float res;
    float k;
    float i;
    int a;
    for (int i=0;i<1;i++){

        if(step == 1){
            k=0;
        }
        else if(step == 2){
            i=1;
        }
        else if(step == 3){

        }
        else if(step == 4){}
        else if(step == 5){}
        else if(step == 6){}
        else if(step == 7){}
        else if(step == 8){}
        else if(step == 9){}
        else if(step == 10){}

        i--;
    }

    return res;
}

float MainWindow::Med_devisa(int f,float z[2][4],float N[2]){

    int step = 1;
    float fx0=0;    //у при начальной точке
    float fx1=0;    //у при точке + 1 шаг
    float fx_1=0;   //у при точке - 1 шаг
    float x1=0;     //z + шаг
    float xk=0;     //z + 2 * шаг
    float h=1;      //шаг
    float fxk=0;    //у при хк
    float xk_1=0;   //хк - 1
    float xk_2=0;   //xk - 2
    float fxk_1=0;  //у при хл_1
    float a=0;
    float b = 0;
    float k = 0;

    for (int i=0;i<1;i++) {
            if(step == 1){                          //Шаг 1
                fx0=function(1,)
                fx1=
                step++;
            }
            else if(step==2){                       //Шаг 2

                if (fx0 > fx1){
                    a = z;
                    x1 = z + h;
                    k = 2;
                    step=4;
                }
                else {
                    if(f==1){                   //Выбор нужной функции
                        z-=h;
                        fx_1 = (z-1)*(z-1);
                        z+=h;
                    }
                    else if(f==2){
                        z-=h;
                        fx_1 = (z*z*z*4)-(z*z*8)-(z*11)+5;
                        z+=h;
                    }
                    else if(f==3){
                        z-=h;
                        fx_1 = z+((3)/(z*z));
                        z+=h;
                    }
                    else if(f==4){
                        z-=h;
                        fx_1 = (z+2.5)/(4-(z*z));
                        z+=h;
                    }
                    step=3;
                }
            }
            else if(step==3){                       //Шаг 3

                if (fx_1 >= fx0){
                    a = z - h;
                    b = z + h;
                    step=6;
                }
                else {
                    b = z;
                    x1 = z - h;
                    k = 2;
                    step=4;
                }
            }
            else if(step==4){                       //Шаг 4
                int k2 = 1;
                for (int j=0;j<k-1;j++) {
                    k2 = k2 * 2;
                }
                xk=z+k2*h;

                //--------------------

                if(f==1){                   //Выбор нужной функции
                    fxk = (xk-1)*(xk-1);
                }
                else if(f==2){
                    fxk = (xk*xk*xk*4)-(xk*xk*8)-(xk*11)+5;
                }
                else if(f==3){
                    fxk = xk+((3)/(xk*xk));
                }
                else if(f==4){
                    fxk = (xk+2.5)/(4-(xk*xk));
                }
                step=5;
            }
            else if(step==5){                       //Шаг 5
                xk_1 = xk - 1;

                //-------------------

                if(f==1){                   //Выбор нужной функции
                    fxk_1 = (xk_1-1)*(xk_1-1);
                }
                else if(f==2){
                    fxk_1 = (xk_1*xk_1*xk_1*4)-(xk_1*xk_1*8)-(xk_1*11)+5;
                }
                else if(f==3){
                    fxk_1 = xk_1+((3)/(xk_1*xk_1));
                }
                else if(f==4){
                    fxk_1 = (xk_1+2.5)/(4-(xk_1*xk_1));
                }

                //-------------------

                if(fxk_1<=fxk){
                    if(h>0){
                        b=xk;
                        step=6;
                    }
                    else {
                        a=xk;
                        step=6;
                    }
                }
                else {
                    if(h>0){
                        xk_2 = xk - 2;
                        a=xk_2;
                    }
                    else {
                        b=xk;
                    }
                    k = k + 1;
                    step=4;
                }
            }
            else if(step==6){                       //Шаг 6
                i++;
            }

            i--;
        }

    N[0]= a;
    N[1]= b;

    return *N;
}

float MainWindow::Med_popolam(int f,float N[2]){

}

float MainWindow::function(int f,float x1,float x2){

    float res;


    if(f==1){
        //res = ((z[0][0]-5)*(z[0][0]-5)*4)+((z[0][1]-6)*(z[0][1]-6));
    }
    else if(f==2){
        //res = ((z[0][0]*z[0][0])*())+(()*())
    }
    else if(f==3){
        //res =
    }
    else if(f==4){
        //res =
    }

    return res;
}
