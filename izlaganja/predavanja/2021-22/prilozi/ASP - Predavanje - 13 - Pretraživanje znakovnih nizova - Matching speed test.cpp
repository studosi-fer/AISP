#include <bits/stdc++.h>
#include <cerrno>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string get_file_contents(const char *filename) {
  ifstream in(filename, std::ios::in | std::ios::binary);
  if (in) {
    string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  }
  throw(errno);
}

// složenost (n-m)*m ~ n*m
int search(const string &haystack, const string &needle) {
  // trebamo naći needle u haystacku
  int i, j;
  int n = haystack.length();
  int m = needle.length();
  for (i = 0; i <= n - m; i++) { // pazi, ide <=
    for (j = 0; (j < m) && (haystack[i + j] == needle[j]); j++)
      ;
    if (j == m) // ako se unutarnji for vrtio za sve znakova
      return i;
  }
  return -1;
}

class HashArraySearch {
private:
  const string &haystack;
  int *testhash; // pokazivač na polje hasheva
  int n;         // duljina haystacka
  int m;         // duljina needle-a
  int gethash1(const string &s) {
    hash<string> hasher;
    return hasher(s);
  }

public:
  // ovo nije pravi RK, ovaj algoritam se i dalje izvodi u ~O(n*m)
  // prednost: računanje hasheva možemo izdvojiti u posebnu fju i napraviti samo
  // jednom (košta nas prostora i O(n) vremena) kad jednom izračunamo hasheve,
  // za sve sljedeće pretrage algoritam radi u O(n+m), ako je hashing fja dobra
  // mana: radi samo za pretrage za strigovima iste duljine (za njih smo
  // izračunali hash)

  HashArraySearch(const string &hstack, int needleLength) : haystack(hstack) {
    n = haystack.length();
    m = needleLength;

    testhash = new int[haystack.length() - m + 1];

    for (int i = 0; i <= n - needleLength; i++) {
      testhash[i] = gethash1(haystack.substr(i, m));
    }
  }

  int search(const string &needle) {

    int needlehash = gethash1(needle);

    // traženje
    for (int i = 0; i <= n - m; i++)
      if (needlehash == testhash[i]) {
        // ako su hashevi isti, velika je šansa da imamo match
        int j;
        for (j = 0; (j < m) && (haystack[i + j] == needle[j]); j++)
          ;
        if (j == m) // ako se unutarnji for vrtio za sve znakova
          return i;
      }
    return -1;
  }
};

class RabinKarp {
private:
  // magični brojevi:
  int base = 256;
  int prime = 251;
  int firstDigitBase;

  // izračunamo potenciju baze prvog znaka
  void calculateFirstDigitBase(int needlelength) {
    firstDigitBase = 1;
    for (int i = 0; i < needlelength - 1; i++)
      firstDigitBase = (firstDigitBase * base) % prime;
  }

  int gethash(const string &s) {
    int hash = 0;
    // ovo će na kraju generirati baza^n * prvi znak + baza^n-1 * drugi znak...
    for (int i = 0; i < s.length(); i++)
      hash = (base * hash + s[i]) % prime;
    return hash;
  }

  int rehash(int oldhash, char leadingChar, char newChar) {
    // maknemo hash prvog znaka i dodamo hash "novog zadnjeg"
    int newhash = oldhash - leadingChar * firstDigitBase; // makni prvi znak
    // pomnožimo ovo što imamo s bazom i dodamo zadnji znak
    newhash = ((newhash * base) + newChar) % prime;
    // moguće da je u množenju ili zbrajanju došlo do prelaska preko maxint
    if (newhash < 0)
      newhash += prime;
    return newhash;
  }

public:
  // ovo je već bolje
  int search(const string &haystack, const string &needle) {
    // ideja: sažetak ("riba") koristi slične znakove kao sažetak ("iba ")
    // tj. izbacimo prvo slovo i dodamo na kraj jedno novo
    // prva ideja:
    // hash("riba") = hash(r) + hash(i) + hash(b) + hash(a)
    // hash("iba ") = hash("riba") - hash(r) + hash(" ")
    // međutim, ovako je hash("riba") == hash("bira") i svih drugih permutacija
    // bolja ideja: dodijelim "težine" svakom mjestu -> težina == BAZA
    // npr. za 4 znaka: (težine su potencije broja 2)
    // hash("riba") = 8*hash(r) + 4*hash(i) + 2*hash(b) + 1*hash(a)
    // hash("iba ") = (hash("riba") - 8*hash(r) ) * 2 + hash(" ")
    // implementacija: BAZA: 256 (jer su znakovi 8-bitni)
    //                  "hash" znaka je njegova ascii vrijednost

    int n = haystack.length();
    int m = needle.length();

    calculateFirstDigitBase(m);

    int t =
        gethash(haystack.substr(0, m)); // haystack hash prvih m znakova (test)
    int p = gethash(needle);            // needle hash (pattern)

    // cout << "needle hash: " << p << endl;

    // traženje
    for (int i = 0; i <= n - m; i++) {
      // cout << "haystack[" << i << "]: " << t << endl;
      if (t == p) {
        // ako su hashevi isti, velika je šansa da imamo match
        int j;
        for (j = 0; (j < m) && (haystack[i + j] == needle[j]); j++)
          ;
        if (j == m) // ako se unutarnji for vrtio za sve znakova
          return i;
      }
      t = rehash(t, haystack[i], haystack[i + m]);
    }
    return -1;
  }
};

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

    /*cout << "LPS:";
    for (i=0; i < needle.length(); i++)
        cout << " " << lps[i];
    cout << endl;*/
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
      // ako nema podudaranja, trebamo vidjeti odakle u haystacku nastavljamo
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

