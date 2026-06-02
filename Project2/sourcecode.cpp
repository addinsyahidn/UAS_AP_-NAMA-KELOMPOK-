#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>

using namespace std;

struct KataGame {
    string kataAsli;
    string statusTebakan;
    int sisaNyawa;

    char tebakanSalah[26];
    int jumlahSalah;
};

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

int main() {
    srand(time(0));

    KataGame game;

    int pilihan;
    int nyawa;

    cout << "===== GAME TEBAK KATA =====\n";
    cout << "1. Easy (8 Nyawa)\n";
    cout << "2. Medium (6 Nyawa)\n";
    cout << "3. Hard (4 Nyawa)\n";
    cout << "Pilih tingkat kesulitan : ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            nyawa = 8;
            break;
        case 2:
            nyawa = 6;
            break;
        case 3:
            nyawa = 4;
            break;
        default:
            nyawa = 6;
            cout << "Pilihan tidak valid. Default Medium.\n";
    }

    inisialisasiGame(game, nyawa);

    while (game.sisaNyawa > 0 && !menang(game)) {
        tampilkanStatus(game);

        char huruf;
        cout << "Masukkan huruf tebakan : ";
        cin >> huruf;

        prosesTebakan(game, huruf);
    }

    cout << "\n========== HASIL ==========\n";

    if (menang(game)) {
        cout << "Selamat! Anda berhasil menebak kata.\n";
        cout << "Kata rahasia: " << game.kataAsli << endl;
    } else {
        cout << "Game Over!\n";
        cout << "Kata rahasia: " << game.kataAsli << endl;
    }

    return 0;
}