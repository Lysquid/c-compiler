#include "Types.h"

Type::Type(const string& name) {
    if (name == "int" || name == "char") this->value = INT;
    if (name == "void") this->value = VOID;
}

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
