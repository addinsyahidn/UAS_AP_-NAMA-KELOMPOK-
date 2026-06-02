#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <vector>
#include <iomanip>

using namespace std;

struct dataBarang{
    string kodeBarang, namaBarang;
    long int harga, jmlhstok;
};

vector <dataBarang> stok;

void tambahBarang(){
    dataBarang temp;

    while (true) {
        cout << "Kode barang: ";
        cin >> temp.kodeBarang;
        bool duplikat = false;
        for (const auto& b : stok)
            if (b.kodeBarang == temp.kodeBarang) { duplikat = true; break; }
        if (!duplikat) break;
        cout << " [ERROR] Kode barang sudah ada! Gunakan kode lain.\n";
    }

    cin.ignore();
    cout << "Nama barang: ";
    getline(cin, temp.namaBarang);

    while (true) {
        cout << "Harga barang: Rp";
        if (cin >> temp.harga && temp.harga >= 0) break;
        cin.clear(); cin.ignore(1000, '\n');
        cout << " [ERROR] Harga tidak valid! Masukkan angka >= 0.\n";
    }

    while (true) {
        cout << "Stok: ";
        if (cin >> temp.jmlhstok && temp.jmlhstok >= 0) break;
        cin.clear(); cin.ignore(1000, '\n');
        cout << " [ERROR] Stok tidak valid! Masukkan angka >= 0.\n";
    }

    stok.push_back(temp);
    cout << " [Success] Barang telah diinput!" << endl;
    system("pause");
}

void tampilkanBarang(){
    cout << "=======================================" << endl;
    cout << "               STOK PRODUK             " << endl;
    cout << "=======================================" << endl << endl;

    if (stok.empty()) {
        cout << " [INFO] Belum ada data barang.\n\n";
        system("pause");
        return;
    }

    cout << "No | Kode Barang | Nama Barang               | Harga barang    | Stok   " << endl;
    cout << "---|-------------|---------------------------|-----------------|--------" << endl;
    for (int i = 0; i < (int)stok.size(); i++){
        cout << setw(2) << i + 1 << " | ";
        cout << setw(11) << stok[i].kodeBarang << " | ";
        cout << setw(25) << left << stok[i].namaBarang << right << " | ";
        cout << "Rp" << setw(10) << stok[i].harga << ",00 | ";
        cout << setw(5) << stok[i].jmlhstok << endl;
    }

    cout << endl;
    system("pause");
}

void barangTermahal(){
    cout << "=======================================" << endl;
    cout << "            BARANG TERMAHAL            " << endl;
    cout << "=======================================" << endl << endl;

    if (stok.empty()) {
        cout << " [INFO] Belum ada data barang.\n\n";
        system("pause");
        return;
    }

    const dataBarang* termahal = &stok[0];
    for (const auto& b : stok) if (b.harga > termahal->harga) termahal = &b;

    cout << " Kode Barang  : " << termahal->kodeBarang << endl;
    cout << " Nama Barang  : " << termahal->namaBarang << endl;
    cout << " Harga        : Rp" << termahal->harga << ",00" << endl;
    cout << " Stok         : " << termahal->jmlhstok << endl;

    cout << endl;
    system("pause");
}

void hitungInventaris(){
    cout << "=======================================" << endl;
    cout << "         TOTAL NILAI INVENTARIS        " << endl;
    cout << "=======================================" << endl << endl;

    if (stok.empty()) {
        cout << " [INFO] Belum ada data barang.\n\n";
        system("pause");
        return;
    }

    cout << "No | Kode Barang | Nama Barang               | Harga barang    | Stok  | Sub-Total" << endl;
    cout << "---|-------------|---------------------------|-----------------|-------|------------------" << endl;

    long long total = 0;
    for (int i = 0; i < (int)stok.size(); i++) {
        long long sub = (long long)stok[i].harga * stok[i].jmlhstok;
        total += sub;
        cout << setw(2) << i + 1 << " | ";
        cout << setw(11) << stok[i].kodeBarang << " | ";
        cout << setw(25) << left << stok[i].namaBarang << right << " | ";
        cout << "Rp" << setw(10) << stok[i].harga << ",00 | ";
        cout << setw(5) << stok[i].jmlhstok << " | ";
        cout << "Rp" << setw(10) << sub << ",00" << endl;
    }

    cout << "---|-------------|---------------------------|-----------------|-------|------------------" << endl << endl;
    cout << " TOTAL NILAI INVENTARIS : Rp" << total << ",00" << endl;

    cout << endl;
    system("pause");
}

