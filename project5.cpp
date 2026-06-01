#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

string negara[] = {
    "afghanistan", "albania", "algeria", "andorra", "angola",
    "argentina", "armenia", "australia", "austria", "azerbaijan",
    "bahrain", "bangladesh", "barbados", "belarus", "belgium",
    "belize", "benin", "bhutan", "bolivia", "botswana",
    "brazil", "brunei", "bulgaria", "burundi", "cambodia",
    "cameroon", "canada", "chad", "chile", "china",
    "colombia", "comoros", "congo", "croatia", "cuba",
    "cyprus", "denmark", "djibouti", "dominica", "ecuador",
    "egypt", "eritrea", "estonia", "eswatini", "ethiopia",
    "fiji", "finland", "france", "gabon", "gambia",
    "georgia", "germany", "ghana", "greece", "grenada",
    "guatemala", "guinea", "guyana", "haiti", "honduras",
    "hungary", "iceland", "india", "indonesia", "iran",
    "iraq", "ireland", "israel", "italy", "jamaica",
    "japan", "jordan", "kazakhstan", "kenya", "kiribati",
    "kuwait", "kyrgyzstan", "laos", "latvia", "lebanon",
    "lesotho", "liberia", "libya", "liechtenstein", "lithuania",
    "luxembourg", "madagascar", "malawi", "malaysia", "maldives",
    "mali", "malta", "mauritania", "mauritius", "mexico",
    "micronesia", "moldova", "monaco", "mongolia", "montenegro",
    "morocco", "mozambique", "myanmar", "namibia", "nauru",
    "nepal", "netherlands", "nicaragua", "niger", "nigeria",
    "norway", "oman", "pakistan", "palau", "panama",
    "paraguay", "peru", "philippines", "poland", "portugal",
    "qatar", "romania", "russia", "rwanda", "samoa",
    "senegal", "serbia", "seychelles", "singapore", "slovakia",
    "slovenia", "somalia", "spain", "sudan", "suriname",
    "sweden", "switzerland", "syria", "tajikistan", "tanzania",
    "thailand", "togo", "tonga", "tunisia", "turkey",
    "turkmenistan", "tuvalu", "uganda", "ukraine", "uruguay",
    "uzbekistan", "vanuatu", "venezuela", "vietnam", "yemen",
    "zambia", "zimbabwe"
};

int main() {
    srand(time(0));

    int skor = 0;
    int jumlah = sizeof(negara) / sizeof(negara[0]);

    while (true) {
        string curr_negara = negara[rand() % jumlah];
        string jawaban;

        cout << "Tebak negara: ";

        for (char x : curr_negara) {
            if (rand() % 2)
                cout << x;
            else
                cout << "_";
        }

        cout << endl;

        cout << "Negara apakah yang dimaksud? ";
        cin >> jawaban;

        if (jawaban == curr_negara) {
            skor++;
            cout << "Selamat! Anda benar." << endl;
        } else {
            cout << "Maaf, jawaban Anda salah." << endl;
            cout << "Jawaban yang benar: " << curr_negara << endl;
        }

        cout << "Skor anda: " << skor << endl;

        cout << "\nIngin bermain lagi? (y/n) ";
        char play = getche();
        cout << endl;

        if (play == 'n' || play == 'N') break;
        cout << endl;
    }

    cout << "Game selesai! Skor akhir: " << skor << endl;
    return 0;
}
