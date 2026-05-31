#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define BERSIH         cout << "\033[2J\033[H"
#define PINDAHKE(b, k) cout << "\033[" << (b) << ";" << (k) << "H"
#define WBKG           "\033[47;30m"
#define RST            "\033[0m"

static const char* WARNA_ANGKA[] = {
    "", "\033[1;34m", "\033[1;32m", "\033[1;31m",
    "\033[1;34m", "\033[1;31m", "\033[1;36m", "\033[1;35m", "\033[1;37m"
};

class Permainan {
    int N, jmlBom;
    bool bom[10][10], buka[10][10], tanda[10][10];
    int  angka[10][10];
    bool kalah, menang, giliran1;
    time_t wktMulai;

    static const int db[8];
    static const int dk[8];

    bool valid(int b, int k) { return b >= 0 && b < N && k >= 0 && k < N; }

    void flood(int b, int k, bool tbk[][10], bool tnd[][10]) {
        if (!valid(b, k) || tbk[b][k] || tnd[b][k]) return;
        tbk[b][k] = true;
        if (angka[b][k] == 0)
            for (int a = 0; a < 8; a++)
                flood(b + db[a], k + dk[a], tbk, tnd);
    }

    void hitungAngka() {
        for (int b = 0; b < N; b++)
            for (int k = 0; k < N; k++) {
                if (bom[b][k]) { angka[b][k] = -1; continue; }
                int h = 0;
                for (int a = 0; a < 8; a++) {
                    int nb = b+db[a], nk = k+dk[a];
                    if (valid(nb, nk) && bom[nb][nk]) h++;
                }
                angka[b][k] = h;
            }
    }

