#include <iostream>
#include "Booth.h"
#include "BoothRadix4.h"
#include "Modulo.h"
#include "BinaryUtils.h"

int main() {
    int multiplicand, multiplier, n;
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

    std::cout << "Enter n for modulo 2^n - 3: ";
    std::cin >> n;

    // Wynik normalnego Bootha
    std::cout << "\nBooth Algorithm:\n";
    Booth booth(multiplicand, multiplier);
    int boothResult = booth.multiply();
    std::vector<int> boothResultBinary = BinaryUtils::toBinary(boothResult, sizeof(int) * 8);
    std::cout << "Result in binary: ";
    for (int bit : boothResultBinary) {
        std::cout << bit;
    }
    std::cout << "\nProduct: " << boothResult << std::endl;

    // Wynik normalnego Bootha poddany modulo
    Modulo modulo(n);
    int boothResultModulo = modulo.applyModulo(boothResult);
    std::vector<int> boothResultModuloBinary = BinaryUtils::toBinary(boothResultModulo, sizeof(int) * 8);
    std::cout << "\nBooth Algorithm with modulo 2^" << n << " - 3:\n";
    std::cout << "Result in binary: ";
    for (int bit : boothResultModuloBinary) {
        std::cout << bit;
    }
    std::cout << "\nResult in decimal: " << boothResultModulo << std::endl;

    // Wynik algorytmu Booth Radix-4
    std::cout << "\nBooth Radix-4 Algorithm:\n";
    BoothRadix4 boothRadix4(M_bin, Q_bin);
    std::vector<int> radix4Result = boothRadix4.multiply();
    int radix4ResultDecimal = boothRadix4.binaryToDecimal(radix4Result);
    std::vector<int> radix4ResultBinary = BinaryUtils::toBinary(radix4ResultDecimal, sizeof(int) * 8);
    std::cout << "Result in binary: ";
    for (int bit : radix4ResultBinary) {
        std::cout << bit;
    }
    std::cout << "\nResult in decimal: " << radix4ResultDecimal << std::endl;

    // Wynik algorytmu Booth Radix-4 poddany modulo
    int radix4ResultModulo = modulo.applyModulo(radix4ResultDecimal);
    std::vector<int> radix4ResultModuloBinary = BinaryUtils::toBinary(radix4ResultModulo, sizeof(int) * 8);
    std::cout << "\nBooth Radix-4 Algorithm with modulo 2^" << n << " - 3:\n";
    std::cout << "Result in binary: ";
    for (int bit : radix4ResultModuloBinary) {
        std::cout << bit;
    }
    std::cout << "\nResult in decimal: " << radix4ResultModulo << std::endl;

    return 0;
}
