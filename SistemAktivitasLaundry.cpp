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
    int n = sizeof(items) / sizeof(items[0]);

    for (int i = 0; i < MAX_ITEMS; i++)
        for (int j = 0; j < MAX_BUDGET; j++)
            memo[i][j] = -1;

    int hasil = knapsackRecursive(items, n - 1, budget);
    cout << "Nilai layanan maksimal yang bisa didapatkan: " << hasil << endl;
}

class Laundry {
public:
    string namaPelanggan;
    map<string, int> jenisPakaian;
    int layanan;
    Laundry* next;

    Laundry(string nama, int pilihLayanan) {
        namaPelanggan = nama;
        layanan = pilihLayanan;
        next = nullptr;
    }

    void tambahPakaian(string pakaian, int jumlah) {
        jenisPakaian[pakaian] += jumlah;
    }

    int hitungHarga() {
        int total = 0;
        for (auto& item : jenisPakaian) {
            int tarif = getTarifDenganStrcmp(item.first, layanan);
            total += tarif * item.second;
        }
        return total;
    }

    string getLayanan() {
        if (layanan == 1) return "Cuci Saja";
        if (layanan == 2) return "Setrika Saja";
        if (layanan == 3) return "Cuci & Setrika";
        return "Tidak Diketahui";
    }

    void tampilkanNota() {
        cout << endl << "======= NOTA PEMBAYARAN =======" << endl;
        cout << "Nama Pelanggan: " << namaPelanggan << endl;
        cout << "Layanan: " << getLayanan() << endl;
        cout << "Detail Pakaian:" << endl;
        for (auto& item : jenisPakaian) {
            int tarif = getTarifDenganStrcmp(item.first, layanan);
            int jumlah = item.second;
            int subtotal = tarif * jumlah;
            cout << "- " << item.first << " x " << jumlah << " = Rp " << subtotal << endl;
        }
        cout << "Total: Rp " << hitungHarga() << endl;
        cout << "===============================" << endl;
        cout << endl;
    }
};

class AntrianLaundry {
private:
    Laundry* head;
public:
    AntrianLaundry() { head = nullptr; }

    void tambahCucian(string nama, int layanan) {
        Laundry* temp = head;
        while (temp != nullptr) {
            if (temp->namaPelanggan == nama && temp->layanan == layanan) {
                inputJenisPakaian(temp);
                cout << "Cucian untuk " << nama << " diperbarui." << endl;
                return;
            }
            temp = temp->next;
        }

        Laundry* baru = new Laundry(nama, layanan);
        inputJenisPakaian(baru);
        if (head == nullptr) head = baru;
        else {
            temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = baru;
        }

        cout << "Cucian atas nama " << nama << " berhasil ditambahkan." << endl;
        baru->tampilkanNota();
    }

    void inputJenisPakaian(Laundry* data) {
        for (auto& item : tarifPerItem) {
            int jumlah;
            cout << "Masukkan jumlah " << item.first << ": ";
            cin >> jumlah;
            if (jumlah > 0)
                data->tambahPakaian(item.first, jumlah);
        }
        cin.ignore();
    }

    void tampilkanCucian() {
        if (!head) {
            cout << "Tidak ada cucian dalam antrian." << endl;
            return;
        }
        Laundry* temp = head;
        cout << "Daftar Cucian:" << endl;
        while (temp) {
            cout << "- " << temp->namaPelanggan << " (" << temp->getLayanan() << "):" << endl;
            for (auto& item : temp->jenisPakaian)
                cout << "  * " << item.first << ": " << item.second << endl;
            cout << "  Total Harga: Rp " << temp->hitungHarga() << endl;
            temp = temp->next;
        }
    }

    void cariBarangDenganKeyword() {
        string keyword;
        cout << "Masukkan keyword jenis barang: ";
        getline(cin, keyword);

        string keywordLower = toLower(keyword);
        bool ditemukan = false;

        for (auto& item : tarifPerItem) {
            if (toLower(item.first).find(keywordLower) != string::npos) {
                cout << "Ditemukan: " << item.first << " - Rp " << item.second << endl;
                ditemukan = true;
            }
        }

        if (!ditemukan) {
            cout << "Tidak ditemukan barang dengan kata kunci tersebut." << endl;
        }
    }

    void hapusCucian() {
        if (!head) {
            cout << "Tidak ada cucian untuk dihapus." << endl;
            return;
        }
        Laundry* temp = head;
        head = head->next;
        cout << "Cucian atas nama " << temp->namaPelanggan << " telah selesai." << endl;
        delete temp;
    }

    void hapusSemuaCucian() {
        while (head) {
            Laundry* temp = head;
            head = head->next;
            delete temp;
        }
    }

    Laundry* getHead() { return head; }
};
    void hitungTotalBiaya(AntrianLaundry& laundry) {
    Laundry* temp = laundry.getHead();
    if (!temp) {
        cout << "Tidak ada transaksi." << endl;
        return;
    }

    int total = 0;
    cout << "Rekap Biaya Laundry:" << endl;
    while (temp) {
        int harga = temp->hitungHarga();
        cout << "- " << temp->namaPelanggan << ": Rp " << harga << endl;
        total += harga;
        temp = temp->next;
    }
    cout << "Total biaya seluruh laundry: Rp " << total << endl;
}

void tampilkanUrutanLaundryTermahal(AntrianLaundry& laundry) {
    map<int, string> urutanHarga;
    Laundry* temp = laundry.getHead();
    if (!temp) {
        cout << "Tidak ada cucian." << endl;
        return;
    }

    while (temp) {
        int harga = temp->hitungHarga();
        string deskripsi = temp->namaPelanggan + " (" + temp->getLayanan() + ")";
        while (urutanHarga.find(harga) != urutanHarga.end())
            harga++;
        urutanHarga[harga] = deskripsi;
        temp = temp->next;
    }

    cout << "=== Urutan Pelanggan berdasarkan Harga (Termahal ke Termurah) ===" << endl;
    for (auto it = urutanHarga.rbegin(); it != urutanHarga.rend(); ++it)
        cout << "- " << it->second << ": Rp " << it->first << endl;
}

void tampilkanMenu() {
    cout << "=== MENU UTAMA ===" << endl;
    cout << "1. Tambah Cucian" << endl;
    cout << "2. Tampilkan Daftar Cucian" << endl;
    cout << "3. Hapus Cucian yang Selesai" << endl;
    cout << "4. Lihat Daftar Jenis Pakaian" << endl;
    cout << "5. Lihat Tarif Laundry" << endl;
    cout << "6. Hitung Total Biaya Semua Transaksi" << endl;
    cout << "7. Tampilkan Urutan Laundry Termahal" << endl;
    cout << "8. Cek Efisiensi Layanan (Knapsack)" << endl;
    cout << "9. Cari Jenis Barang Laundry" << endl;
    cout << "10. Keluar dan Hapus Semua Data" << endl;
    cout << "Pilihan: ";
}

int main() {
    AntrianLaundry laundry;
    int pilihan = 0;
    string nama;
    int jenisLayanan;
