#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <string>
#include <stdexcept>
#include <iostream>

class ComplexNumber
{
public:

    ComplexNumber()
    {
        setR(1.0);
        setI(0.0);
        isset = true;
    }

    ComplexNumber(double r)
    {
        setR(r);
        isset = true;
    }

    ComplexNumber(double r, double i)
    {
        setR(r);
        setI(i);
        isset = true;
    }

    ComplexNumber(ComplexNumber* cn)
    {
        setR(cn->getR());
        setI(cn->getI());
        isset = true;
    }

    ~ComplexNumber() {}

    const friend bool operator !=(ComplexNumber& n1, ComplexNumber& n2)
    {
        return !(
            n1.getR() == n2.getR() &&
            n1.getI() == n2.getI()
            );
    }

    const friend bool operator ==(ComplexNumber& n1, ComplexNumber& n2)
    {
        return (
            n1.getR() == n2.getR() &&
            n1.getI() == n2.getI()
            );
    }

    virtual std::string to_string()
    {
        return std::to_string((int)(getR())) + " + " +
               std::to_string((int)(getI())) + "i";
    }

    const bool operator !()
    {
        return isset;
    }

    ComplexNumber operator +(ComplexNumber cn)
    {
        return ComplexNumber(
            this->getR() + cn.getR(),
            this->getI() + cn.getI()
        );
    }

    ComplexNumber operator -(ComplexNumber cn)
    {
        return ComplexNumber(
            this->getR() - cn.getR(),
            this->getI() - cn.getI()
        );
    }

    ComplexNumber operator *(ComplexNumber cn)
    {
        return ComplexNumber(
            this->getR() * cn.getR() -
            this->getI() * cn.getI(),
            this->getR() * cn.getI() +
            this->getI() * cn.getR()
        );
    }

    ComplexNumber operator /(ComplexNumber cn)
    {
        try
        {
            int a_r = this->getR();
            int a_i = this->getI();

            int b_r = cn.getR();
            int b_i = cn.getI();

            int c_r;
            int c_i;

            int divider = b_r * b_r + b_i * b_i;

            if (divider == 0) throw std::invalid_argument("Divide by zero");

            c_r = (a_r * b_r + a_i * b_i) /
                (b_r * b_r + b_i * b_i);

            c_i = (b_r * a_i + a_r * b_i) /
                (b_r * b_r + b_i * b_i);

            return ComplexNumber(c_r, c_i);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << "Error's stack\n";
            std::cerr << "\tin class ComplexNumber\n";
            throw std::invalid_argument(e);
        }
    }

    void setR(double r)
    {
        this->r = r;
    }

    void setI(double i)
    {
        this->i = i;
    }

    const double getR()
    {
        return r;
    }

    const double getI()
    {
        return i;
    }

protected:
    double r;
    double i;
    bool isset = false;
};

#endif // COMPLEXNUMBER_H
