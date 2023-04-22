#ifndef SYSTEMPROGRAMMING__LAB1_OPERATION_H
#define SYSTEMPROGRAMMING__LAB1_OPERATION_H

#include <iostream>
#include <string>

enum Type {
    Not = 1,
    And,
    Or,
    Xor
};
enum Lan {
    A = 0,
    C = 1
};

class Operation {
private:
//comparison operations
    bool _equal(int a, int b) const;
    bool _not_equal(int a, int b) const;
    bool _greater(int a, int b) const;
    bool _greater_equal(int a, int b) const;
    bool _less(int a, int b) const;
    bool _less_equal(int a, int b) const;

public:
    Lan lan;
    explicit Operation();
    void set_lan(Lan lang);

//basic mathematical operations
    void add(int &a, int b) const;
    void sub(int &a, int b) const;
    void mul(int &a, int b) const;
    double div(int a, int b) const;

//comparison start point
    bool comparison(int a, int b, std::string operation);

//logical operations
    static void logical(Type operation, int &a, int b = 0);

//array indexing
    int index(int *mass, int index) const;

// shift operations
    static void logical_shift(int &a, int shift = -1);
    static void arithmetic_shift(int &a, int shift = -1);
    static void cyclic_shift(int &a, int shift = -1);
};

#endif //SYSTEMPROGRAMMING__LAB1_OPERATION_H