    void tanamAcak(int bm, int km) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) bom[i][j] = false;

        bool aman[10][10] = {};
        aman[bm][km] = true;
        for (int a = 0; a < 8; a++) {
            int nb = bm+db[a], nk = km+dk[a];
            if (valid(nb, nk)) aman[nb][nk] = true;
        }
        for (int i = 0; i < jmlBom;) {
            int b = rand()%N, k = rand()%N;
            if (!bom[b][k] && !aman[b][k]) { bom[b][k] = true; i++; }
        }
        hitungAngka();
    }

    bool bisaSelesai(int bm, int km) {
        bool tbk[10][10] = {}, tnd[10][10] = {};
        flood(bm, km, tbk, tnd);

        bool ubah = true;
        while (ubah) {
            ubah = false;

            for (int b = 0; b < N; b++) for (int k = 0; k < N; k++) {
                if (!tbk[b][k] || angka[b][k] <= 0) continue;
                int ttup = 0, btnd = 0;
                for (int a = 0; a < 8; a++) {
                    int nb = b+db[a], nk = k+dk[a];
                    if (!valid(nb, nk)) continue;
                    if (tnd[nb][nk]) btnd++;
                    else if (!tbk[nb][nk]) ttup++;
                }
                if (ttup > 0 && angka[b][k] - btnd == ttup) {
                    for (int a = 0; a < 8; a++) {
                        int nb = b+db[a], nk = k+dk[a];
                        if (valid(nb, nk) && !tbk[nb][nk] && !tnd[nb][nk]) {
                            tnd[nb][nk] = true; ubah = true;
                        }
                    }
                }
                if (ttup > 0 && angka[b][k] == btnd) {
                    for (int a = 0; a < 8; a++) {
                        int nb = b+db[a], nk = k+dk[a];
                        if (valid(nb, nk) && !tbk[nb][nk] && !tnd[nb][nk]) {
                            flood(nb, nk, tbk, tnd); ubah = true;
                        }
                    }
                }
            }   

            for (int b1 = 0; b1 < N; b1++) for (int k1 = 0; k1 < N; k1++) {
                if (!tbk[b1][k1] || angka[b1][k1] <= 0) continue;

                int btnd1 = 0;
                for (int a = 0; a < 8; a++)
                    if (valid(b1+db[a], k1+dk[a]) && tnd[b1+db[a]][k1+dk[a]]) btnd1++;
                int sisaBom1 = angka[b1][k1] - btnd1;
                if (sisaBom1 <= 0) continue;

                for (int a2 = 0; a2 < 8; a2++) {
                    int b2 = b1+db[a2], k2 = k1+dk[a2];
                    if (!valid(b2, k2) || !tbk[b2][k2] || angka[b2][k2] <= 0) continue;
                    if (b1 == b2 && k1 == k2) continue;

                    int btnd2 = 0;
                    for (int a = 0; a < 8; a++)
                        if (valid(b2+db[a], k2+dk[a]) && tnd[b2+db[a]][k2+dk[a]]) btnd2++;
                    int sisaBom2 = angka[b2][k2] - btnd2;
                    if (sisaBom2 <= 0 || sisaBom2 < sisaBom1) continue;

                    bool subset = true;
                    int bkan_subset = 0;

                    for (int a = 0; a < 8; a++) {
                        int nb1 = b1+db[a], nk1 = k1+dk[a];
                        if (!valid(nb1, nk1) || tbk[nb1][nk1] || tnd[nb1][nk1]) continue;
                        bool jg2 = false;
                        for (int aa = 0; aa < 8; aa++)
                            if (b2+db[aa] == nb1 && k2+dk[aa] == nk1) { jg2 = true; break; }
                        if (!jg2) { subset = false; break; }
                    }
                    if (!subset) continue;

                    for (int a = 0; a < 8; a++) {
                        int nb2 = b2+db[a], nk2 = k2+dk[a];
                        if (!valid(nb2, nk2) || tbk[nb2][nk2] || tnd[nb2][nk2]) continue;
                        bool jg1 = false;
                        for (int aa = 0; aa < 8; aa++)
                            if (b1+db[aa] == nb2 && k1+dk[aa] == nk2) { jg1 = true; break; }
                        if (!jg1) bkan_subset++;
                    }

                    if (bkan_subset > 0) {
                        if (sisaBom2 - sisaBom1 == 0) {
                            for (int a = 0; a < 8; a++) {
                                int nb2 = b2+db[a], nk2 = k2+dk[a];
                                if (!valid(nb2, nk2) || tbk[nb2][nk2] || tnd[nb2][nk2]) continue;
                                bool jg1 = false;
                                for (int aa = 0; aa < 8; aa++)
                                    if (b1+db[aa] == nb2 && k1+dk[aa] == nk2) { jg1 = true; break; }
                                if (!jg1) { flood(nb2, nk2, tbk, tnd); ubah = true; }
                            }
                        }
                        else if (sisaBom2 - sisaBom1 == bkan_subset) {
                            for (int a = 0; a < 8; a++) {
                                int nb2 = b2+db[a], nk2 = k2+dk[a];
                                if (!valid(nb2, nk2) || tbk[nb2][nk2] || tnd[nb2][nk2]) continue;
                                bool jg1 = false;
                                for (int aa = 0; aa < 8; aa++)
                                    if (b1+db[aa] == nb2 && k1+dk[aa] == nk2) { jg1 = true; break; }
                                if (!jg1) { tnd[nb2][nk2] = true; ubah = true; }
                            }
                        }
                    }
                }
            }
        }
        for (int b = 0; b < N; b++)
            for (int k = 0; k < N; k++)
                if (!bom[b][k] && !tbk[b][k]) return false;
        return true;
    }

    void tanamBom(int bm, int km) {
        int coba = 0;
        do { tanamAcak(bm, km); } while (!bisaSelesai(bm, km) && ++coba < 300);
    }

    int sisaBom() {
        int j = 0;
        for (int b = 0; b < N; b++)
            for (int k = 0; k < N; k++) j += tanda[b][k];
        return jmlBom - j;
    }

    bool cekMenang() {
        for (int b = 0; b < N; b++)
            for (int k = 0; k < N; k++)
                if (tanda[b][k] != bom[b][k]) return false;
        return true;
    }

    void renderStatus() {
        PINDAHKE(1, 1);
        cout << "  Minesweeper++  |  Bom tersisa: " << sisaBom()
             << "  |  Waktu: " << (int)difftime(time(0), wktMulai) << " detik   ";
    }

    void renderSel(int b, int k, bool ungkap = false) {
        PINDAHKE(5 + b*2, 6 + k*5);
        if (ungkap && bom[b][k]) {
            const char* w = tanda[b][k] ? "\033[1;32m" : buka[b][k] ? "\033[1;31m" : "\033[1;35m";
            const char* s = tanda[b][k] ? "F"          : buka[b][k] ? "*"          : "B";
            cout << WBKG << " " << w << s << "\033[0m" << WBKG << "  |" << RST;
        } else if (buka[b][k] && angka[b][k] > 0) {
            cout << WBKG << " " << WARNA_ANGKA[angka[b][k]] << angka[b][k] << "\033[0m" << WBKG << "  |" << RST;
        } else if (buka[b][k]) {
            cout << WBKG << "    |" << RST;
        } else {
            const char* w = tanda[b][k] ? "\033[1;33m" : "\033[2;37m";
            const char* s = tanda[b][k] ? "?"          : ".";
            cout << WBKG << " " << w << s << "\033[0m" << WBKG << "  |" << RST;
        }
    }

    void renderGaris() {
        cout << WBKG << "+";
        for (int k = 0; k < N; k++) cout << "----+";
        cout << RST;
    }

    void tampilkanPapan(bool ungkap = false) {
        BERSIH; renderStatus();
        PINDAHKE(3, 5);
        cout << " ";
        for (int k = 0; k < N; k++) { int n=k+1; cout << (n<10?"  ":" ") << n << "  "; }
        PINDAHKE(4, 5); renderGaris();
        for (int b = 0; b < N; b++) {
            PINDAHKE(5+b*2, 1);
            int n = b+1; cout << (n<10?"   ":"  ") << n << WBKG << "|" << RST;
            for (int k = 0; k < N; k++) renderSel(b, k, ungkap);
            PINDAHKE(6+b*2, 5); renderGaris();
        }
        PINDAHKE(5+N*2+1, 1);
        cout << "  [.] Tutup  [?] Tanda  [ ] Kosong  [1-8] Angka  [B] Bom  [*] Meledak  [F] Benar";
    }

    void bersihkanMenu() {
        for (int i = 0; i < 5; i++) {
            PINDAHKE(6+N*2+i, 1);
            for (int j = 0; j < 80; j++) cout << ' ';
        }
    }

    void bukaSel(int b, int k) {
        bool sblm[10][10] = {};
        for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) sblm[i][j] = buka[i][j];
        flood(b, k, buka, tanda);
        for (int i = 0; i < N; i++) for (int j = 0; j < N; j++)
            if (buka[i][j] != sblm[i][j]) renderSel(i, j);
        menang = cekMenang();
    }

    bool inputKoord(int &b, int &k) {
        PINDAHKE(6+N*2+1, 1); cout << "  Baris (1-" << N << "): "; cin >> b;
        PINDAHKE(6+N*2+2, 1); cout << "  Kolom (1-" << N << "): "; cin >> k;
        if (cin.fail() || b < 1 || b > N || k < 1 || k > N) {
            cin.clear(); cin.ignore(1000, '\n');
            PINDAHKE(6+N*2+3, 1); cout << "  [!] Koordinat tidak valid! Tekan Enter...";
            cin.ignore(1000, '\n'); cin.get();
            return false;
        }
        b--; k--;
        return true;
    }

    void mainRonde() {
        for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
            bom[i][j] = buka[i][j] = tanda[i][j] = false; angka[i][j] = 0;
        }
        kalah = menang = false; giliran1 = true;
        wktMulai = time(0);
        tampilkanPapan();

        while (!kalah && !menang) {
            renderStatus();
            PINDAHKE(6+N*2, 1);
            cout << "  Aksi: [1] Buka  [2] Tandai/Hapus   Pilihan: " << flush;
            int aksi; cin >> aksi;
            if (cin.fail() || (aksi != 1 && aksi != 2)) { cin.clear(); cin.ignore(1000,'\n'); continue; }

            int b, k;
            if (!inputKoord(b, k)) { bersihkanMenu(); continue; }

            if (aksi == 1) {
                if (tanda[b][k]) {
                    PINDAHKE(6+N*2+3, 1); cout << "  [!] Hapus tanda dulu. Tekan Enter...";
                    cin.ignore(1000,'\n'); cin.get();
                } else if (buka[b][k]) {
                    PINDAHKE(6+N*2+3, 1); cout << "  [!] Kotak sudah terbuka. Tekan Enter...";
                    cin.ignore(1000,'\n'); cin.get();
                } else {
                    if (giliran1) {
                        PINDAHKE(6+N*2, 1); cout << "  Membuat papan..." << flush;
                        tanamBom(b, k); giliran1 = false; tampilkanPapan();
                    }
                    if (bom[b][k]) { buka[b][k] = true; kalah = true; }
                    else bukaSel(b, k);
                }
            } else {
                if (buka[b][k]) {
                    PINDAHKE(6+N*2+3, 1); cout << "  [!] Tidak bisa menandai kotak terbuka. Tekan Enter...";
                    cin.ignore(1000,'\n'); cin.get();
                } else {
                    tanda[b][k] = !tanda[b][k];
                    renderSel(b, k); renderStatus();
                    menang = cekMenang();
                }
            }
            bersihkanMenu();
        }

        tampilkanPapan(true);
        PINDAHKE(5+N*2+2, 1);
        cout << (kalah ? "  *** GAME OVER! Kamu menginjak bom! ***"
                       : "  *** SELAMAT! Semua bom berhasil ditandai! ***") << "\n";
        cout << "  Waktu: " << (int)difftime(time(0), wktMulai) << " detik\n\n";
    }

