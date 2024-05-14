#include "BinaryUtils.h"

std::vector<int> BinaryUtils::toBinary(int num, int size) {
    std::vector<int> bin(size, 0);
    for (int i = 0; i < size; i++) {
        bin[size - 1 - i] = (num >> i) & 1;
    }
    return bin;
}

int BinaryUtils::binaryToDecimal(const std::vector<int>& binary) {
    int result = 0;
    int n = binary.size();
    bool isNegative = binary[0] == 1;

    for (int i = 0; i < n; i++) {
        result = (result << 1) | binary[i];
    }

    if (isNegative) {
        result -= (1 << n);
    }

    return result;
}