void cekRestock(){
    cout << "=======================================" << endl;
    cout << "        BARANG KRITIS (STOK < 5)       " << endl;
    cout << "=======================================" << endl << endl;

    bool ada = false;
    for (const auto& b : stok) {
        if (b.jmlhstok < 5) {
            if (!ada) {
                cout << left << setw(12) << "Kode";
                cout << setw(25) << "Nama Barang";
                cout << right << setw(6) << "Stok" << endl;
                cout << string(43, '-') << endl;
                ada = true;
            }
            cout << left << setw(12) << b.kodeBarang;
            cout << setw(25) << b.namaBarang;
            cout << right << setw(6) << b.jmlhstok << endl;
        }
    }

    if (!ada)
        cout << " [OK] Semua barang memiliki stok yang cukup (>= 5).\n";

    cout << endl;
    system("pause");
}

void updateStock(){
    cout << "=======================================" << endl;
    cout << "           UPDATE STOK BARANG          " << endl;
    cout << "=======================================" << endl << endl;

    if (stok.empty()) {
        cout << " [INFO] Belum ada data barang.\n\n";
        system("pause");
        return;
    }

    string kode;
    cout << "Masukkan kode barang: ";
    cin >> kode;

    dataBarang* target = nullptr;
    for (auto& b : stok)
        if (b.kodeBarang == kode) { target = &b; break; }

    if (target == nullptr) {
        cout << " [ERROR] Barang dengan kode \"" << kode << "\" tidak ditemukan.\n";
        system("pause");
        return;
    }

    cout << " Ditemukan    : " << target->namaBarang << endl;
    cout << " Stok saat ini: " << target->jmlhstok << endl;
    cout << " Pilih operasi:\n";
    cout << "   1. Tambah stok (barang masuk)\n";
    cout << "   2. Kurangi stok (barang keluar)\n";

    int op;
    do {
        cout << " Pilihan (1/2): ";
        cin >> op;
        if (op != 1 && op != 2)
            cout << " [ERROR] Pilih 1 atau 2!\n";
    } while (op != 1 && op != 2);

    long int jumlah;
    while (true) {
        cout << " Jumlah: ";
        if (cin >> jumlah && jumlah > 0) break;
        cin.clear(); cin.ignore(1000, '\n');
        cout << " [ERROR] Masukkan angka > 0.\n";
    }

    long int* pStok = &target->jmlhstok;
    if (op == 1) {
        *pStok += jumlah;
        cout << " [Success] Stok bertambah: " << *pStok - jumlah << " -> " << *pStok << endl;
    } else {
        if (jumlah > *pStok) {
            cout << " [ERROR] Stok tidak cukup! Stok saat ini hanya " << *pStok << ".\n";
        } else {
            *pStok -= jumlah;
            cout << " [Success] Stok berkurang: " << *pStok + jumlah << " -> " << *pStok << endl;
        }
    }

    cout << endl;
    system("pause");
}


int main(){
    while (true){
        system ("cls");
        cout << "=======================================" << endl;
        cout << "   SISTEM MANAJEMEN INVENTARIS TOKO    " << endl;
        cout << "=======================================" << endl;
        cout << "Layanan: " << endl;
        cout << "1. Tambah Barang" << endl;
        cout << "2. Tampilkan Semua Barang" << endl;
        cout << "3. Cari Barang Termahal" << endl;
        cout << "4. Hitung Total Inventaris" << endl;
        cout << "5. Cek Restock" << endl;
        cout << "6. Update Stock" << endl;
        cout << "7. Keluar" << endl;

        int input;
        do{
            cout << "Pilih layanan (1-7): "; 
            cin >> input;
            
            if (input < 1 || input > 7){
                cout << " [ERROR] Input tidak valid!";
                this_thread::sleep_for(chrono::seconds(1));
                cout << "\033[A\r\033[J";
            }
        } while (input < 1 || input > 7);

        system("cls");
        if (input == 1){ tambahBarang(); system("cls");}
        else if (input == 2){ tampilkanBarang(); system("cls");}
        else if (input == 3){ barangTermahal(); system("cls");}
        else if (input == 4){ hitungInventaris(); system("cls");}
        else if (input == 5){ cekRestock(); system("cls");}
        else if (input == 6){ updateStock(); system("cls");}
        else{
            cout << " PROGRAM SELESAI!  " << endl;
            cout << " Terima kasih" << endl;
            break;
        }
    }

    return 0;
}
