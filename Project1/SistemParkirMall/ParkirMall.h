// ParkirMall.h
#ifndef PARKIRMALL_H
#define PARKIRMALL_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

// Class untuk data kendaraan
class Kendaraan {
public:
    string platMobil;
    string merkMobil;
    string warnaMobil;
    time_t waktuMasuk;
    
    Kendaraan(string plat, string merk, string warna);
};

// Class untuk data petugas
class Petugas {
public:
    string nama;
    string id;
    
    Petugas(string n, string i);
};

// Class utama sistem parkir
class SistemParkir {
private:
    vector<Kendaraan*> daftarParkir;
    Petugas* petugasAktif;
    const int KAPASITAS_MAX = 10;
    
    string formatWaktu(time_t waktu);
    int hitungBiaya(time_t waktuMasuk);
    
public:
    SistemParkir();
    ~SistemParkir();
    void setPetugas(string nama, string id);
    bool tambahKendaraan();
    void tampilkanDaftar();
    void prosesPembayaran();
    bool isParkirPenuh();
};

#endif