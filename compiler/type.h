#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <vector>
#include <iostream>

class Type
{

public: 
    typedef enum
	{
		TYPE_INT
	} typeName;

    Type(typeName type){
        this->type = type;
    };

    void printType(std::ostream &o){
        switch (type)
        {
        case TYPE_INT:
            o << "int";
            break;
        
        default:
            break;
        }
    };

    std::string getType(){
        switch (type)
        {
        case TYPE_INT:
            return "int";
            break;
        
        default:
            return "";
            break;
        }
    }

private:
    typeName type;
};


#endif