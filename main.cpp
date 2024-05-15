#include <iostream>
#include "DataPath.h"
#include "ControlPath.h"
#include "BinaryUtils.h"
#include "Modulo.h"  // Upewnij się, że klasa Modulo jest zaimportowana

int main() {
    int liczba1, liczba2, n;
    std::cout << "Podaj liczbe 1: ";
    std::cin >> liczba1;
    std::vector<int> M_bin = BinaryUtils::toBinary(liczba1, sizeof(int) * 8);
    std::cout << "Liczba 1 w binarnym: ";
    for (int bit : M_bin) {
        std::cout << bit;
    }
    std::cout << std::endl;

    std::cout << "Podaj liczbe 2: ";
    std::cin >> liczba2;
    std::vector<int> Q_bin = BinaryUtils::toBinary(liczba2, sizeof(int) * 8);
    std::cout << "Liczba 2 w binarnym: ";
    for (int bit : Q_bin) {
        std::cout << bit;
    }
    std::cout << std::endl;

    std::cout << "Podaj n dla modulo 2^n - 3: ";
    std::cin >> n;

    // Booth Radix-4
    DataPath dp(sizeof(int) * 8);
    ControlPath cp;
    dp.setInput(liczba1, liczba2);

    bool start = true;
    while (!cp.done) {
        cp.updateState(start, dp.checkZero(), dp.Q_1, dp.Q_0, dp.Qm_1);
        dp.update(cp.ALU_op, cp.ldA, cp.shiftA, cp.clrA, cp.ldQ, cp.shiftQ, cp.clrQ, cp.ldM, cp.clrM);
        start = false; // Upewnij się, że start jest ustawiony tylko raz na początku
    }

    int radix4Result = BinaryUtils::binaryToDecimal(dp.A) + BinaryUtils::binaryToDecimal(dp.Q);
    std::vector<int> radix4ResultBinary = BinaryUtils::toBinary(radix4Result, sizeof(int) * 8);
    std::cout << "\nAlgorytm Booth Radix-4:\n";
    std::cout << "Wynik w binarnym: ";
    for (int bit : radix4ResultBinary) {
        std::cout << bit;
    }
    std::cout << "\nWynik w dziesietnym: " << radix4Result << std::endl;

    // Wynik algorytmu Booth Radix-4 poddany modulo
    Modulo modulo(n);
    int radix4ResultModulo = modulo.applyModulo(radix4Result);
    std::vector<int> radix4ResultModuloBinary = BinaryUtils::toBinary(radix4ResultModulo, sizeof(int) * 8);
    std::cout << "\nAlgorytm Booth Radix-4 z modulo 2^" << n << " - 3:\n";
    std::cout << "Wynik w binarnym: ";
    for (int bit : radix4ResultModuloBinary) {
        std::cout << bit;
    }
    std::cout << "\nWynik w dziesietnym: " << radix4ResultModulo << std::endl;

    return 0;
}
