/****************************************************************************/
/*	Project:	Circle API           		    							*/
/*	File:		circle.hpp						    						*/
/*	Date: 		05/01/2023													*/
/*	Name: 		Amit Regev     												*/
/*	Version: 	1.00														*/
/****************************************************************************/

#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include "shape.hpp"


class Circle : public Shape
{

public:

    explicit Circle(double size_ = 0, double x_center_ = 0, double y_center_  = 0) : Shape(GREEN, size_, x_center_, y_center_){}; 
    ~Circle() noexcept = default;
    Circle& operator=(const Circle& o_) = default;
    Circle(const Circle& o_) = default; 

    void Print();

};

void Circle:: Print()
{
    std::cout << "Circle Data\n\n" << "Color: " << GetColor()<<"\n"<<"Radius:" << GetSize()<<"\n" << "Center: " <<"(" <<GetCenter().GetX()<< ","<<GetCenter().GetY()<<")\n" <<std:: endl;
}


#endif  //	ifndef __CIRCLE_HPP__













