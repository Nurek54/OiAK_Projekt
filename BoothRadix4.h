#ifndef BOOTH_RADIX4_H
#define BOOTH_RADIX4_H

#include <vector>

class BoothRadix4 {
public:
    BoothRadix4(int M, int Q);
    int multiply();

private:
    std::vector<int> addBinary(const std::vector<int>& a, const std::vector<int>& b);
    std::vector<int> negateBinary(const std::vector<int>& a);
    void arithmeticRightShift(std::vector<int>& A, std::vector<int>& Q, int k);
    int decodeRadix4(int y2i1, int y2i, int y2im1);

    int M;
    int Q;
    int n;
    std::vector<int> M_bin;
    std::vector<int> Q_bin;
    std::vector<int> A;
    std::vector<int> M_neg;
};

#endif // BOOTH_RADIX4_H
