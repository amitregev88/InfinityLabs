/****************************************************************************/
/*	Project:	Shapes API           		    							*/
/*	File:		shapes.hpp						    						*/
/*	Date: 		05/01/2023													*/
/*	Name: 		Amit Regev     												*/
/*	Version: 	1.00														*/
/****************************************************************************/

#ifndef __SHAPES_HPP__
#define __SHAPES_HPP__

#include <iostream> 
#include "point.hpp"


class Shape
{
public:
    enum Color_ty {NO_COLOR, BLUE, GREEN};
    explicit Shape(Color_ty color_ = NO_COLOR, double size_ = 0, double  x_center_ = 0 , double  y_center_ = 0) : m_color(color_), m_size(size_), m_center(x_center_, y_center_){};
    virtual ~Shape(){};
    virtual void Print() = 0;

    double GetSize() const;
    Point GetCenter() const;
    std::string GetColor() const; 
    int GetPubPid() const;

    void SetSize(double size);
    void SetCenter(double x , double y);
    void SetPid(int pub_pid_);


private:
    Color_ty m_color;
    double m_size;
    Point m_center;
    int m_pub_pid;
};


double Shape::GetSize() const
{
    return m_size;
}

Point Shape::GetCenter() const
{
    return m_center;
}

std::string Shape:: GetColor() const
{
    std::string color;

    switch (m_color)
    {
    case BLUE:
        
        color = "Blue";
        return color;
        break;

    case GREEN:
        color = "Green";
        return color;
    
    default:
        color = "Invalid color";
        return color;
        break;
    } 
}

int Shape:: GetPubPid() const
{
    return m_pub_pid;

}

void Shape:: SetSize(double size)
{
    m_size = size;

}

void Shape::SetCenter(double x , double y)
{
    m_center.SetX(x);
    m_center.SetY(y);
    
}

void Shape::SetPid(int pub_pid_)
{
    m_pub_pid = pub_pid_;
}




#endif //__SHAPES_HPP__#endif