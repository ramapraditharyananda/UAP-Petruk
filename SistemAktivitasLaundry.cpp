#include<iostream>
#include<cstring>
#include<string>
#include<map>
using namespace std;

const int MAX_ITEMS = 100;
const int MAX_BUDGET = 10000;

map<string, int> tarifPerItem = {
    {"Baju", 3000},
    {"Celana", 4000},
    {"Jaket", 5000},
    {"Seprai", 6000},
    {"Handuk", 3500}
};

const char* daftarPakaian[] = {"Baju", "Celana", "Jaket", "Seprai", "Handuk"};
const char** ptrPakaian = daftarPakaian;

string toLower(const string& s) {
    string result = s;
    for (size_t i = 0; i < result.size(); ++i) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] - 'A' + 'a';
        }
    }
    return result;
}

void tampilkanPakaian() {
    cout << "Jenis pakaian:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "- " << *(ptrPakaian + i) << endl;
    }
}

void tampilkanTarif() {
    cout << "Tarif per item (Rp):" << endl;
    for (auto& item : tarifPerItem) {
        cout << "- " << item.first << ": Rp " << item.second << endl;
    }
}

int getTarifDenganStrcmp(const string& namaPakaian, int layanan) {
    const char* np = namaPakaian.c_str();

    if (strcmp(np, "Baju") == 0)
        return (layanan == 3) ? 3000 * 2 : 3000;
    else if (strcmp(np, "Celana") == 0)
        return (layanan == 3) ? 4000 * 2 : 4000;
    else if (strcmp(np, "Jaket") == 0)
        return (layanan == 3) ? 5000 * 2 : 5000;
    else if (strcmp(np, "Seprai") == 0)
        return (layanan == 3) ? 6000 * 2 : 6000;
    else if (strcmp(np, "Handuk") == 0)
        return (layanan == 3) ? 3500 * 2 : 3500;
    else
        return 0;
}

struct ItemLaundry {
    string nama;
    int biaya;
    int nilai;
};

int memo[MAX_ITEMS][MAX_BUDGET];

int knapsackRecursive(ItemLaundry items[], int i, int budget) {
    if (i < 0 || budget <= 0)
        return 0;

    if (memo[i][budget] != -1)
        return memo[i][budget];

    if (items[i].biaya > budget) {
        memo[i][budget] = knapsackRecursive(items, i - 1, budget);
    } else {
        int ambil = items[i].nilai + knapsackRecursive(items, i - 1, budget - items[i].biaya);
        int tidakAmbil = knapsackRecursive(items, i - 1, budget);
        memo[i][budget] = (ambil > tidakAmbil) ? ambil : tidakAmbil;
    }

    return memo[i][budget];
}
