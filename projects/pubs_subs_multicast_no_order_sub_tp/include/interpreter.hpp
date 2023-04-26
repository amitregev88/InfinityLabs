/****************************************************************************/
/*	Project:	Interpreter API           		    						*/
/*	File:		interpreter.hpp						    					*/
/*	Date: 		05/01/2023													*/
/*	Name: 		Amit Regev     												*/
/*	Version: 	1.00														*/
/****************************************************************************/

#ifndef __INTERPRETER_HPP__
#define __INTERPRETER_HPP__

#include "shape.hpp"
#include "square.hpp"
#include "circle.hpp"
#include "both.hpp"
#include "utils.hpp"

class Interpreter
{
public:
    explicit Interpreter(){};
    ~Interpreter() noexcept = default;
    Interpreter &operator=(const Interpreter &) = delete;
    Interpreter(const Interpreter &) = delete;

    std::string Serialize(Data_ty dtype_);
    Shape *Deserialize(std::string data_);


    
};

std::string Interpreter::Serialize(Data_ty dtype_)
{
    std::string data;
    std::string x = std::to_string((rand() % 100)) + "\0";
    std::string y = std::to_string((rand() % 100)) + "\0";

    int p = getpid();


    switch (dtype_)
    {
    case SQUARE:

        data = "square!7!" + x + "!" + y + "!" + std::to_string(p);
        return data;
        break;
    case CIRCLE:

        data += "circle!7!" + x + "!" + y + "!" + std::to_string(p);
        return data;
        break;
    case BOTH:
        data += "both!7!" + x + "!" + y + "!" + std::to_string(p);
        return data;
        break;

    default:
        std::cout<<"data type is not exsist to serialize\n";
        return data;
        break;
    }
};


Shape* Interpreter:: Deserialize(std::string data_)
{    
    
    int pos = data_.find("!");
    std::string type = data_.substr(0,pos); //datatype

    std::string size_tmp = data_.substr(pos+1); 

    pos = size_tmp.find("!");

    std::string size_str = size_tmp.substr(0,pos ); 

    double size = std::stod(size_str); //size

    std::string x_tmp = size_tmp.substr(pos + 1); 

    pos = x_tmp.find("!");

    std::string x_str = x_tmp.substr(0, pos); 

    double x = std::stod(x_str); // X center

    std::string y_tmp = x_tmp.substr(pos + 1); 

    pos = y_tmp.find("!");

    std::string y_str = y_tmp.substr(0, pos); 

    double y = std::stod(y_str); // Y center

    pos = y_tmp.find("!");

    std::string pub_pid_str = y_tmp.substr(pos+1);

    int pub_pid = std::stod(pub_pid_str);


    if(type.compare("square") == 0)
    {
        Square *ret = new Square;
        ret->SetCenter(x,y);
        ret->SetSize(size);
        ret->SetPid(pub_pid);
        return ret;
    }
    else if(type.compare("circle") == 0)
    {
        Circle *ret = new Circle;
        ret->SetCenter(x,y);
        ret->SetSize(size);
        ret->SetPid(pub_pid);
        return ret;
    }
    else if(type.compare("both") == 0)
    {
        Both *ret = new Both;
        ret->SetCenter(x,y);
        ret->SetSize(size);
        ret->SetPid(pub_pid);
        return ret;
    }

    else
    {
        std::cout << "data type is not exist" << std::endl;
        return nullptr;
    }



}

#endif //	ifndef __INTERPRETER_HPP__
