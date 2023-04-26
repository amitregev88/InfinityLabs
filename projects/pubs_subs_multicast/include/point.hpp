/****************************************************************************/
/*	Project:	Point API           		    							*/
/*	File:		point.hpp						    						*/
/*	Date: 		05/01/2023													*/
/*	Name: 		Amit Regev     												*/
/*	Version: 	1.00														*/
/****************************************************************************/

#ifndef __POINT_HPP__
#define __POINT_HPP__

class Point
{	
public:

    explicit Point(double x_, double y_);
    ~Point() = default;
    Point& operator=(const Point&) = delete; 
    //Point(const Point&); 


    double GetX();
    double GetY();
    void SetX(double);
    void SetY(double);
	
private:
    double m_x;
    double m_y;
};


Point::Point(double x_, double y_):m_x(x_), m_y(y_)
{};

double Point::GetX()
{
    return m_x;
}

double Point::GetY()
{
    return m_y;
}

void Point::SetX(double x_)
{
     m_x = x_;
}

void Point::SetY(double y_)
{
     m_y = y_;
}



#endif  //	ifndef __POINT_HPP__