#include <iostream>
#include <string>

using namespace std;

class KMP {

    void computeLPS(const string &needle, int lps[]) {
        int i = 1;
        int len = 0; // najduzi pronadjeni prefix == suffix
        lps[0] = 0;

        while (i < needle.length()) {
            if (needle[i] == needle[len]) { // ako smo našli par
                lps[i] = len + 1;
                len++;
                i++;
            } else { // mismatch znaka prefixa i sufixa
                // ovo je isto kao i u metodi search, ako smo imali neko podudaranje
                // podnizova tj. len!=0 onda moramo len pomaknuti
                if (len != 0)
                    len = lps[len - 1];
                else {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        cout << "LPS:";
        for (i = 0; i < needle.length(); i++)
            cout << " " << lps[i];
        cout << endl;
    }

public:
    int search(const string &haystack, const string &needle) {
        int n = haystack.length();
        int m = needle.length();

        int lps[m];
        computeLPS(needle, lps);

        int i = 0, j = 0; // i je index po haystacku, j po needle

        while (i < n) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
            }
            // ako nema podudaranja, trebamo vidjeti odakle u needle nastavljamo
            else {
                if (j != 0)
                    // ovo je najzanimljiviji dio
                    // u prošlom koraku smo pronašli neko podudaranje, sad treba vidjeti
                    // koliko znakova možemo preskočiti
                    // i se ne mijenja, on je na prvom znaku koji se ne podudara
                    // j ne treba ići od 0 nego gledamo koliki 
                    // prefix==suffix je na zadnjem znaku koji se podudarao
                    // i j postavimo na njega
                    j = lps[j - 1];
                else {
                    // inače samo povećam i za 1 i idem dalje
                    i++;
                }
            }
            // na kraju, ako je j==m onda sam matchao cijeli string
            if (j == m)
                return (i - m); // ili i-j
        }
        // ako sam došao do tu i nisam našao ništa
        return -1;
    }
};

int main() {
    string ulaz = "riba ribi grize rep";
    string uzorak1 = "ribi";

    KMP kmp;
    //cout << kmp.search(ulaz, uzorak1) << endl;
    cout << kmp.search("vodovodovodnog", "vodovodno") << endl;
    //cout << kmp.search("onionionspl", "onions") << endl;
    //cout << kmp.search("tapetapetari", "tapetar") << endl;
    //cout << kmp.search("AACAAAAAAAACAAAAACAAAACAAACAAAACACCA", "AACAAACAAAACA");
    return 0;
}