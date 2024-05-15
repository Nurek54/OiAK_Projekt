#include "BoothRadix4.h"
#include "BinaryUtils.h"

BoothRadix4::BoothRadix4(int M, int Q) : M(M), Q(Q) {
    n = sizeof(int) * 8;
    A.resize(n, 0);
    M_bin = BinaryUtils::toBinary(M, n);
    Q_bin = BinaryUtils::toBinary(Q, n);
    M_neg = negateBinary(M_bin);
}

std::vector<int> BoothRadix4::addBinary(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result(a.size(), 0);
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        int sum = a[i] + b[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }
    return result;
}

std::vector<int> BoothRadix4::negateBinary(const std::vector<int>& a) {
    std::vector<int> result(a.size(), 0);
    std::vector<int> one(a.size(), 0);
    one[a.size() - 1] = 1;
    for (int i = 0; i < a.size(); i++) {
        result[i] = a[i] == 0 ? 1 : 0;
    }
    result = addBinary(result, one);
    return result;
}

void BoothRadix4::arithmeticRightShift(std::vector<int>& A, std::vector<int>& Q, int k) {
    while (k > 0) {
        bool msb_A = A[0];
        bool msb_Q = Q[0];
        Q.pop_back();
        Q.insert(Q.begin(), A.back());
        A.pop_back();
        A.insert(A.begin(), msb_A);
        k--;
    }
}

int BoothRadix4::decodeRadix4(int y2i1, int y2i, int y2im1) {
    int value = (y2i1 << 2) | (y2i << 1) | y2im1;
    switch (value) {
        case 0: return 0;
        case 1: return 1;
        case 2: return 1;
        case 3: return 2;
        case 4: return -2;
        case 5: return -1;
        case 6: return -1;
        case 7: return 0;
        default: return 0;
    }
}

int BoothRadix4::multiply() {
    int m = (n + 1) / 2;
    std::vector<int> Q_ext = Q_bin;
    Q_ext.insert(Q_ext.begin(), 0); // Dodanie zera do LSB

    for (int i = 0; i < m; i++) {
        int y2i1 = Q_ext[2 * i + 2];
        int y2i = Q_ext[2 * i + 1];
        int y2im1 = Q_ext[2 * i];
        int action = decodeRadix4(y2i1, y2i, y2im1);

        if (action == 1) {
            A = addBinary(A, M_bin);
        } else if (action == -1) {
            A = addBinary(A, M_neg);
        } else if (action == 2) {
            std::vector<int> M2 = addBinary(M_bin, M_bin);
            A = addBinary(A, M2);
        } else if (action == -2) {
            std::vector<int> M2_neg = addBinary(M_neg, M_neg);
            A = addBinary(A, M2_neg);
        }
        arithmeticRightShift(A, Q_ext, 2);
    }

    // Konwersja wyniku z postaci binarnej na liczbę całkowitą
    int result = 0;
    for (int i = 0; i < n; i++) {
        result += Q_ext[i] << (n - 1 - i);
    }

    return result;
}
