/*Juho Kontiainen */
/* Opiskelija numero: 0503209 */
/* pvmr 9.11.2018 */
/*Sisältää tiedoston lukemisen, sekä siihen liittyvät asiat */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiedosto.h"
Solmu* tdstoluku(Solmu *pAlku) {
  char nimi[100], muisti[121];
  printf("Anna luettavan tiedoston nimi: ");
  scanf("%s", nimi);
  
  if (pAlku != NULL) {
    /* Muistin vapauttaminen */
    printf("Poistetaan aiemmat tiedot ja luetaan uudet.\n");
    pAlku = tyhjenna(pAlku);
  }
  Solmu *ptr, *ptrUusi;
  
  FILE *tiedosto;
  if ((tiedosto = fopen(nimi, "r")) == NULL) {
    perror("Tiedoston avaaminen ep�onnistui.");
    exit(1);
  }
  printf("Luetaan tiedosto %s.\n", nimi);
  
  /* Rivi rivilt� luku */
  while (fgets(muisti,120,tiedosto)) {
    
    /* Muistin varaus */	
    if ((ptrUusi=(Solmu*)malloc(sizeof(Solmu))) == NULL) {
      printf("Muistin varaus ep�onnistui.");
      exit(1);
    }
    /* SOLMUN ALUSTUS */
    ptrUusi->luku = atoi(strtok(muisti, "\n"));
    ptrUusi->pNext = NULL;
    
    /*UUDEN ALKION LIS�YS LISTAAN*/
    
    if (pAlku == NULL) {
      pAlku = ptrUusi;
    } else { 
      ptr = pAlku;
      while (ptr->pNext != NULL)
	ptr = ptr->pNext;
      ptr->pNext = ptrUusi;
    }	
  }
  printf("Tiedosto %s luettu.\n", nimi);
  fclose(tiedosto);
  return pAlku;
}
void tulostalista(Solmu *pAlku) {
  Solmu *ptr = pAlku;
  if (ptr == NULL) {
    printf("Lista on tyhjä.\n");
  } else {
    printf("Listassa on seuraavat tiedot.\n");
    while (ptr != NULL) {
      printf("%d\n", ptr->luku);
      ptr = ptr->pNext;
    }
  }
}
Solmu* tyhjenna(Solmu *pAlku) {
  /* Muistin vapautus */
  Solmu *ptr = pAlku;
  while (ptr!= NULL) {
    pAlku = ptr->pNext;
    free(ptr);
    ptr = pAlku;
  }	
  
  return pAlku;
}
