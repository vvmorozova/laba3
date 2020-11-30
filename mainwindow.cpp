#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include "complexnumber.h"
#include "quaternion.h"
#include "collection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s = new Stack<Quaternion>();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_workWithOneQuant_RB_clicked()
{
    if (s->isEmpty())
    {
        ui->workWithTwoQuant_RB->setChecked(true);
        return;
    }

    ui->widget_2->setEnabled(false);
}

void MainWindow::on_plusBtn_clicked()
{
    if (ui->workWithOneQuant_RB->isChecked())
    {
        if (!(ui->firstQuant_R_LE->text().length() != 0
                && ui->firstQuant_I_LE->text().length() != 0
                && ui->firstQuant_J_LE->text().length() != 0
                && ui->firstQuant_K_LE->text().length() != 0))
        {
            return;
        }

        double q_r = ui->firstQuant_R_LE->text().toDouble();
        double q_i = ui->firstQuant_I_LE->text().toDouble();
        double q_j = ui->firstQuant_J_LE->text().toDouble();
        double q_k = ui->firstQuant_K_LE->text().toDouble();

        Quaternion q1 = Quaternion(q_r, q_i, q_j, q_k);
        Quaternion* tmp_top = s->pop();
        Quaternion q3 = q1 + *tmp_top;

        s->push(new Quaternion(q3));

        ui->firstStackQuant_R_LE->setText(QString::number((q3.getR())));
        ui->firstStackQuant_I_LE->setText(QString::number((q3.getI())));
        ui->firstStackQuant_J_LE->setText(QString::number((q3.getJ())));
        ui->firstStackQuant_K_LE->setText(QString::number((q3.getK())));

        delete tmp_top;

        return;
    }

    if (ui->workWithTwoQuant_RB->isChecked())
    {
        if (!(ui->firstQuant_R_LE->text().length() != 0
              && ui->firstQuant_I_LE->text().length() != 0
              && ui->firstQuant_J_LE->text().length() != 0
              && ui->firstQuant_K_LE->text().length() != 0
              && ui->secondQuant_R_LE->text().length() != 0
              && ui->secondQuant_I_LE->text().length() != 0
              && ui->secondQuant_J_LE->text().length() != 0
              && ui->secondQuant_K_LE->text().length() != 0))
        {
            return;
        }

        double q1_r = ui->firstQuant_R_LE->text().toDouble();
        double q1_i = ui->firstQuant_I_LE->text().toDouble();
        double q1_j = ui->firstQuant_J_LE->text().toDouble();
        double q1_k = ui->firstQuant_K_LE->text().toDouble();

        double q2_r = ui->secondQuant_R_LE->text().toDouble();
        double q2_i = ui->secondQuant_I_LE->text().toDouble();
        double q2_j = ui->secondQuant_J_LE->text().toDouble();
        double q2_k = ui->secondQuant_K_LE->text().toDouble();

        Quaternion q1 = Quaternion(q1_r, q1_i, q1_j, q1_k);
        Quaternion q2 = Quaternion(q2_r, q2_i, q2_j, q2_k);
        Quaternion q_top = q1 + q2;

        if (!s->isEmpty())
        {
            Quaternion* q_underTop = s->pop();
            s->push(new Quaternion(*q_underTop));

            ui->secondStackQuant_R_LE->setText(QString::number((q_underTop->getR())));
            ui->secondStackQuant_I_LE->setText(QString::number((q_underTop->getI())));
            ui->secondStackQuant_J_LE->setText(QString::number((q_underTop->getJ())));
            ui->secondStackQuant_K_LE->setText(QString::number((q_underTop->getK())));

            delete q_underTop;
        }

        s->push(new Quaternion(q_top));

        ui->firstStackQuant_R_LE->setText(QString::number((q_top.getR())));
        ui->firstStackQuant_I_LE->setText(QString::number((q_top.getI())));
        ui->firstStackQuant_J_LE->setText(QString::number((q_top.getJ())));
        ui->firstStackQuant_K_LE->setText(QString::number((q_top.getK())));

        return;
    }
}

