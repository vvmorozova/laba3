#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "complexnumber.h"
#include "quaternion.h"
#include "collection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_workWithOneQuant_RB_clicked();

    void on_plusBtn_clicked();

    void on_minusBtn_clicked();

    void on_multBtn_clicked();

    void on_divBtn_clicked();

    void on_workWithTwoQuant_RB_clicked();

private:
    Ui::MainWindow *ui;
    Stack<Quaternion>* s;
};
#endif // MAINWINDOW_H
