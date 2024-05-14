#include "Modulo.h"

Modulo::Modulo(int n) {
    modValue = (1 << n) - 3;
}

int Modulo::applyModulo(int value) {
    int result = value % modValue;
    if (result < 0) {
        result += modValue;
    }
    return result;
}