#define d 256
int searchRK(const char pat[], const char txt[], int q) {
  int M = strlen(pat);
  int N = strlen(txt);
  int i, j;
  int p = 0; // hash value for pattern
  int t = 0; // hash value for txt
  int h = 1;

  // The value of h would be "pow(d, M-1)%q"
  for (i = 0; i < M - 1; i++)
    h = (h * d) % q;

  // Calculate the hash value of pattern and first
  // window of text
  for (i = 0; i < M; i++) {
    p = (d * p + pat[i]) % q;
    t = (d * t + txt[i]) % q;
  }

  // Slide the pattern over text one by one
  for (i = 0; i <= N - M; i++) {

    // Check the hash values of current window of text
    // and pattern. If the hash values match then only
    // check for characters on by one
    if (p == t) {
      /* Check for characters one by one */
      for (j = 0; j < M; j++) {
        if (txt[i + j] != pat[j])
          break;
      }

      // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
      if (j == M)
        return i;
    }

    // Calculate hash value for next window of text: Remove
    // leading digit, add trailing digit
    if (i < N - M) {
      t = (d * (t - txt[i] * h) + txt[i + M]) % q;

      // We might get negative value of t, converting it
      // to positive
      if (t < 0)
        t = (t + q);
    }
  }
  return -1;
}

int main() {
  int index;

  // Stvarni podaci - Biblija (s Project Gutenberg)
  //string ulaz = get_file_contents("kingjamesbible.txt"); // cca 4.5MB
  //string uzorak = "In the beginning was the Word";

  // txt datoteka od 5MB slova a i na kraju jedno b :) Tražimo baš takav podniz
  string ulaz = get_file_contents("aaaaaaab.txt"); // cca 5MB
  string uzorak = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";

  using namespace std::chrono;
  steady_clock::time_point begin;
  steady_clock::time_point end;

  // Brute force
  begin = steady_clock::now();
  index = search(ulaz, uzorak);
  end = steady_clock::now();
  cout << "(" << index
       << ") Brute force = " << duration_cast<milliseconds>(end - begin).count()
       << "ms" << endl;

  // array of hashes
  begin = steady_clock::now();
  HashArraySearch hs(ulaz, uzorak.length());
  index = hs.search(uzorak);
  end = steady_clock::now();
  cout << "(" << index << ") Array of hashes 1st = "
       << duration_cast<milliseconds>(end - begin).count() << "ms" << endl;

  // array of hashes - opet ali sam već imamo stvoreno polje
  // možemo poslati i drugi string za pretragu, ali mora biti iste duljine!
  begin = steady_clock::now();
  index = hs.search(uzorak);
  end = steady_clock::now();
  cout << "(" << index << ") Array of hashes repeated = "
       << duration_cast<milliseconds>(end - begin).count() << "ms" << endl;

  // RK
  RabinKarp rk;
  begin = steady_clock::now();
  index = rk.search(ulaz, uzorak);
  end = steady_clock::now();
  cout << "(" << index
       << ") Rabin Karp = " << duration_cast<milliseconds>(end - begin).count()
       << "ms" << endl;

  // RK2 - radi s poljima i dijeli s potencijom broja 2, a ne s prostim brojem
  KMP kmp;
  begin = steady_clock::now();
  index = searchRK(uzorak.c_str(), ulaz.c_str(), 1024); // suprotno preporuci
  end = steady_clock::now();
  cout << "(" << index << ") Rabin Karp #2 = "
       << duration_cast<milliseconds>(end - begin).count() << "ms" << endl;

  // KMP
  begin = steady_clock::now();
  index = kmp.search(ulaz, uzorak);
  end = steady_clock::now();
  cout << "(" << index << ") Knuth Morris Pratt = "
       << duration_cast<milliseconds>(end - begin).count() << "ms" << endl;

  return 0;
}