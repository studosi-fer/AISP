#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct s {
  long  maticniBroj;
  char  imePrezime[24+1];
  int   sifraPredmet;
  short ocjena;
};
typedef struct s zapis; 

int fatal(char *poruka) {
  puts(poruka);
  exit(1);
}
int stavi(zapis *stavka, long *vrh, FILE *f) {
  // zapisi na kraj
  if (*vrh <= 0) {
    if (fseek(f, sizeof(*vrh), SEEK_SET)) return 0; 
  } else {
    if (fseek(f, *vrh+sizeof(*stavka), SEEK_SET)) return 0;
    // da nema skini ...
    // if (fseek(f, 0l, SEEK_END)) return 0;
  }
  fwrite(stavka, sizeof(*stavka), 1, f);    
  *vrh = ftell(f) - sizeof(zapis); 
  return 1;
}

int skini(zapis *stavka, long *vrh, FILE *f) {
  // ako se ne moze pozicionirati (vrh < 0)
  // u datoteci, znaci da je stog prazan
  if (fseek(f, *vrh, SEEK_SET)) return 0;
  
  // procitaj zapis s kraja datoteke, tj. s vrha stoga
  fread(stavka, sizeof(*stavka), 1, f);    
  *vrh -= sizeof(zapis);
  return 1;
}

void stog () {
  FILE *f;
  long vrh = -1L;
  int i;
  zapis z;

  srand((unsigned) time(NULL));

  if ((f = fopen("stog.dat", "r+b")) == NULL) 
    if ((f = fopen("stog.dat", "w+b")) == NULL) 
      fatal("Datoteka se ne moze otvoriti!");
  // prvo procitaj adresu zadnjeg
  fread(&vrh, sizeof(vrh), 1, f);
  // isprazni stog i ispisi sve podatke 
  while (skini(&z, &vrh, f)) {
    printf("%ld %s %d %d\n", 
              z.maticniBroj, z.imePrezime, 
              z.sifraPredmet, z.ocjena);
  }   
  // nakon sto procitas sve zapise,
  // malo stavi malo skini
  strcpy (z.imePrezime, "Hrvoje Horvat");
  for (i = 1; i <= 20; ++i) {
    if (rand() % 2) {
      z.maticniBroj = rand() % 1024;
      z.ocjena = rand() % 5 + 1;
      z.sifraPredmet = rand() % 100;
      if (!stavi(&z, &vrh, f))
        printf("stavi %ld\n", z.maticniBroj); 
    } else if (skini(&z, &vrh, f)) {
        printf("skini %ld\n", z.maticniBroj); 
    } else {
        printf("stavi/skini neuspješan\n");
    }
  }

  // zapisi na pocetak datoteke novu adresu zadnjeg zapisa
  fseek(f, 0L, SEEK_SET); // ILI: rewind(f);
  fwrite(&vrh, sizeof(vrh), 1, f);
  fclose(f);
  return;
}

int main() {
  stog();
  return 0;
}