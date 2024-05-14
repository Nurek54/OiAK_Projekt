#include <iostream>
#include "Booth.h"
#include "BoothRadix4.h"
#include "BinaryUtils.h"

int main() {
    int multiplicand, multiplier;
    std::cout << "Enter multiplicand: ";
    std::cin >> multiplicand;
    std::vector<int> M_bin = BinaryUtils::toBinary(multiplicand, sizeof(int) * 8);
    std::cout << "Multiplicand in binary: ";
    for (int bit : M_bin) {
        std::cout << bit;
    }
    std::cout << std::endl;

    std::cout << "Enter multiplier: ";
    std::cin >> multiplier;
    std::vector<int> Q_bin = BinaryUtils::toBinary(multiplier, sizeof(int) * 8);
    std::cout << "Multiplier in binary: ";
    for (int bit : Q_bin) {
        std::cout << bit;
    }
    std::cout << std::endl;

    std::cout << "\nBooth Algorithm:\n";
    Booth booth(multiplicand, multiplier);
    int boothResult = booth.multiply();
    std::vector<int> boothResultBinary = BinaryUtils::toBinary(boothResult, sizeof(int) * 8);
    std::cout << "Result in binary: ";
    for (int bit : boothResultBinary) {
        std::cout << bit;
    }
    std::cout << "\nProduct: " << boothResult << std::endl;

    std::cout << "\nBooth Radix-4 Algorithm:\n";
    BoothRadix4 boothRadix4(M_bin, Q_bin);
    std::vector<int> radix4Result = boothRadix4.multiply();

    std::cout << "Result in binary: ";
    for (int bit : radix4Result) {
        std::cout << bit;
    }
    std::cout << "\nResult in decimal: ";
    int radix4ResultDecimal = boothRadix4.binaryToDecimal(radix4Result);
    std::cout << radix4ResultDecimal << std::endl;

    return 0;
}
