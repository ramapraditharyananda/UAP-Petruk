#include<iostream>
#include<string>
#include<map>
using namespace std;

void (*menuPointer)();
int tarifLaundry[3][2] = {
    {5000, 8000},
    {10000, 15000},
    {15000, 20000}
};
string daftarPakaian[] = {"Baju", "Celana", "Jaket", "Seprai", "Handuk"};
string* ptrPakaian = daftarPakaian;

void tampilkanPakaian() {
    cout << "Jenis pakaian:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "- " << *(ptrPakaian + i) << endl;
    }
}

void tampilkanTarif() {
    cout << "Tarif Laundry (Rp):" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Berat " << (i + 1) << " kg: Cuci = " << tarifLaundry[i][0]
             << ", Setrika = " << tarifLaundry[i][1]
             << ", Cuci & Setrika = " << tarifLaundry[i][0] + tarifLaundry[i][1] << endl;
    }
}