void MainWindow::on_minusBtn_clicked()
{
    if (ui->workWithOneQuant_RB->isChecked())
    {
        if (!(ui->firstQuant_R_LE->text().length() != 0
                && ui->firstQuant_I_LE->text().length() != 0
                && ui->firstQuant_J_LE->text().length() != 0
                && ui->firstQuant_K_LE->text().length() != 0))
        {
            return;
        }

        double q_r = ui->firstQuant_R_LE->text().toDouble();
        double q_i = ui->firstQuant_I_LE->text().toDouble();
        double q_j = ui->firstQuant_J_LE->text().toDouble();
        double q_k = ui->firstQuant_K_LE->text().toDouble();

        Quaternion q1 = Quaternion(q_r, q_i, q_j, q_k);
        Quaternion* tmp_top = s->pop();
        Quaternion q3 = q1 - *tmp_top;

        s->push(new Quaternion(q3));

        ui->firstStackQuant_R_LE->setText(QString::number((q3.getR())));
        ui->firstStackQuant_I_LE->setText(QString::number((q3.getI())));
        ui->firstStackQuant_J_LE->setText(QString::number((q3.getJ())));
        ui->firstStackQuant_K_LE->setText(QString::number((q3.getK())));

        delete tmp_top;

        return;
    }

    if (ui->workWithTwoQuant_RB->isChecked())
    {
        if (!(ui->firstQuant_R_LE->text().length() != 0
              && ui->firstQuant_I_LE->text().length() != 0
              && ui->firstQuant_J_LE->text().length() != 0
              && ui->firstQuant_K_LE->text().length() != 0
              && ui->secondQuant_R_LE->text().length() != 0
              && ui->secondQuant_I_LE->text().length() != 0
              && ui->secondQuant_J_LE->text().length() != 0
              && ui->secondQuant_K_LE->text().length() != 0))
        {
            return;
        }

        double q1_r = ui->firstQuant_R_LE->text().toDouble();
        double q1_i = ui->firstQuant_I_LE->text().toDouble();
        double q1_j = ui->firstQuant_J_LE->text().toDouble();
        double q1_k = ui->firstQuant_K_LE->text().toDouble();

        double q2_r = ui->secondQuant_R_LE->text().toDouble();
        double q2_i = ui->secondQuant_I_LE->text().toDouble();
        double q2_j = ui->secondQuant_J_LE->text().toDouble();
        double q2_k = ui->secondQuant_K_LE->text().toDouble();

        Quaternion q1 = Quaternion(q1_r, q1_i, q1_j, q1_k);
        Quaternion q2 = Quaternion(q2_r, q2_i, q2_j, q2_k);
        Quaternion q_top = q1 - q2;

        if (!s->isEmpty())
        {
            Quaternion* q_underTop = s->pop();
            s->push(new Quaternion(*q_underTop));

            ui->secondStackQuant_R_LE->setText(QString::number((q_underTop->getR())));
            ui->secondStackQuant_I_LE->setText(QString::number((q_underTop->getI())));
            ui->secondStackQuant_J_LE->setText(QString::number((q_underTop->getJ())));
            ui->secondStackQuant_K_LE->setText(QString::number((q_underTop->getK())));

            delete q_underTop;
        }

        s->push(new Quaternion(q_top));

        ui->firstStackQuant_R_LE->setText(QString::number((q_top.getR())));
        ui->firstStackQuant_I_LE->setText(QString::number((q_top.getI())));
        ui->firstStackQuant_J_LE->setText(QString::number((q_top.getJ())));
        ui->firstStackQuant_K_LE->setText(QString::number((q_top.getK())));

        return;
    }
}

void MainWindow::on_multBtn_clicked()
{
    if (ui->workWithOneQuant_RB->isChecked())
    {
        if (!(ui->firstQuant_R_LE->text().length() != 0
                && ui->firstQuant_I_LE->text().length() != 0
                && ui->firstQuant_J_LE->text().length() != 0
                && ui->firstQuant_K_LE->text().length() != 0))
        {
            return;
        }

        double q_r = ui->firstQuant_R_LE->text().toDouble();
        double q_i = ui->firstQuant_I_LE->text().toDouble();
        double q_j = ui->firstQuant_J_LE->text().toDouble();
        double q_k = ui->firstQuant_K_LE->text().toDouble();

        Quaternion q1 = Quaternion(q_r, q_i, q_j, q_k);
        Quaternion* tmp_top = s->pop();
        Quaternion q3 = q1 * *tmp_top;

        s->push(new Quaternion(q3));

        ui->firstStackQuant_R_LE->setText(QString::number((q3.getR())));
        ui->firstStackQuant_I_LE->setText(QString::number((q3.getI())));
        ui->firstStackQuant_J_LE->setText(QString::number((q3.getJ())));
        ui->firstStackQuant_K_LE->setText(QString::number((q3.getK())));

        delete tmp_top;

        return;
    }

    if (ui->workWithTwoQuant_RB->isChecked())
    {
        if (!(ui->firstQuant_R_LE->text().length() != 0
              && ui->firstQuant_I_LE->text().length() != 0
              && ui->firstQuant_J_LE->text().length() != 0
              && ui->firstQuant_K_LE->text().length() != 0
              && ui->secondQuant_R_LE->text().length() != 0
              && ui->secondQuant_I_LE->text().length() != 0
              && ui->secondQuant_J_LE->text().length() != 0
              && ui->secondQuant_K_LE->text().length() != 0))
        {
            return;
        }

        double q1_r = ui->firstQuant_R_LE->text().toDouble();
        double q1_i = ui->firstQuant_I_LE->text().toDouble();
        double q1_j = ui->firstQuant_J_LE->text().toDouble();
        double q1_k = ui->firstQuant_K_LE->text().toDouble();

        double q2_r = ui->secondQuant_R_LE->text().toDouble();
        double q2_i = ui->secondQuant_I_LE->text().toDouble();
        double q2_j = ui->secondQuant_J_LE->text().toDouble();
        double q2_k = ui->secondQuant_K_LE->text().toDouble();

        Quaternion q1 = Quaternion(q1_r, q1_i, q1_j, q1_k);
        Quaternion q2 = Quaternion(q2_r, q2_i, q2_j, q2_k);
        Quaternion q_top = q1 * q2;

        if (!s->isEmpty())
        {
            Quaternion* q_underTop = s->pop();
            s->push(new Quaternion(*q_underTop));

            ui->secondStackQuant_R_LE->setText(QString::number((q_underTop->getR())));
            ui->secondStackQuant_I_LE->setText(QString::number((q_underTop->getI())));
            ui->secondStackQuant_J_LE->setText(QString::number((q_underTop->getJ())));
            ui->secondStackQuant_K_LE->setText(QString::number((q_underTop->getK())));

            delete q_underTop;
        }

        s->push(new Quaternion(q_top));

        ui->firstStackQuant_R_LE->setText(QString::number((q_top.getR())));
        ui->firstStackQuant_I_LE->setText(QString::number((q_top.getI())));
        ui->firstStackQuant_J_LE->setText(QString::number((q_top.getJ())));
        ui->firstStackQuant_K_LE->setText(QString::number((q_top.getK())));

        return;
    }
}

