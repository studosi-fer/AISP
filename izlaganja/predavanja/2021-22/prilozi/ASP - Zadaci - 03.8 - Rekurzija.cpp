#include <iostream>

using namespace std;

int provjeriZagrade(char *niz, int *zastavica){
    if (*niz == '\0'){
        return (*zastavica == 0 ? 1 : 0);
    }else{
        if (*niz == '[')
            (*zastavica)++;
        else if (*niz == ']')
            (*zastavica)--;

        return provjeriZagrade(niz + 1, zastavica);
    }
}

int main (void){
    char testStr1[] = "[]";
    char testStr2[] = "][";
    char testStr3[] = "[[]";
    char testStr4[] = "asda[[sad saddadw ][ asda]] ";
    char testStr5[] = "asda[[sad saddadw ][ asda]] [";

    int zastavica = 0;

    cout << "Zagrade potpune: " << (provjeriZagrade(testStr5, &zastavica) ? "TRUE" : "FALSE") << endl;

    return 0;
}