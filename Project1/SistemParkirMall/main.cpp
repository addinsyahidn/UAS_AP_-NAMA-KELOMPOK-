#include "ParkirMall.h"
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>  

// ========== IMPLEMENTASI FUNGSI DARI CLASS ==========

// Konstruktor Kendaraan
Kendaraan::Kendaraan(string plat, string merk, string warna) {
    platMobil = plat;
    merkMobil = merk;
    warnaMobil = warna;
    waktuMasuk = time(0);
}

// Konstruktor Petugas
Petugas::Petugas(string n, string i) {
    nama = n;
    id = i;
}

// Konstruktor SistemParkir
SistemParkir::SistemParkir() {
    petugasAktif = nullptr;
}

// Destruktor SistemParkir
SistemParkir::~SistemParkir() {
    for (Kendaraan* k : daftarParkir) {
        delete k;
    }
    delete petugasAktif;
}

// Implementasi formatWaktu
string SistemParkir::formatWaktu(time_t waktu) {
    time_t now = time(0);
    double detik = difftime(now, waktu);
    int jam = (int)detik / 3600;
    int menit = ((int)detik % 3600) / 60;
    int detikInt = (int)detik % 60;
    
    return to_string(jam) + " jam " + to_string(menit) + 
           " menit " + to_string(detikInt) + " detik";
}

// Implementasi hitungBiaya
int SistemParkir::hitungBiaya(time_t waktuMasuk) {
    time_t now = time(0);
    double detik = difftime(now, waktuMasuk);
    int jam = (int)detik / 3600;
    
    if (jam < 1) return 5000;
    if (jam <= 2) return 8000;
    return 8000 + (jam - 2) * 3000;
}

// Implementasi setPetugas
void SistemParkir::setPetugas(string nama, string id) {
    petugasAktif = new Petugas(nama, id);
    cout << "\n=== Petugas Terdaftar ===" << endl;
    cout << "Nama: " << petugasAktif->nama << endl;
    cout << "ID: " << petugasAktif->id << endl;
    cout << "========================\n" << endl;
}

// Implementasi tambahKendaraan
bool SistemParkir::tambahKendaraan() {
    if (daftarParkir.size() >= KAPASITAS_MAX) {
        cout << "\n!!! PARKIRAN PENUH !!!" << endl;
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return false;
    }
    
    int jumlah;
    cout << "Masukan jumlah mobil yang akan diparkirkan: ";
    cin >> jumlah;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    for (int i = 0; i < jumlah; i++) {
        if (daftarParkir.size() >= KAPASITAS_MAX) {
            cout << "\n!!! PARKIRAN PENUH !!!" << endl;
            break;
        }
        
        string plat, merk, warna;
        cout << "\nMobil ke " << (i + 1) << endl;
        cout << "Masukkan plat mobil : ";
        getline(cin, plat);
        cout << "Masukkan merk mobil : ";
        getline(cin, merk);
        cout << "Masukkan warna mobil: ";
        getline(cin, warna);
        
        Kendaraan* baru = new Kendaraan(plat, merk, warna);
        daftarParkir.push_back(baru);
        cout << "Mobil berhasil diparkir!" << endl;
    }
    
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return true;
}

