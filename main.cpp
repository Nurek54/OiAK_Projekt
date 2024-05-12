#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Dodaje dwie liczby binarne
void dodaj(vector<int> &a, const vector<int> &b) {
    int carry = 0;
    for (size_t i = 0; i < a.size(); i++) {
        int sum = a[i] + b[i] + carry;
        a[i] = sum % 2;
        carry = sum / 2;
    }
}

// Dopełnienie do dwóch
void uzupelnienieDoDwoch(vector<int> &num) {
    vector<int> jeden(num.size(), 0);
    jeden[0] = 1;
    for (int &bit : num) {
        bit = (bit + 1) % 2;
    }
    dodaj(num, jeden);
}

// Przesunięcie w prawo o jeden bit (dla zwykłego Bootha)
void przesunWPrawo(vector<int> &ac, vector<int> &qr, int &qn) {
    int temp = ac[0];
    qn = qr[0];
    for (size_t i = 0; i < ac.size() - 1; i++) {
        ac[i] = ac[i + 1];
        qr[i] = qr[i + 1];
    }
    qr[qr.size() - 1] = temp;
}

// Algorytm Bootha (standardowy)
void booth(const vector<int> &br, vector<int> &ac, vector<int> &qr, int &qn, int licznik) {
    vector<int> mt = br;
    uzupelnienieDoDwoch(mt);

    while (licznik != 0) {
        int qBits = (qn << 1) + qr[0];
        if (qBits == 0b01) {
            dodaj(ac, br);
        } else if (qBits == 0b10) {
            dodaj(ac, mt);
        }
        przesunWPrawo(ac, qr, qn);
        licznik--;
    }
}

void boothRadix4(vector<int> &br, vector<int> &ac, vector<int> &qr, int &qn, int licznik) {
    while (licznik > 0) {
        int qBits = (qn << 1) + qr[0];
        if (qBits == 0b01) {
            dodaj(ac, br);
        } else if (qBits == 0b10) {
            uzupelnienieDoDwoch(br);
            dodaj(ac, br);
            uzupelnienieDoDwoch(br);
        }
        przesunWPrawo(ac, qr, qn);
        licznik--;
    }
}

// Wczytaj dane
void wczytajDane(vector<int> &br, vector<int> &qr, vector<int> &ac, int &brn, int &qrn, int &qn, int &qn_1, int &licznik) {
    cout << "\nPodaj liczbe bitow mnoznika: ";
    cin >> brn;
    br.resize(brn);
    ac.resize(brn, 0);
    cout << "\nWprowadz mnoznik w postaci binarnej: ";
    for (int i = brn - 1; i >= 0; i--)
        cin >> br[i];
    uzupelnienieDoDwoch(br);

    cout << "\nPodaj liczbe bitow mnoznika: ";
    cin >> qrn;
    qr.resize(qrn);
    cout << "\nWprowadz mnoznik w postaci binarnej: ";
    for (int i = qrn - 1; i >= 0; i--)
        cin >> qr[i];

    qn = 0;
    qn_1 = 0;
    licznik = qrn + (qrn % 2 == 0 ? 0 : 1); // Parzysta liczba iteracji
}

// Wyświetla wynik
void wyswietlWynik(const vector<int> &ac, const vector<int> &qr) {
    for (auto it = ac.rbegin(); it != ac.rend(); ++it)
        cout << *it;
    cout << " ";
    for (auto it = qr.rbegin(); it != qr.rend(); ++it)
        cout << *it;
    cout << endl;
}

// Funkcja modulo multiply
void moduloMultiply(vector<int> &ac, vector<int> &qr, int n) {
    long long m = pow(2, n) - 3;
    long long wynik = 0;
    long long podstawa = 1;

    // Konwersja binarnego wyniku do liczby
    for (int i = 0; i < qr.size(); i++) {
        if (qr[i] == 1) {
            wynik += podstawa;
        }
        podstawa *= 2;
    }

    // Dodaj AC do wyniku
    podstawa = pow(2, qr.size());
    for (int i = 0; i < ac.size(); i++) {
        if (ac[i] == 1) {
            wynik += podstawa;
        }
        podstawa *= 2;
    }

    // Wykonaj modulo
    wynik %= m;

    // Zamień z powrotem na wektor binarny
    for (int i = 0; i < qr.size(); i++) {
        qr[i] = wynik % 2;
        wynik /= 2;
    }
    for (int i = 0; i < ac.size(); i++) {
        ac[i] = wynik % 2;
        wynik /= 2;
    }
}

int main() {
    vector<int> br, qr, ac;
    vector<int> oryginalnyQr, oryginalnyAc;
    int brn, qrn, qn = 0, qn_1 = 0, wybor, licznik, n;
    bool kontynuowac = true;
    bool uzyjTychSamychDanych = false;

    while (kontynuowac) {
        if (!uzyjTychSamychDanych) {
            wczytajDane(br, qr, ac, brn, qrn, qn, qn_1, licznik);
            oryginalnyQr = qr;
            oryginalnyAc = vector<int>(brn, 0);
        } else {
            qr = oryginalnyQr;
            ac = vector<int>(brn, 0);
            qn = 0;
            qn_1 = 0;
            licznik = qrn + (qrn % 2 == 0 ? 0 : 1);
        }

        cout << "\nPodaj wartosc n do mnozenia modulo 2^n - 3: ";
        cin >> n;

        cout << "\nWybierz algorytm:\n1 - Zwykly Booth\n2 - Booth-Radix 4\n3 - Zakoncz program\nTwoj wybor: ";
        cin >> wybor;

        switch (wybor) {
            case 1:
                booth(br, ac, qr, qn, licznik);
                moduloMultiply(ac, qr, n);
                cout << "\nWynik: ";
                wyswietlWynik(ac, qr);
                break;
            case 2:
                boothRadix4(br, ac, qr, qn, licznik);
                moduloMultiply(ac, qr, n);
                cout << "\nWynik: ";
                wyswietlWynik(ac, qr);
                break;
            case 3:
                kontynuowac = false;
                continue;
            default:
                cout << "Nieznany wybor, sprobuj ponownie.\n";
                continue;
        }

        int ponownie;
        cout << "\nCzy chcesz wybrac inny algorytm na tych samych danych? (1 - Tak, 0 - Nie): ";
        cin >> ponownie;
        uzyjTychSamychDanych = (ponownie == 1);
    }
    return 0;
}
