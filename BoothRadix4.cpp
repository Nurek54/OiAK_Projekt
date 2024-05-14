#include "BoothRadix4.h"
#include "BinaryUtils.h"

BoothRadix4::BoothRadix4(const std::vector<int>& M, const std::vector<int>& Q)
        : M(M), Q(Q), Q_1(0) {
    A.resize(Q.size(), 0);
    M_neg = twosComplement(M);
}

std::vector<int> BoothRadix4::binaryAdd(const std::vector<int>& a, const std::vector<int>& b) {
    int carry = 0;
    std::vector<int> result(a.size(), 0);

    for (int i = a.size() - 1; i >= 0; --i) {
        int sum = a[i] + b[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }

    return result;
}

void BoothRadix4::arithmeticRightShift() {
    int signBit = A[0];
    Q_1 = Q.back();
    Q.pop_back();
    Q.insert(Q.begin(), A.back());
    A.pop_back();
    A.insert(A.begin(), signBit); // Maintain the sign bit
}

std::vector<int> BoothRadix4::twosComplement(const std::vector<int>& binary) {
    std::vector<int> result(binary.size(), 0);
    int carry = 1;

    for (int i = binary.size() - 1; i >= 0; --i) {
        result[i] = binary[i] ? 0 : 1;
    }

    for (int i = binary.size() - 1; i >= 0; --i) {
        result[i] += carry;
        if (result[i] == 2) {
            result[i] = 0;
            carry = 1;
        } else {
            carry = 0;
        }
    }

    return result;
}

std::vector<int> BoothRadix4::multiply() {
    int n = Q.size();

    for (int i = 0; i < n / 2; ++i) {
        int Q0_Q1 = Q[Q.size() - 1] + 2 * Q_1;

        if (Q0_Q1 == 1 || Q0_Q1 == -2) {
            A = binaryAdd(A, M_neg);
        } else if (Q0_Q1 == 2 || Q0_Q1 == -1) {
            A = binaryAdd(A, M);
        }

        arithmeticRightShift();
        arithmeticRightShift(); // Perform two right shifts
    }

    std::vector<int> result;
    result.insert(result.end(), A.begin(), A.end());
    result.insert(result.end(), Q.begin(), Q.end());

    return result;
}

int BoothRadix4::binaryToDecimal(const std::vector<int>& binary) {
    int result = 0;
    int n = binary.size();

    // Sprawdzamy, czy liczba jest ujemna
    bool isNegative = binary[0] == 1;

    // Jeżeli liczba jest ujemna, obliczamy jej wartość w formacie binarnym
    if (isNegative) {
        // Konwersja binarna uzupełnienia do dwóch
        std::vector<int> complement = twosComplement(binary);
        for (int i = 0; i < n; i++) {
            result = (result << 1) | complement[i];
        }
        result = -result;
    } else {
        for (int i = 0; i < n; i++) {
            result = (result << 1) | binary[i];
        }
    }

    return result;
}
