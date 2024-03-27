#include "Types.h"

ostream& operator<<(ostream& os, const Type& type)
{
    switch (type) {
        case (Type::VOID):
            os << string("void");
            break;
        case (Type::INT):
            os << string("int");
            break;
    }
    return os;
}
