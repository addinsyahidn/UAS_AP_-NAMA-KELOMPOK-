#ifndef KATAGAME_H
#define KATAGAME_H

#include <string>
using namespace std;

struct KataGame {
    string kataAsli;
    string statusTebakan;
    int sisaNyawa;

    char tebakanSalah[26];
    int jumlahSalah;
};

extern string bankKata[];
extern const int JUMLAH_KATA;

string pilihKataAcak();
void inisialisasiGame(KataGame &game, int nyawa);
void tampilkanStatus(const KataGame &game);
bool prosesTebakan(KataGame &game, char huruf);
bool menang(const KataGame &game);

#endif