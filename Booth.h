#ifndef BOOTH_H
#define BOOTH_H

#include <vector>
#include "BinaryUtils.h"

class Booth {
public:
    Booth(int M, int Q);
    int multiply();

private:
    std::vector<int> addBinary(const std::vector<int>& a, const std::vector<int>& b);
    std::vector<int> negateBinary(const std::vector<int>& a);
    void rightShift(std::vector<int>& A, std::vector<int>& Q, int& Q_1);

    int M;
    int Q;
    int n;
    std::vector<int> A;
    std::vector<int> M_bin;
    std::vector<int> Q_bin;
    std::vector<int> M_neg;
    int Q_1;
};

#endif // BOOTH_H
