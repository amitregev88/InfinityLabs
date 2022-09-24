/****************************************************************************/
/*	File:		complexes.hpp												*/
/*	Date: 		18/09/2022													*/
/*	Name: 		Amit Regev												    */
/*	Reviewer:	Boaz														*/
/****************************************************************************/
#ifndef __COMPLEXES__
#define __COMPLEXES__

#include <iostream>     //cin, cout
/*******************************Function Prototypes*************************/
namespace ilrd
{

class Complex;

inline Complex& operator+=(Complex&, const Complex &);
inline Complex& operator-=(Complex&, const Complex &);
inline Complex& operator*=(Complex&, const Complex &);
inline Complex& operator/=(Complex&, const Complex &);

inline const Complex operator+(Complex, const Complex&);
inline const Complex operator-(Complex, const Complex&);
inline const Complex operator*(Complex, const Complex&);
inline const Complex operator/(Complex, const Complex&);
 
inline bool operator==(Complex, const Complex&);
inline bool operator!=(Complex, const Complex&);
 
inline std::ostream& operator<<(std::ostream& os_, const Complex &num_);
std::istream& operator>>(std::istream& is_, Complex &num_);

class Complex
{
public: 
    inline Complex(double real_ = 0, double imaginary_ = 0); 
                                                    //non explicit on purpose
                                                    //implicit conversion

    //copy constractor, assignment operator and destructor are generated
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
inline Complex& operator+=(Complex &n1_, const Complex &n2_)
{
    n1_.SetReal(n1_.GetReal() + n2_.GetReal());
    n1_.SetImaginary(n1_.GetImaginary() + n2_.GetImaginary());

    return (n1_);
}
/****************************************************************************/
inline Complex& operator-=(Complex &n1_, const Complex &n2_)
{
    n1_.SetReal(n1_.GetReal() - n2_.GetReal());
    n1_.SetImaginary(n1_.GetImaginary() - n2_.GetImaginary());

    return (n1_);
}
/****************************************************************************/
inline Complex& operator*=(Complex &n1_, const Complex &n2_)
{
    n1_.SetReal(n1_.GetReal() * n2_.GetReal());
    n1_.SetImaginary(n1_.GetImaginary() * n2_.GetImaginary());

    return (n1_);
}

/****************************************************************************/
inline Complex& operator/=(Complex &n1_, const Complex &n2_)
{
    n1_.SetReal(n1_.GetReal() / n2_.GetReal());
    n1_.SetImaginary(n1_.GetImaginary() / n2_.GetImaginary());

    return (n1_);
}

/****************************************************************************/
inline const Complex operator+(Complex n1_, const Complex &n2_)
{
    return (n1_ += n2_);
}

/****************************************************************************/
inline const Complex operator-(Complex n1_, const Complex& n2_)
{
    return (n1_ -= n2_);
}

/****************************************************************************/
inline const Complex operator*(Complex n1_, const Complex& n2_)
{
    return (n1_ *= n2_);
}

/****************************************************************************/
inline const Complex operator/(Complex n1_, const Complex& n2_)
{
    return (n1_ /= n2_);
}
 
/****************************************************************************/ 
inline bool operator==(Complex n1_, const Complex& n2_)
{
    return (n1_.GetReal() == n2_.GetReal() && 
            n1_.GetImaginary() == n2_.GetImaginary());
}

/****************************************************************************/
inline bool operator!=(Complex n1_, const Complex& n2_)
{
    return (!operator==(n1_, n2_));
}

/****************************************************************************/
inline std::ostream& operator<<(std::ostream& os_, const Complex &num_)
{   
    return (os_ << "("<<num_.GetReal() <<", " <<num_.GetImaginary() << "i)");
}

/****************************************************************************/

} 

#endif //	ifndef __COMPLEXES__

