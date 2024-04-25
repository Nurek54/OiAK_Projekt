#include<iostream>
using namespace std;

// Funkcja dodajaca dwie liczby binarne (w postaci tablic) i przechowujaca wynik w pierwszej tablicy
void dodaj(int a[], int x[], int q) {
    int i, c = 0;
    for (i = 0; i < q; i++) {
        a[i] = a[i] + x[i] + c;
        if (a[i] > 1) {
            a[i] = a[i] % 2;
            c = 1;
        } else {
            c = 0;
        }
    }
}

// Funkcja wykonujaca przesuniecie arytmetyczne w prawo (ASHR) dla dwoch liczb binarnych (AC i QR)
void przesunWPrawo(int ac[], int qr[], int &qn, int q) {
    int temp, i;
    temp = ac[0];
    qn = qr[0];
    for (i = 0; i < q - 1; i++) {
        ac[i] = ac[i + 1];
        qr[i] = qr[i + 1];
    }
    qr[q - 1] = temp;
}

// Funkcja wyswietlajaca wynik mnozenia
void wyswietlWynik(int ac[], int qr[], int qrn) {
    int i;
    for (i = qrn - 1; i >= 0; i--)
        cout << ac[i];
    cout << " ";
    for (i = qrn - 1; i >= 0; i--)
        cout << qr[i];
    cout << endl;
}

// Funkcja wykonujaca uzupelnienie do 2 dla liczby binarnej (zmiana na jej dopełnienie do jedynki)
void uzupelnienieDoDwoch(int a[], int n) {
    int i;
    int x[8] = { 0 };
    x[0] = 1;
    for (i = 0; i < n; i++) {
        a[i] = (a[i] + 1) % 2;
    }
    dodaj(a, x, n);
}

int main(int argc, char **argv) {
    int mt[10], br[10], qr[10], sc, ac[10] = { 0 };
    int brn, qrn, i, qn, temp;
    cout << "\n--Podaj mnoznik i mnoznik w postaci dwojkowej uzupelnionej do 2 jesli jest ujemny--";
    cout << "\n Liczba bitow mnoznika=";
    cin >> brn;
    cout << "\nMnoznik=";
    for (i = brn - 1; i >= 0; i--)
        cin >> br[i];
    for (i = brn - 1; i >= 0; i--)
        mt[i] = br[i];
    uzupelnienieDoDwoch(mt, brn);
    cout << "\n Liczba bitow mnoznika=";
    cin >> qrn;
    sc = qrn;
    cout << "Mnoznik=";
    for (i = qrn - 1; i >= 0; i--)
        cin >> qr[i];
    qn = 0;
    temp = 0;
    while (sc != 0) {
        if ((qn + qr[0]) == 1) {
            if (temp == 0) {
                dodaj(ac, mt, qrn);
                temp = 1;
            } else if (temp == 1) {
                dodaj(ac, br, qrn);
                temp = 0;
            }
            przesunWPrawo(ac, qr, qn, qrn);
        } else if (qn - qr[0] == 0)
            przesunWPrawo(ac, qr, qn, qrn);
        sc--;
    }
    cout << "Wynik=";
    wyswietlWynik(ac, qr, qrn);
}
