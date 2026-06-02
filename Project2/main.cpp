#include <iostream>
#include <ctime>
#include <cstdlib>
#include "KataGame.h"

using namespace std;

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