#include <cstring>
#include <iostream>
#include <list>
using namespace std;

struct Zapis {
   char oib[11 + 1];
   char prezime[14 + 1];
};

#define N 350
#define BLOK 512
#define C (BLOK / sizeof(Zapis)) // 18
#define M (int)(N * 1.3 / C)     // 25
#define PRIME 23                 // 23

class HashInFile {
 private:
   FILE *ft;
   Zapis row[C];

   int getAdress(char OIB[]) {
      // lijen sam :)
      hash<string> hasher;
      cout << "adresa:" << (hasher(OIB) % PRIME) << endl;
      return hasher(OIB) % PRIME;
   }

 public:
   HashInFile(const char *fileName) {
      if ((ft = fopen(fileName, "w+")) == NULL) {
         cout << "File open failed" << endl;
         exit(1);
      }
   }
   ~HashInFile() { fclose(ft); }

   int addElement(Zapis inputRecord) {
      int i, j, start;
      cout << "Spremam zapis: {" << inputRecord.oib << "," << inputRecord.prezime << "} ";
      i = start = getAdress(inputRecord.oib);
      do { // ponavljaj dok ne dodamo zapis u file
         // čitaj sve zapise iz retka / "pretinca"
         // na početka bloka
         fseek(ft, i * BLOK, SEEK_SET);
         // pročitaj sve elemente u polje
         fread(row, sizeof(row), 1, ft);
         for (j = 0; j < C; j++) {
            if (row[j].oib[0] != '\0') {
               // tu već postoji zapis
               std::cout << "Postoji zapis na poziciji " << j << ": {" << row[j].oib << "," << row[j].prezime << "}" << endl;
               if (strncmp(row[j].oib, inputRecord.oib, 11) == 0) {
                  // isti oib
                  std::cout << "Isti oib: " << inputRecord.oib << endl;
                  return 1;
               }
            } else {
               // spremi zapis
               row[j] = inputRecord;
               fseek(ft, i * BLOK, SEEK_SET);
               std::cout << "Red " << i << " - spremam na poziciju " << j << endl;
               fwrite(row, sizeof(row), 1, ft);
               return 1;
            }
         }
         // Ako je redak pun, idemo na sljedeći
         i = (i + 1) % M;
         std::cout << "Nema mjesta, sljedeci red = " << i;
      } while (i != start); // Dok ne pročitamo ciklički cijelu datoteku
      return 0;             // nema mjesta
   }

   void clear() {
      int i;
      for (i = 0; i < C; i++)
         row[i].oib[0] = '\0';
      for (i = 0; i < M; i++) {
         fseek(ft, i * BLOK, SEEK_SET);
         fwrite(row, sizeof(row), 1, ft);
      }
   }

   void print() {
      // ispiši cijelu hash tablicu
      int i, j;
      std::cout << "Datoteka: \n";
      for (i = 0; i < M; i++) {
         fseek(ft, i * BLOK, SEEK_SET);
         fread(row, sizeof(row), 1, ft);
         for (j = 0; j < C; j++) {
            if (row[j].oib[0] != '\0') {
               std::cout << "Redak:" << i << ", zapis: " << j << ": ";               
               std::cout << row[j].oib << " " << row[j].prezime << "\n";
            }
         }
      }
   }
};

int main() {

   HashInFile h = HashInFile("hashFile.bin");
   h.clear();

   Zapis z1 = {"4573287451", "Mirko"};
   h.addElement(z1);

   Zapis z2 = {"1234567890", "Slavko"};
   h.addElement(z2);

   Zapis z3 = {"4873534671", "Jela"};
   h.addElement(z3);

   Zapis z4 = {"1174514474", "Ante"};
   h.addElement(z4);   

   Zapis z5 = {"2174538400", "Bara"};
   h.addElement(z5);   

   h.print();

   return 0;
}