#include <iostream>
#include <vector>
using namespace std;

// Dodaje dwie binarne liczby reprezentowane przez tablice bitów
void dodaj(vector<int> &a, const vector<int> &b) {
    int carry = 0;
    for (size_t i = 0; i < a.size(); i++) {
        int sum = a[i] + b[i] + carry;
        a[i] = sum % 2;
        carry = sum / 2;
    }
}

// Przeprowadza dopełnienie do dwóch
void uzupelnienieDoDwoch(vector<int> &num) {
    vector<int> jeden(num.size(), 0);
    jeden[0] = 1;
    for (int &bit : num) {
        bit = (bit + 1) % 2;
    }
    dodaj(num, jeden);
}

// Przesuwa w prawo, obsługując Booth-Radix 4
void przesunWPrawo(vector<int> &ac, vector<int> &qr, int &qn) {
    int temp = ac[0];
    qn = qr[0];
    for (size_t i = 0; i < ac.size() - 1; i++) {
        ac[i] = ac[i + 1];
        qr[i] = qr[i + 1];
    }
    qr[qr.size() - 1] = temp;
}

// Wyświetla wynik w formie binarnej
void wyswietlWynik(const vector<int> &ac, const vector<int> &qr) {
    for (auto it = ac.rbegin(); it != ac.rend(); ++it)
        cout << *it;
    cout << " ";
    for (auto it = qr.rbegin(); it != qr.rend(); ++it)
        cout << *it;
    cout << endl;
}

// Wykonuje mnożenie w algorytmie Booth-Radix 4
int main() {
    int brn, qrn;
    vector<int> br, qr, ac;
    int qn = 0, licznik;

    cout << "\n--Podaj mnoznik i mnoznik w postaci dwojkowej uzupelnionej do 2 jesli jest ujemny--";
    cout << "\n Liczba bitow mnoznika=";
    cin >> brn;
    br.resize(brn);
    ac.resize(brn, 0);

    cout << "\nMnoznik=";
    for (int i = brn - 1; i >= 0; i--)
        cin >> br[i];
    uzupelnienieDoDwoch(br);

    cout << "\n Liczba bitow mnoznika=";
    cin >> qrn;
    qr.resize(qrn);
    licznik = qrn;

    cout << "Mnoznik=";
    for (int i = qrn - 1; i >= 0; i--)
        cin >> qr[i];

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

    cout << "Wynik=";
    wyswietlWynik(ac, qr);
}
