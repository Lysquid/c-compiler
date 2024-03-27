#pragma once

#include "string"

using namespace std;

class Type {
public:
    enum {
        VOID,
        INT,
    };

    Type() : value(0) {}

    Type(const string& name);

    Type(int value): value(value) {}

    operator int() const { return this->value; };

    friend ostream& operator<<(ostream& os, const Type& type);

private:
    int value;
};
