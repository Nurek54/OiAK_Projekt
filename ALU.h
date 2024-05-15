#ifndef ALU_H
#define ALU_H

#include <vector>

class ALU {
public:
    static std::vector<int> execute(const std::vector<int>& in1, const std::vector<int>& in2, int ALU_op);

private:
    static std::vector<int> add(const std::vector<int>& a, const std::vector<int>& b);
    static std::vector<int> subtract(const std::vector<int>& a, const std::vector<int>& b);
    static std::vector<int> shiftLeft(const std::vector<int>& a);
    static std::vector<int> shiftLeftTwice(const std::vector<int>& a);
};

#endif // ALU_H
