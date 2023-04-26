/****************************************************************************/
/*	Project:	Square API           		    							*/
/*	File:		both.hpp						    						*/
/*	Date: 		05/01/2023													*/
/*	Name: 		Amit Regev     												*/
/*	Version: 	1.00														*/
/****************************************************************************/
#ifndef __BOTH_HPP__
#define __BOTH_HPP__

#include "shape.hpp"


class Both : public Shape
{

public:
    
    explicit Both(double size_ = 0, double x_center_ = 0, double y_center_  = 0) : Shape(NO_COLOR, size_, x_center_, y_center_){}; 
    ~Both() noexcept = default; 
    Both& operator=(const Both& o_) = default;
    Both(const Both& o_) = default; 

    void Print();     

};

void Both:: Print()
{
    std::cout << "Square and Circle Data\n\n" << "Color: " << GetColor()<<"\n"<<"Size:" << GetSize()<<"\n" << "Center: " <<"(" <<GetCenter().GetX()<< ","<<GetCenter().GetY()<<")\n" <<"PUB PID:" << GetPubPid()<<"\n" <<std:: endl;
}

#endif  //	ifndef __BOTH_HPP__













