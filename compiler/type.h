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

    Type();
    ~Type();
    Type(typeName type);
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

private:
    int type;
};


#endif