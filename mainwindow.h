#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:

    void res();

    float Med_devisa(int f,float z[2][4],float N[2]);
    float Med_popolam(int f,float N[2]);
    float Gaysa_Zedele();

    float function(int f,float x1,float x2);



};
#endif // MAINWINDOW_H
