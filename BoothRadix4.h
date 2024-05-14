#ifndef BOOTHRADIX4_H
#define BOOTHRADIX4_H

#include <vector>

class BoothRadix4 {
public:
    BoothRadix4(const std::vector<int>& M, const std::vector<int>& Q);
    std::vector<int> multiply();
    int binaryToDecimal(const std::vector<int>& binary);

private:
    std::vector<int> M;
    std::vector<int> Q;
    std::vector<int> A;
    std::vector<int> M_neg;
    int Q_1;

    std::vector<int> binaryAdd(const std::vector<int>& a, const std::vector<int>& b);
    void arithmeticRightShift();
    std::vector<int> twosComplement(const std::vector<int>& binary);
};

#endif // BOOTHRADIX4_H
