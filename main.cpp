#include <iostream>
#include "Booth.h"
#include "BoothRadix4.h"
#include "Modulo.h"
#include "BinaryUtils.h"

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

    // Wynik normalnego Bootha
    std::cout << "\nAlgorytm Bootha:\n";
    Booth booth(liczba1, liczba2);
    int boothResult = booth.multiply();
    std::vector<int> boothResultBinary = BinaryUtils::toBinary(boothResult, sizeof(int) * 8);
    std::cout << "Wynik w binarnym: ";
    for (int bit : boothResultBinary) {
        std::cout << bit;
    }
    std::cout << "\nProdukt: " << boothResult << std::endl;

    // Wynik normalnego Bootha poddany modulo
    Modulo modulo(n);
    int boothResultModulo = modulo.applyModulo(boothResult);
    std::vector<int> boothResultModuloBinary = BinaryUtils::toBinary(boothResultModulo, sizeof(int) * 8);
    std::cout << "\nAlgorytm Bootha z modulo 2^" << n << " - 3:\n";
    std::cout << "Wynik w binarnym: ";
    for (int bit : boothResultModuloBinary) {
        std::cout << bit;
    }
    std::cout << "\nWynik w dziesietnym: " << boothResultModulo << std::endl;

    // Wynik algorytmu Booth Radix-4
    std::cout << "\nAlgorytm Booth Radix-4:\n";
    BoothRadix4 boothRadix4(M_bin, Q_bin);
    std::vector<int> radix4Result = boothRadix4.multiply();
    int radix4ResultDecimal = boothRadix4.binaryToDecimal(radix4Result);
    std::vector<int> radix4ResultBinary = BinaryUtils::toBinary(radix4ResultDecimal, sizeof(int) * 8);
    std::cout << "Wynik w binarnym: ";
    for (int bit : radix4ResultBinary) {
        std::cout << bit;
    }
    std::cout << "\nWynik w dziesietnym: " << radix4ResultDecimal << std::endl;

    // Wynik algorytmu Booth Radix-4 poddany modulo
    int radix4ResultModulo = modulo.applyModulo(radix4ResultDecimal);
    std::vector<int> radix4ResultModuloBinary = BinaryUtils::toBinary(radix4ResultModulo, sizeof(int) * 8);
    std::cout << "\nAlgorytm Booth Radix-4 z modulo 2^" << n << " - 3:\n";
    std::cout << "Wynik w binarnym: ";
    for (int bit : radix4ResultModuloBinary) {
        std::cout << bit;
    }
    std::cout << "\nWynik w dziesietnym: " << radix4ResultModulo << std::endl;

    return 0;

}
