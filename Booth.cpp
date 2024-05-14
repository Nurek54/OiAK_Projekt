#include "Booth.h"
#include <vector>
#include <iostream>

Booth::Booth(int M, int Q) : M(M), Q(Q) {
    n = sizeof(int) * 8;  // Zakładamy 32-bitowe liczby całkowite
    A.resize(n, 0);
    M_bin = BinaryUtils::toBinary(M, n);
    Q_bin = BinaryUtils::toBinary(Q, n);
    M_neg = negateBinary(M_bin);
    Q_1 = 0;
}

std::vector<int> Booth::addBinary(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result(a.size(), 0);
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        int sum = a[i] + b[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }
    return result;
}

std::vector<int> Booth::negateBinary(const std::vector<int>& a) {
    std::vector<int> result(a.size(), 0);
    std::vector<int> one(a.size(), 0);
    one[a.size() - 1] = 1;
    for (int i = 0; i < a.size(); i++) {
        result[i] = a[i] == 0 ? 1 : 0;
    }
    result = addBinary(result, one);
    return result;
}

void Booth::rightShift(std::vector<int>& A, std::vector<int>& Q, int& Q_1) {
    Q_1 = Q[Q.size() - 1];
    for (int i = Q.size() - 1; i > 0; i--) {
        Q[i] = Q[i - 1];
    }
    Q[0] = A[A.size() - 1];
    for (int i = A.size() - 1; i > 0; i--) {
        A[i] = A[i - 1];
    }
}

int Booth::multiply() {
    for (int i = 0; i < n; i++) {
        if (Q_bin[n - 1] == 1 && Q_1 == 0) {
            A = addBinary(A, M_neg);
        } else if (Q_bin[n - 1] == 0 && Q_1 == 1) {
            A = addBinary(A, M_bin);
        }
        rightShift(A, Q_bin, Q_1);
    }

    // Konwersja wyniku z postaci binarnej na liczbę całkowitą
    int result = 0;
    for (int i = 0; i < n; i++) {
        result += Q_bin[i] << (n - 1 - i);
    }

    return result;
}
