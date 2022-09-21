/********************************************/
/* Project:C++ Complex                      */
/* Date: 18/09/2022                         */
/*  Reviewer                                */
/*                 HRD025                   */
/********************************************/

#include <iostream>

#ifndef __COMPLEX__
#define __COMPLEX__


Complex& operator+=(Complex&, const Complex&);
Complex& operator-=(Complex&, const Complex&);
Complex& operator*=(Complex&, const Complex&);
Complex& operator/=(Complex&, const Complex&);

const Complex operator+(const Complex&, const Complex&);
const Complex operator-(const Complex&, const Complex&);
const Complex operator*(const Complex&, const Complex&);
const Complex operator/(const Complex&, const Complex&);

bool operator==(const Complex&, const Complex&);
bool operator!=(const Complex&, const Complex&);

std::ostream& operator<<(std::ostream& os_, const Complex&);
std::istream& operator>>(std::istream& is_, Complex&);


class Complex
{
    public:
    Complex(double real = 0, double imag = 0); //non explicit on purpose
    //copy and = generated


    void SetReal(double cmplx_);
    void SetImaginary(double cmplx_);

    double GetReal()const;
    double GetImaginary()const;


    private:
    Complex(const Complex&);//for disabling , Do Not IMPLEMENT
    int m_num_real;
    int m_num_imaginary;
}

#endif __COMPLEX__;