#include "KataGame.h"
#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

string bankKata[] = {
    "komputer",
    "program",
    "algoritma",
    "kampus",
    "mahasiswa",
    "internet",
    "keyboard",
    "monitor",
    "printer",
    "database",
    "jaringan",
    "variabel",
    "struktur",
    "pointer",
    "compiler"
};

const int JUMLAH_KATA = 15;

string pilihKataAcak() {
    int index = rand() % JUMLAH_KATA;
    return bankKata[index];
}

void inisialisasiGame(KataGame &game, int nyawa) {
    game.kataAsli = pilihKataAcak();
    game.statusTebakan = string(game.kataAsli.length(), '_');
    game.sisaNyawa = nyawa;
    game.jumlahSalah = 0;
}

void tampilkanStatus(const KataGame &game) {
    cout << "\n=================================\n";

    cout << "Kata : ";
    for (char c : game.statusTebakan) {
        cout << c << ' ';
    }

    cout << "\nNyawa : " << game.sisaNyawa;

    cout << "\nHuruf Salah : ";
    for (int i = 0; i < game.jumlahSalah; i++) {
        cout << game.tebakanSalah[i] << ' ';
    }

    cout << "\n=================================\n";
}

bool prosesTebakan(KataGame &game, char huruf) {
    bool ditemukan = false;

    huruf = tolower(huruf);

    for (int i = 0; i < game.kataAsli.length(); i++) {
        if (game.kataAsli[i] == huruf) {
            game.statusTebakan[i] = huruf;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        game.tebakanSalah[game.jumlahSalah] = huruf;
        game.jumlahSalah++;
        game.sisaNyawa--;

        cout << "Huruf tidak ditemukan!\n";
    } else {
        cout << "Huruf ditemukan!\n";
    }

    return ditemukan;
}

bool menang(const KataGame &game) {
    return game.kataAsli == game.statusTebakan;
}