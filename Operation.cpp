#include "Operation.h"

Operation::Operation() {
    this->lan = A;
}

void Operation::set_lan(Lan lang) {
    this->lan = lang;
}

//basic mathematical operations
int Operation::add(int a, int b) const {
    if (this->lan == A) {
        int c = 0;
        __asm{
                mov eax, a
                add eax, b
                mov c, eax
        }
        return c;
    }
    return a + b;
}

int Operation::sub(int a, int b) const {
    if (this->lan == A) {
        int c = 0;
        __asm{
                mov eax, a
                sub eax, b
                mov c, eax
        }
        return c;
    }
    return a - b;
}

int Operation::mul(int a, int b) const {
    if (this->lan == A) {
        int c = 0;
        __asm{
                mov eax, a
                mov ebx, b
                imul ebx   // using imul for signed numbers
                mov c, eax
        }
        return c;
    }
    return a * b;
}

double Operation::div(int a, int b) const {
    if (this->lan == A) {
        int i = 0, j = 0;
        __asm{
                mov eax, a
                cdq         // extension EAX -> EDX:EAX
                mov ebx, b
                idiv ebx    // using idiv for signed numbers
                mov i, eax  // edx - remainder
                mov j, edx
        }
        return (j / (b * 0.1)) * 0.1 + i;
    }
    return ((a % b) / (b * 0.1)) * 0.1 + a / b;
}

//comparison operations
bool Operation::_greater(int a, int b) const {
    if (this->lan == A) {
        int c = 0;
        __asm{
                mov   eax, a
                cmp   eax, b
                mov   eax, 1
                jg L
                mov   eax, 0
                L: mov   c, eax
        }
        return c;
    }
    return a > b;
}

bool Operation::_less(int a, int b) const {
    if (this->lan == A) {
        int c = 0;
        __asm{
                mov   eax, a
                cmp   eax, b
                mov   eax, 1
                jl L
                mov   eax, 0
                L: mov   c, eax
        }
        return c;
    }
    return a < b;
}

bool Operation::_equal(int a, int b) const {
    if (this->lan == A) {
        int c = 0;
        __asm{
                mov   eax, a
                cmp   eax, b
                mov   eax, 1
                je L
                mov   eax, 0
                L: mov   c, eax
        }
        return c;
    }
    return a == b;
}

bool Operation::_not_equal(int a, int b) const {
    if (this->lan == A) {
        int c = 0;
        __asm{
                mov   eax, a
                cmp   eax, b
                mov   eax, 1
                jne L
                mov   eax, 0
                L: mov   c, eax
        }
        return c;
    }
    return a != b;
}

bool Operation::_greater_equal(int a, int b) const {
    if (this->lan == A) {
        int c = 0;
        __asm{
                mov   eax, a
                cmp   eax, b
                mov   eax, 1
                jge L
                mov   eax, 0
                L: mov   c, eax
        }
        return c;
    }
    return a >= b;
}

bool Operation::_less_equal(int a, int b) const {
    if (this->lan == A) {
        int c = 0;
        __asm{
                mov   eax, a
                cmp   eax, b
                mov   eax, 1
                jle L
                mov   eax, 0
                L: mov   c, eax
        }
        return c;
    }
    return a <= b;
}

bool Operation::comparison(int a, int b, std::string operation) {
    int ascii = 0;
    for (int i = 0; i <= operation.length(); ++i) ascii += (int) operation[i];
    switch (ascii) {
        case (int) '=':
            return this->_equal(a, b);
        case (int) '>':
            return this->_greater(a, b);
        case (int) '<':
            return this->_less(a, b);
        case (int) '!' + '=':
            return this->_not_equal(a, b);
        case (int) '>' + '=':
            return this->_greater_equal(a, b);
        case (int) '<' + '=':
            return this->_less_equal(a, b);
        default:
            std::cout << "Wrong operation, choose: =, >, <, !=, >=, <=";
    }
}

//logical operations
int Operation::logical(Type operation, int a, int b) {
    int c = 0;
    switch (operation) {
        case Not:
            __asm {
                    mov eax, a
                    not eax
            }
            break;
        case And:
            __asm{
                    mov eax, a
                    and eax, b
            }
            break;
        case Or:
            __asm{
                    mov eax, a
                    or eax, b
            }
            break;
        case Xor:
            __asm {
                    mov eax, a
                    xor eax, b
            }
            break;
        default:
            std::cout << "Wrong operation, choose: Not, And, Or, Xor";
    }
    __asm mov c, eax
    return c;
}

//array indexing
int Operation::index(int *mass, int index) {
    std::cout << mass;
    return 0;
}








