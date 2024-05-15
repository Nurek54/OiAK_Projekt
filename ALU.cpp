#include "ALU.h"

std::vector<int> ALU::execute(const std::vector<int>& in1, const std::vector<int>& in2, int ALU_op) {
    std::vector<int> result;
    switch (ALU_op) {
        case 0: // ADD
            result = add(in1, in2);
            break;
        case 1: // SUBTRACT
            result = subtract(in1, in2);
            break;
        case 2: // ADD and SHIFT LEFT
            result = add(in1, shiftLeftTwice(in2));
            break;
        case 3: // SUBTRACT and SHIFT LEFT
            result = subtract(in1, shiftLeftTwice(in2));
            break;
    }
    return result;
}

std::vector<int> ALU::add(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result(a.size(), 0);
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        int sum = a[i] + b[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }
    return result;
}

std::vector<int> ALU::subtract(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> neg_b = b;
    for (int i = 0; i < b.size(); i++) {
        neg_b[i] = b[i] == 0 ? 1 : 0;
    }
    std::vector<int> one(b.size(), 0);
    one.back() = 1;
    neg_b = add(neg_b, one);
    return add(a, neg_b);
}

std::vector<int> ALU::shiftLeft(const std::vector<int>& a) {
    std::vector<int> result(a.size(), 0);
    for (int i = 0; i < a.size() - 1; i++) {
        result[i] = a[i + 1];
    }
    return result;
}

std::vector<int> ALU::shiftLeftTwice(const std::vector<int>& a) {
    std::vector<int> result(a.size(), 0);
    for (int i = 0; i < a.size() - 2; i++) {
        result[i] = a[i + 2];
    }
    return result;
}