// Implementasi tampilkanDaftar
void SistemParkir::tampilkanDaftar() {
    if (daftarParkir.empty()) {
        cout << "\n=== TIDAK ADA KENDARAAN YANG SEDANG PARKIR ===\n" << endl;
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
    
    cout << "\n=== DAFTAR MOBIL YANG SEDANG PARKIR ===" << endl;
    cout << "Total: " << daftarParkir.size() << " / " << KAPASITAS_MAX << endl;
    cout << "========================================\n" << endl;
    
    for (size_t i = 0; i < daftarParkir.size(); i++) {
        cout << "=======================" << endl;
        cout << "Mobil ke-" << (i + 1) << endl;
        cout << "  Plat mobil : " << daftarParkir[i]->platMobil << endl;
        cout << "  Merk mobil : " << daftarParkir[i]->merkMobil << endl;
        cout << "  Warna mobil: " << daftarParkir[i]->warnaMobil << endl;
        cout << "  Waktu parkir: " << formatWaktu(daftarParkir[i]->waktuMasuk) << endl;
        cout << "=======================" << endl;
    }
    
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Implementasi prosesPembayaran 
void SistemParkir::prosesPembayaran() {
    if (daftarParkir.empty()) {
        cout << "\n=== TIDAK ADA KENDARAAN YANG SEDANG PARKIR ===\n" << endl;
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    tampilkanDaftar();
    string platInput;
    cout << "Masukkan plat mobil yang akan dibayar: ";
    getline(cin, platInput);  

    // Cari mobil berdasarkan plat nomor (case-insensitive, abaikan spasi)
    int foundIndex = -1;
    for (size_t i = 0; i < daftarParkir.size(); i++) {
        string platTersimpan = daftarParkir[i]->platMobil;
        string platInputTemp = platInput;

        // Ubah ke lowercase
        for (char &c : platTersimpan) c = tolower(c);
        for (char &c : platInputTemp) c = tolower(c);

        // Hapus semua spasi
        string cleanTersimpan = "", cleanInput = "";
        for (char c : platTersimpan) if (c != ' ') cleanTersimpan += c;
        for (char c : platInputTemp) if (c != ' ') cleanInput += c;

        if (cleanTersimpan == cleanInput) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "\n!!! PLAT NOMOR TIDAK DITEMUKAN !!!" << endl;
        cout << "Pastikan plat mobil yang dimasukkan benar.\n" << endl;
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    Kendaraan* keluar = daftarParkir[foundIndex];
    int biaya = hitungBiaya(keluar->waktuMasuk);

    cout << "\n=== STRUK PEMBAYARAN ===" << endl;
    cout << "Plat Nomor: " << keluar->platMobil << endl;
    cout << "Merk      : " << keluar->merkMobil << endl;
    cout << "Warna     : " << keluar->warnaMobil << endl;
    cout << "Durasi    : " << formatWaktu(keluar->waktuMasuk) << endl;
    cout << "Biaya     : Rp " << biaya << endl;
    cout << "========================" << endl;
    cout << "Terima kasih!\n" << endl;

    delete keluar;
    daftarParkir.erase(daftarParkir.begin() + foundIndex);

    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Implementasi isParkirPenuh
bool SistemParkir::isParkirPenuh() {
    return daftarParkir.size() >= KAPASITAS_MAX;
}

// ========== FUNGSI MAIN (JALANNYA PROGRAM) ==========
int main() {
    SistemParkir parkir;
    string nama, id;
    
    system("cls");
    
    cout << "============================================" << endl;
    cout << "-------------SELAMAT DATANG-----------------" << endl; 
    cout << "         DI PORTAL PARKIR KHUSUS MOBIL      " << endl;
    cout << "              MALL PRIENAL                  " << endl;
    cout << "============================================" << endl;

    cout << "\nKami senang Anda telah hadir." << endl;
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini.\n";
    
    cout << "\nMasukkan nama : ";
    getline(cin, nama);
    cout << "Masukkan ID   : ";
    getline(cin, id);
    
    parkir.setPetugas(nama, id);

    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    
    int pilihan;
    do {
        system("cls");
        
        cout << "==========================================" << endl;
        cout << "   Silahkan input Opsi berikut dalam angka" << endl;
        cout << "==========================================" << endl;
        cout << "1. Tambah Kendaraan" << endl;
        cout << "2. Tampilkan Daftar" << endl;
        cout << "3. Pembayaran" << endl;
        cout << "4. Keluar Program" << endl;
        cout << "========================================" << endl;
        cout << "Masukkan opsi : ";
        cin >> pilihan;
        
        // Validasi input pilihan menu
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n!!! Input harus angka 1-4 !!!" << endl;
            cout << "Tekan Enter untuk melanjutkan...";
            cin.get();
            continue;
        }
        
        switch(pilihan) {
            case 1: 
                parkir.tambahKendaraan(); 
                break;
            case 2: 
                parkir.tampilkanDaftar(); 
                break;
            case 3: 
                parkir.prosesPembayaran(); 
                break;
            case 4: 
                cout << "\nTerima kasih telah menggunakan sistem parkir!" << endl;
                cout << "Sampai jumpa kembali di Mall Prienal.\n" << endl;
                break;
            default: 
                cout << "\n!!! Pilihan salah! Masukkan 1-4 !!!" << endl;
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
        }
    } while(pilihan != 4);
    
    return 0;
}
