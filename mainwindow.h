#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <alpha.h>
#include <function.h>

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

    float find_minimum(alpha *alp);

    QVector<float>grad(function *f, QVector<float>x);

    QVector<QVector<float>>gessa(function *f,QVector<float>x);

    float norma(QVector<float>f);

    QVector<QVector<float>>envers_matrix(QVector<QVector<float>>f);

    float det(QVector<QVector<float>>f);

    QVector<QVector<float>>minor(QVector<QVector<float>>f);

    QVector<QVector<float>>mul(QVector<QVector<float>>f,float b);

    QVector<float>mul(QVector<float>f,float b);

    QVector<float>mul(QVector<QVector<float>>f,QVector<float>b);


};
#endif // MAINWINDOW_H
