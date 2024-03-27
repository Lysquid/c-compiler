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

    Type(const string& name) {
        if (name == "int" || name == "char") this->value = INT;
        if (name == "void") this->value = VOID;
    }

    Type(int value) {
        this->value = value;
    }

    operator int() const {
        return this->value;
    };

    friend ostream& operator<<(ostream& os, const Type& type);

private:
    int value;
};
