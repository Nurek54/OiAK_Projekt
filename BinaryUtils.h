#ifndef BINARY_UTILS_H
#define BINARY_UTILS_H

#include <vector>

class BinaryUtils {
public:
    static std::vector<int> toBinary(int num, int size);
    static int binaryToDecimal(const std::vector<int>& binary);
};

#endif // BINARY_UTILS_H