void MainWindow::on_divBtn_clicked()
{
    if (ui->workWithOneQuant_RB->isChecked())
    {
        if (!(ui->firstQuant_R_LE->text().length() != 0
                && ui->firstQuant_I_LE->text().length() != 0
                && ui->firstQuant_J_LE->text().length() != 0
                && ui->firstQuant_K_LE->text().length() != 0))
        {
            return;
        }

        double q_r = ui->firstQuant_R_LE->text().toDouble();
        double q_i = ui->firstQuant_I_LE->text().toDouble();
        double q_j = ui->firstQuant_J_LE->text().toDouble();
        double q_k = ui->firstQuant_K_LE->text().toDouble();

        Quaternion q1 = Quaternion(q_r, q_i, q_j, q_k);
        Quaternion* tmp_top = s->pop();
        Quaternion q3 = q1 / *tmp_top;

        s->push(new Quaternion(q3));

        ui->firstStackQuant_R_LE->setText(QString::number((q3.getR())));
        ui->firstStackQuant_I_LE->setText(QString::number((q3.getI())));
        ui->firstStackQuant_J_LE->setText(QString::number((q3.getJ())));
        ui->firstStackQuant_K_LE->setText(QString::number((q3.getK())));

        delete tmp_top;

        return;
    }

    if (ui->workWithTwoQuant_RB->isChecked())
    {
        if (!(ui->firstQuant_R_LE->text().length() != 0
              && ui->firstQuant_I_LE->text().length() != 0
              && ui->firstQuant_J_LE->text().length() != 0
              && ui->firstQuant_K_LE->text().length() != 0
              && ui->secondQuant_R_LE->text().length() != 0
              && ui->secondQuant_I_LE->text().length() != 0
              && ui->secondQuant_J_LE->text().length() != 0
              && ui->secondQuant_K_LE->text().length() != 0))
        {
            return;
        }

        double q1_r = ui->firstQuant_R_LE->text().toDouble();
        double q1_i = ui->firstQuant_I_LE->text().toDouble();
        double q1_j = ui->firstQuant_J_LE->text().toDouble();
        double q1_k = ui->firstQuant_K_LE->text().toDouble();

        double q2_r = ui->secondQuant_R_LE->text().toDouble();
        double q2_i = ui->secondQuant_I_LE->text().toDouble();
        double q2_j = ui->secondQuant_J_LE->text().toDouble();
        double q2_k = ui->secondQuant_K_LE->text().toDouble();

        Quaternion q1 = Quaternion(q1_r, q1_i, q1_j, q1_k);
        Quaternion q2 = Quaternion(q2_r, q2_i, q2_j, q2_k);
        Quaternion q_top = q1 / q2;

        if (!s->isEmpty())
        {
            Quaternion* q_underTop = s->pop();
            s->push(new Quaternion(*q_underTop));

            ui->secondStackQuant_R_LE->setText(QString::number((q_underTop->getR())));
            ui->secondStackQuant_I_LE->setText(QString::number((q_underTop->getI())));
            ui->secondStackQuant_J_LE->setText(QString::number((q_underTop->getJ())));
            ui->secondStackQuant_K_LE->setText(QString::number((q_underTop->getK())));

            delete q_underTop;
        }

        s->push(new Quaternion(q_top));

        ui->firstStackQuant_R_LE->setText(QString::number((q_top.getR())));
        ui->firstStackQuant_I_LE->setText(QString::number((q_top.getI())));
        ui->firstStackQuant_J_LE->setText(QString::number((q_top.getJ())));
        ui->firstStackQuant_K_LE->setText(QString::number((q_top.getK())));

        return;
    }
}

void MainWindow::on_workWithTwoQuant_RB_clicked()
{
    ui->widget_2->setEnabled(true);
}
