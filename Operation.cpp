#include "Operation.h"

Operation::Operation() {
    this->lan = A;
}

void Operation::set_lan(Lan lang) {
    this->lan = lang;
}

//basic mathematical operations
void Operation::add(int &a, int b) const {
    if (this->lan == A) {
        __asm{
                mov esi, a
                mov eax,[esi]
                add eax, b
                mov[esi], eax
        }
    } else a += b;
}

void Operation::sub(int &a, int b) const {
    if (this->lan == A) {
        __asm{
                mov esi, a
                mov eax,[esi]
                sub eax, b
                mov[esi], eax
        }
    } else a -= b;
}

void Operation::mul(int &a, int b) const {
    if (this->lan == A) {
        __asm{
                mov esi, a
                mov eax,[esi]
                mov ebx, b
                imul ebx                     // using imul for signed numbers
                mov[esi], eax
        }
    } else a *= b;
}

double Operation::div(int a, int b) const {
    if (this->lan == A) {
        int i = 0, j = 0;
        __asm{
                mov eax, a
                cdq                          // extension EAX -> EDX:EAX
                mov ebx, b
                idiv ebx                     // using idiv for signed numbers
                mov i, eax                   // edx - remainder
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
void Operation::logical(Type operation, int &a, int b) {
    __asm mov esi, a
    switch (operation) {
        case Not:
            __asm {
                    mov eax,[esi]
                    not eax
            }
            break;
        case And:
            __asm{
                    mov eax,[esi]
                    and eax, b
            }
            break;
        case Or:
            __asm{
                    mov eax,[esi]
                    or eax, b
            }
            break;
        case Xor:
            __asm {
                    mov eax,[esi]
                    xor eax, b
            }
            break;
        default:
            std::cout << "Wrong operation, choose: Not, And, Or, Xor";
    }
    __asm mov[esi], eax
}


//array indexing
int Operation::index(int *mass, int index) const {
    if (this->lan == A) {
        int s = sizeof(mass);
        int c = 0;
        __asm{
                mov eax, s
                mov ecx, index
                mul ecx
                mov ebx, mass
                add ebx, eax
                mov eax,[ebx]
                mov c, eax
        }
        return c;
    }
    return mass[index];
}

// shift operations
void Operation::logical_shift(int &a, int shift) {
    if (shift < 0) {                         // left shift
        int sh = ~shift + 1;
        __asm{
                mov ecx, sh
                mov esi, a
                mov eax,[esi]
                shl eax, cl
                mov[esi], eax
        }
    } else {                                 // right shift
        __asm{
                mov ecx, shift
                mov esi, a
                mov eax,[esi]
                shr eax, cl
                mov[esi], eax
        }
    }
}

void Operation::arithmetic_shift(int &a, int shift) {
    if (shift < 0) {                         // left shift
        int sh = ~shift + 1;
        __asm{
                mov ecx, sh
                mov esi, a
                mov eax,[esi]
                sal eax, cl
                mov[esi], eax
        }
    } else {                                 // right shift
        __asm{
                mov ecx, shift
                mov esi, a
                mov eax,[esi]
                sar eax, cl
                mov[esi], eax
        }
    }
}

void Operation::cyclic_shift(int &a, int shift) {
    if (shift < 0) {                         // left shift
        int sh = ~shift + 1;
        __asm{
                mov ecx, sh
                mov esi, a
                mov eax,[esi]
                rol eax, cl
                mov[esi], eax
        }
    } else {                                 // right shift
        __asm{
                mov ecx, shift
                mov esi, a
                mov eax,[esi]
                ror eax, cl
                mov[esi], eax
        }
    }
}





