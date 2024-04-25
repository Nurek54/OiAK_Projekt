#include<iostream>
using namespace std;

// Funkcja dodajaca dwie liczby binarne (w postaci tablic) i przechowujaca wynik w pierwszej tablicy
void dodaj(int a[], int x[], int q) {
    int i, c = 0; // 'c' jest zmienną przechowującą nadmiar (carry)
    for (i = 0; i < q; i++) {
        a[i] = a[i] + x[i] + c; // dodawanie odpowiadających bitów wraz z przeniesieniem
        if (a[i] > 1) {
            a[i] = a[i] % 2; // jeśli suma bitów wynosi 2 lub więcej, ustaw odpowiedni bit na 0 lub 1
            c = 1; // ustawienie nadmiaru na 1
        } else {
            c = 0; // brak nadmiaru
        }
    }
}

// Funkcja wykonująca przesunięcie arytmetyczne w prawo (ASHR) dla dwóch liczb binarnych (AC i QR)
void przesunWPrawo(int ac[], int qr[], int &qn, int q) {
    int temp, i;
    temp = ac[0]; // przechowanie najstarszego bitu
    qn = qr[0]; // przypisanie nowego bitu najmłodszego w QR
    for (i = 0; i < q - 1; i++) {
        ac[i] = ac[i + 1]; // przesunięcie bitów AC
        qr[i] = qr[i + 1]; // przesunięcie bitów QR
    }
    qr[q - 1] = temp; // przypisanie starego najstarszego bitu AC do najmłodszego bitu QR
}

// Funkcja wyświetlająca wynik mnożenia
void wyswietlWynik(int ac[], int qr[], int qrn) {
    int i;
    for (i = qrn - 1; i >= 0; i--)
        cout << ac[i]; // wyświetlenie bitów AC od najstarszego do najmłodszego
    cout << " ";
    for (i = qrn - 1; i >= 0; i--)
        cout << qr[i]; // wyświetlenie bitów QR od najstarszego do najmłodszego
    cout << endl;
}

// Funkcja wykonująca uzupełnienie do 2 dla liczby binarnej (zmiana na jej dopełnienie do jedynki)
void uzupelnienieDoDwoch(int a[], int n) {
    int i;
    int x[8] = { 0 }; // pomocnicza tablica do dodania 1
    x[0] = 1; // dodanie 1 do najmłodszego bitu
    for (i = 0; i < n; i++) {
        a[i] = (a[i] + 1) % 2; // negacja każdego bitu
    }
    dodaj(a, x, n); // dodanie 1 do wyniku negacji
}

int main(int argc, char **argv) {
    int mt[10], br[10], qr[10], sc, ac[10] = { 0 }; // deklaracje tablic dla mnożenia i pomocniczych zmiennych
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
