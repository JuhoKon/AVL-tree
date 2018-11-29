/*Juho Kontiainen */
/* Opiskelija numero: 0503209 */
/* pvmr 9.11.2018 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiedosto.h"
#include "puu.h"
/* Valikko */
int valikko() {
  int valinta;
  printf("\n1) Lue tiedostosta avaimet\n");
  printf("2) Tulosta tiedostossa olevat tiedot\n");
  printf("3) Lisää luetut avaimet puuhun\n");
  printf("4) Lisää omia avaimia puuhun\n");
  printf("5) Tulosta puurakenne\n");
  printf("6) Tyhjennä puu\n");
  printf("7) Hae avainta puusta\n");
  printf("8) Avaimien määrällinen lisäys\n");
  printf("0) Lopeta\n");
  printf("Anna valintasi: ");
  if(1 == scanf("%d", &valinta)) {
    return valinta;
  } else {
    printf("Väärä syöte.\n");
    return 0;
  }
  printf("\n");
}

int main() {
  int valinta = 1,avain;
  puuosoitin puu = NULL;
	puuosoitin puu2 = NULL;
  int a,lkmr,etp =0;
  Solmu *pAlku = NULL;	
  while (valinta !=0) {;
    valinta = valikko();
    if (valinta == 0) {
    } else if (valinta == 1) {	
      pAlku = tdstoluku(pAlku);
    } else if (valinta == 2) {
      tulostalista(pAlku);
    } else if (valinta == 3) {
      puu =lisauspuuhun(puu,pAlku); /* lisäys tapahtuu lukemalla lista, joka on tehty tiedostosta. */
    } else if (valinta == 4) {
      puu = yksitlisaus(puu);      /* lisäys käyttäjän syötteestä */ 	
    } else if (valinta == 5) {
      tulosta_puu(puu);
      print2D(puu,0);
    } else if (valinta == 6) {
      freememory(puu);
      puu = NULL;
      printf("Puu tyhjennetty.\n");
    } else if (valinta == 7) {
      printf("Anna etsittävä avain: ");
      scanf("%d", &avain);
      if((puu2=search(puu,avain)) == NULL) { /*palauttaa NULL, jos avainta ei löydy. */
	printf("Avainta ei löytynyt.\n");
      } else {
	printf("Avain %d löytyi.\n",puu2->luku);
	
      }
    } else if (valinta == 8){ /*Testausta varten */
      
      printf("Kuinka paljon tahdot avaimia lisätä puuhun: ");
      scanf("%d",&lkmr);
      for (a=1; a<=lkmr; a++) {
	lisaa_solmu(&puu, a, &etp);
      }
      
    } else {
      printf("Väärä syöte.\n");
    }	
  }
  if (puu != NULL) {
    freememory(puu);
  }

  pAlku = tyhjenna(pAlku);
	printf("Kiitos ohjelman käytöstä!\n");
  return 0;
}
/* EOF */
