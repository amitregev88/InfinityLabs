/****************************************************************************/
/*	Project:	Square API           		    							*/
/*	File:		square.hpp						    						*/
/*	Date: 		05/01/2023													*/
/*	Name: 		Amit Regev     												*/
/*	Version: 	1.00														*/
/****************************************************************************/
#ifndef __SQUARE_HPP__
#define __SQUARE_HPP__

#include "shape.hpp"


class Square : public Shape
{

public:
    
    explicit Square(double size_ = 0, double x_center_ = 0, double y_center_  = 0) : Shape(BLUE, size_, x_center_, y_center_){}; 
    ~Square() noexcept = default; 
    Square& operator=(const Square& o_) = default;
    Square(const Square& o_) = default; 

    void Print();     

};

void Square:: Print()
{
    std::cout << "Square Data\n\n" << "Color: " << GetColor()<<"\n"<<"Length:" << GetSize()<<"\n" << "Center: " <<"(" <<GetCenter().GetX()<< ","<<GetCenter().GetY()<<")\n" <<std:: endl;
}

#endif  //	ifndef __SQUARE_HPP__













