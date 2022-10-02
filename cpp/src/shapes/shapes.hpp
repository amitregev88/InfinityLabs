/****************************************************************************/
/*	Project:	Shapes                      							    */
/*	File:		shapes.hpp  												*/
/*	Date: 		29/09/2022													*/
/*	Name: 		Amit Regev													*/
/*	Reviewer:														        */
/****************************************************************************/

#ifndef __ILRD_HRD25_SHAPES_HPP__
#define __ILRD_HRD25_SHAPES_HPP__

#include <iostream> 
#include <cstring> 



#include "utility.hpp"

namespace ilrd 
{

class Shapes
{
public:
    virtual void Draw() = 0;
    virtual void Move(double x, double y) = 0;

protected:

    class Point;
    string GetName();
        
}

class Point
{
public:
    explicit Point(double x_, double y_): m_x(x_), m_y(y_){}
    void SetX(x_):m_x{}
    void SetX(y_):m_y{}
    double GetX(x_):m_x{}
    double GetY(y_):m_y{}

    //CCtor and Dtor are default.

private:

    double m_x;
    double m_y;
    
}


class Line
{

public:
    explicit Line(double x1_, double y1_, double x2_, double y2_): 
                            m_x1(x1_), m_y1(y1_), m_x2(x2_), m_y2(y2_){}  

private:

    m_x1;
    m_y1;
    m_x2;
    m_y2;

    double m_length;
    const char m_name;
}


class Circle
{

public:
    Circle(double radius_, double len_): m_radius(radius_), m_length(len_);
    void SetCenter(double x_, double y_): m_x(x_), m_y(y_){};

private:

    double m_radius;
    double m_length;
    double m_x;
    double m_y;
    const char m_name;

}


class Square
{
public:
    explicit Square(double len_)
    void SetCenter(double x_, double y_)


private:
    double m_l;
    double m_x;
    double m_y;
    const char m_name;


}


Class Rectangle
{

public:
    explicit Rectangle(double width_, double len_)
    void SetCenter(double x_, double y_)

private:

    double m_w;
    double m_l;
    double m_x;
    double m_y;
    const char m_name;


}