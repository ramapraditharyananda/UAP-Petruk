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

struct ItemLaundry {
    string nama;
    int biaya;
    int nilai;
};

int knapsack(ItemLaundry items[], int n, int budget) {
    int K[n+1][budget+1];
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= budget; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (items[i-1].biaya <= w)
                K[i][w] = max(items[i-1].nilai + K[i-1][w - items[i-1].biaya], K[i-1][w]);
            else
                K[i][w] = K[i-1][w];
        }
    }
    return K[n][budget];
}

void cekEfisiensiLayanan() {
    ItemLaundry items[] = {
        {"Cuci 1kg", 5000, 3},
        {"Setrika 1kg", 8000, 4},
        {"Cuci 2kg", 10000, 6},
        {"Setrika 2kg", 15000, 7},
        {"Cuci 3kg", 15000, 8},
        {"Setrika 3kg", 20000, 10}
    };
    int budget;
    cout << "Masukkan budget laundry (Rp): ";
    cin >> budget;
    int n = sizeof(items)/sizeof(items[0]);
    int hasil = knapsack(items, n, budget);
    cout << "Nilai layanan maksimal yang bisa didapatkan: " << hasil << endl;
}
