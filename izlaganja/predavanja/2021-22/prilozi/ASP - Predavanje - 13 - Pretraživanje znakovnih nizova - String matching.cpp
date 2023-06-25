#include <iostream>
#include<string>

using namespace std;

int search(const string &haystack, const string &needle) {
    int i, j;
    int n = haystack.length();
    int m = needle.length();
    for (i=0; i <= n-m; i++) {
        for (j=0; (j<m) && (haystack[i+j] == needle[j]); j++)
            ;
        if (j == m)
            return i;
    }
    return -1;
}

int gethash1(const string &s) {
    hash<string> hasher;
    return hasher(s);
}

int rk1(const string &haystack, const string &needle) {
    int n = haystack.length();
    int m = needle.length();
    int testhash[n-m+1];
    int needlehash = gethash1(needle); 
    cout << "needlehash: " << needlehash << endl;

    //priprema
    cout << "testhash:";
    for (int i =0; i<=n-m; i++) {
        testhash[i] = gethash1(haystack.substr(i,m));
        cout << " " << testhash[i];
    }
    cout << endl;

    //trazenje
    for (int i=0; i <= n-m; i++) {
        if (needlehash == testhash[i]) {
            int j;
            for (j=0; (j<m) && (haystack[i+j] == needle[j]); j++)
                ;
            if (j == m)
                return i;
        }
    }
    return -1;
}

class RabinKarp {
private:
    int base = 256;
    int prime = 251;
    int firstCharBase = 1;

    void calculateFirstCharBase(int needleLen) {
        for (int i=0; i<needleLen-1; i++)
            firstCharBase = (firstCharBase*base) % prime;
    }

    int gethash(const string &s) {
        int hash = 0;
        for (int i=0; i< s.length(); i++)
            hash = (hash * base + s[i]) % prime;
        return hash;
    }

    int rehash(int oldhash, char leadingChar, char newChar) {
        //maknemo prvi znak i dodamo novi
        int newhash = oldhash - (leadingChar * firstCharBase);
        newhash = ((newhash * base) + newChar) % prime;
        if (newhash < 0) newhash += prime;
        return newhash;
    }

public:
    int search(const string &haystack, const string &needle){
        int n = haystack.length();
        int m = needle.length();

        calculateFirstCharBase(m);

        int t = gethash(haystack.substr(0,m));
        int p = gethash(needle);

        cout << "needle hash: " << p << endl;

        //search
        for (int i=0; i<=n-m; i++) {
            cout << "haystack[" << i << "]: " << t << endl;
            if (t == p) {
                //našao sam isti hash
                int j;
                for (j=0; (j<m) && (haystack[i+j] == needle[j]); j++)
                    ;
                if (j == m)
                    return i;  
            }
            t = rehash(t, haystack[i], haystack[i+m]);
        }
        return -1;
    }

};


int main() {

    string ulaz = "riba ribi grize rep";
    string uzorak = "ribi";

    //cout << search(ulaz, uzorak) << endl;
    //cout << search(ulaz, "ewrewrew") << endl;

    //cout << rk1(ulaz, uzorak) << endl;

    RabinKarp rk;
    cout << rk.search(ulaz, uzorak) << endl;

    return 0;
}