public:
    bool inputPengaturan() {
        int n, b;
        cout << "\n  Ukuran papan (4-10): "; cin >> n;
        if (cin.fail() || n < 4 || n > 10) {
            cin.clear(); cin.ignore(1000,'\n');
            cout << "  [!] Ukuran harus antara 4 dan 10.\n"; return false;
        }
        int mksBom = max(1, n*n*35/100);
        cout << "  Jumlah bom (1-" << mksBom << "): "; cin >> b;
        if (cin.fail() || b < 1 || b > mksBom) {
            cin.clear(); cin.ignore(1000,'\n');
            cout << "  [!] Jumlah bom tidak valid.\n"; return false;
        }
        N = n; jmlBom = b; return true;
    }

    void menuUtama() {
        srand((unsigned)time(0));
        while (true) {
            BERSIH;
            cout << "\n""  ============================\n"
                        "    M I N E S W E E P E R ++\n"
                        "  ============================\n\n"
                        "  [1] Mulai Permainan Baru\n"
                        "  [2] Keluar\n\n"
                        "  Pilihan: ";
            int pilihan; cin >> pilihan;
            if (cin.fail()) { cin.clear(); cin.ignore(1000,'\n'); continue; }
            if (pilihan == 1) {
                BERSIH;
                while (!inputPengaturan()) {
                    cout << "  Coba lagi. Tekan Enter...";
                    cin.ignore(1000,'\n'); cin.get(); BERSIH;
                }
                mainRonde();
                cout << "  Tekan Enter untuk kembali ke menu...";
                cin.ignore(1000,'\n'); cin.get();
            } else if (pilihan == 2) {
                BERSIH; cout << "\n  Sampai jumpa!\n\n"; break;
            }
        }
    }
};

const int Permainan::db[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
const int Permainan::dk[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

int main() { Permainan g; g.menuUtama(); }
