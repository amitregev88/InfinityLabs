/****************************************************************************/
/*	File:		complexes.hpp												*/
/*	Date: 		18/09/2022													*/
/*	Name: 		Amit Regev												    */
/*	Reviewer:																*/
/****************************************************************************/

#ifndef __COMPLEXES__
#define __COMPLEXES__

#include <iostream>     //cin, cout
/*******************************Function Prototypes*************************/
namespace ilrd
{

class Complex;

inline Complex& operator+=(Complex &, const Complex &);
inline Complex& operator-=(Complex &, const Complex &);
inline Complex& operator*=(Complex &, const Complex &);
inline Complex& operator/=(Complex &, const Complex &);

inline const Complex operator+(Complex, const Complex &);
inline const Complex operator-(Complex, const Complex &);
inline const Complex operator*(Complex, const Complex &);
inline const Complex operator/(Complex, const Complex &);
 
inline bool operator==(Complex, Complex);
inline bool operator!=(Complex, Complex);
 
inline std::ostream& operator<<(std::ostream& os_, const Complex &num_);
std::istream& operator>>(std::istream& is_, Complex &num_);

class Complex
{
public: // Uses generated copy constractor, assignment operator and destructor
    inline Complex(double real_ = 0, double imaginary_ = 0); 
                                                    // uses implicit conversion
    inline void SetReal(double);
    inline void SetImaginary(double);
    inline double GetReal() const;
    inline double GetImaginary() const;

private:
    double m_real;
    double m_imaginary;
};

/****************************************************************************/
inline Complex::Complex(double real_, double imaginary_): 
 m_real(real_), m_imaginary(imaginary_)
{} 
/****************************************************************************/
inline void Complex::SetReal(double num_)
{
    m_real = num_;
}
/****************************************************************************/
inline void Complex::SetImaginary(double num_)
{
    m_imaginary = num_;
}
/****************************************************************************/
inline double Complex::GetReal() const
{
    return (m_real);
}
/****************************************************************************/
inline double Complex::GetImaginary() const
{
    return (m_imaginary);
}
/****************************************************************************/
inline Complex& operator+=(Complex &num1_, const Complex &num2_)
{
    num1_.SetReal(num1_.GetReal() + num2_.GetReal());
    num1_.SetImaginary(num1_.GetImaginary() + num2_.GetImaginary());

    return (num1_);
}
/****************************************************************************/
inline Complex& operator-=(Complex &num1_, const Complex &num2_)
{
    num1_.SetReal(num1_.GetReal() - num2_.GetReal());
    num1_.SetImaginary(num1_.GetImaginary() - num2_.GetImaginary());

    return (num1_);
}
/****************************************************************************/
inline Complex& operator*=(Complex &num1_, const Complex &num2_)
{
    num1_.SetReal(num1_.GetReal() * num2_.GetReal());
    num1_.SetImaginary(num1_.GetImaginary() * num2_.GetImaginary());

    return (num1_);
}

/****************************************************************************/
inline Complex& operator/=(Complex &num1_, const Complex &num2_)
{
    num1_.SetReal(num1_.GetReal() / num2_.GetReal());
    num1_.SetImaginary(num1_.GetImaginary() / num2_.GetImaginary());

    return (num1_);
}

/****************************************************************************/
inline const Complex operator+(Complex num1_, const Complex &num2_)
{
    return (num1_ += num2_);
}

/****************************************************************************/
inline const Complex operator-(Complex num1_, const Complex& num2_)
{
    return (num1_ -= num2_);
}

/****************************************************************************/
inline const Complex operator*(Complex num1_, const Complex& num2_)
{
    return (num1_ *= num2_);
}

/****************************************************************************/
inline const Complex operator/(Complex num1_, const Complex& num2_)
{
    return (num1_ /= num2_);
}
 
/****************************************************************************/ 
inline bool operator==(Complex num1_, Complex num2_)
{
    return (num1_.GetReal() == num2_.GetReal() && 
            num1_.GetImaginary() == num2_.GetImaginary());
}

/****************************************************************************/
inline bool operator!=(Complex num1_, Complex num2_)
{
    return (!operator==(num1_, num2_));
}

/****************************************************************************/
inline std::ostream& operator<<(std::ostream& os_, const Complex &num_)
{   
    return (os_ << num_.GetReal() <<" " <<num_.GetImaginary() << 'i');
}

/****************************************************************************/

} // namespace ilrd

#endif /*	ifndef __COMPLEXES__									    */
/*********************************End Of Header******************************/
