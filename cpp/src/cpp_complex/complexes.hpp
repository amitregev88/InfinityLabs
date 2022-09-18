/********************************************/
/* Project:C++ Complex                      */
/* Date: 18/09/2022                         */
/*  Reviewer                                */
/*                 HRD025                   */
/********************************************/


#ifndef __COMPLEX__
#define __COMPLEX__


complexes operator+=(complexes& _n1, const complexes& _n2);
complexes operator-=(complexes& _n1, const complexes& _n2);
complexes operator*=(complexes& _n1, const complexes& _n2);
complexes operator/=(complexes& _n1, const complexes& _n2);
complexes operator+(const complexes& _n1, complexes& n2);
complexes operator-(const complexes& _n1, complexes& n2);
complexes operator*(const complexes& _n1, const complexes& _n2);
complexes operator/(const complexes& _n1, const complexes& _n2);
bool operator==(const complexes& _n1, const complexes& _n2);
bool operator!=(const complexes& _n1, const complexes& _n2);

//cin?
//cout?



class complexes
{
    public:
    void SetReal(int _num);
    void SetImaginary(int _num);
    int GetReal()const;
    int GetImaginary()const;


    private:
    int m_num_real;
    int m_num_imaginary;
}

#endif