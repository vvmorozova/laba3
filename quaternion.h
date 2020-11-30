#ifndef QUATERNION_H
#define QUATERNION_H
#include <string>
#include "complexnumber.h"

class Quaternion : public ComplexNumber
{
public:
    Quaternion()
    {
        setJ(0.);
        setK(0.);
    }

    ~Quaternion(){}

    Quaternion(double r) : ComplexNumber(r)
    {
        setJ(0.);
        setK(0.);
    }

    Quaternion(double r, double i) : ComplexNumber(r, i)
    {
        setJ(0.);
        setK(0.);
    }

    Quaternion(double r, double i, double j) : ComplexNumber(r, i)
    {
        setJ(j);
        setK(0.);
    }

    Quaternion(double r, double i, double j, double k) : Quaternion(r, i, j)
    {
        setK(k);
    }

    std::string to_string() override
    {
        return
            std::to_string((int)this->getR()) +  " + " +
            std::to_string((int)this->getI()) + "i + " +
            std::to_string((int)this->getJ()) + "j + " +
            std::to_string((int)this->getK()) + "k"    ;
    }

    const friend bool operator !=(Quaternion& n1, Quaternion& n2)
    {
        return !(
            n1.getR() == n2.getR() &&
            n1.getI() == n2.getI() &&
            n1.getJ() == n2.getJ() &&
            n1.getK() == n2.getK()
            );
    }

    const friend bool operator ==(Quaternion& n1, Quaternion& n2)
    {
        return (
            n1.getR() == n2.getR() &&
            n1.getI() == n2.getI() &&
            n1.getJ() == n2.getJ() &&
            n1.getK() == n2.getK()
            );
    }

    Quaternion operator +(Quaternion q)
    {
        return Quaternion(
            this->getR() + q.getR(),
            this->getI() + q.getI(),
            this->getJ() + q.getJ(),
            this->getK() + q.getK()
        );
    }

    Quaternion operator -(Quaternion q)
    {
        return Quaternion(
            this->getR() - q.getR(),
            this->getI() - q.getI(),
            this->getJ() - q.getJ(),
            this->getK() - q.getK()
        );
    }

    Quaternion operator *(Quaternion q)
    {
        double c_0;
        double c_1;
        double c_2;
        double c_3;

        double a_0 = this->getR();
        double a_1 = this->getI();
        double a_2 = this->getJ();
        double a_3 = this->getK();
        double b_0 = q.getR();
        double b_1 = q.getI();
        double b_2 = q.getJ();
        double b_3 = q.getK();

        c_0 = a_0 * b_0 - a_1 * b_1 - a_2 * b_2 - a_3 * b_3;
        c_1 = a_0 * b_1 + a_1 * b_0 + a_2 * b_3 - a_3 * b_2;
        c_2 = a_0 * b_2 - a_1 * b_3 + a_2 * b_0 + a_3 * b_1;
        c_3 = a_0 * b_3 + a_1 * b_2 - a_2 * b_1 + a_3 * b_0;

        return Quaternion(c_0, c_1, c_2, c_3);
    }

    Quaternion operator /(Quaternion q)
    {
        double c_0;
        double c_1;
        double c_2;
        double c_3;

        double a_0 = this->getR();
        double a_1 = this->getI();
        double a_2 = this->getJ();
        double a_3 = this->getK();

        double b_0 = q.getR();
        double b_1 = q.getI();
        double b_2 = q.getJ();
        double b_3 = q.getK();

        int divider = b_0 * b_0 + b_1 * b_1 + b_2 * b_2 + b_3 * b_3;

        if (divider == 0)
            throw std::invalid_argument("Divide by zero");

        c_0 = (b_0 * a_0 + b_1 * a_1 + b_2 * a_2 + b_3 * a_3) /
            (b_0 * b_0 + b_1 * b_1 + b_2 * b_2 + b_3 * b_3);

        c_1 = (b_0 * a_1 - b_1 * a_0 - b_2 * a_3 + b_3 * a_2) /
            (b_0 * b_0 + b_1 * b_1 + b_2 * b_2 + b_3 * b_3);

        c_2 = (b_0 * a_2 + b_1 * a_3 - b_2 * a_0 - b_3 * a_1) /
            (b_0 * b_0 + b_1 * b_1 + b_2 * b_2 + b_3 * b_3);

        c_3 = (b_0 * a_3 - b_1 * a_2 + b_2 * a_1 - b_3 * a_0) /
            (b_0 * b_0 + b_1 * b_1 + b_2 * b_2 + b_3 * b_3);

        return Quaternion(c_0, c_1, c_2, c_3);
    }

    void setJ(double j)
    {
        this->j = j;
    }

    double getJ()
    {
        return this->j;
    }

    void setK(double k)
    {
        this->k = k;
    }

    double getK()
    {
        return this->k;
    }

private:
    double j, k;
};



#endif // QUATERNION_H
