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
		int
	} typeName;

    Type();
    ~Type();
    Type(typeName type);
    void printType(std::ostream &o){
        switch (type)
        {
        case int:
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