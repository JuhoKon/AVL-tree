/*Juho Kontiainen */
/* Opiskelija numero: 0503209 */
/* pvmr 9.11.2018 */
/*sisältää puun rakentamisen ja muut puuhun liittyvät toimenpiteet */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiedosto.h"
#include "puu.h"
void lisaa_solmu(puuosoitin *emo, int luku, int *etp) {

  if((*emo) == NULL) {  /*liikutaan niin pitkälle solmussa, että löydetään vasen/oikea vapaa (riippuen luvusta) */
    *etp = 1;					/* kun löydetään, niin *etp annetaan arvo 1 */
    if((*emo = (puuosoitin)malloc(sizeof(puusolmu))) == NULL) {
      
      perror("malloc");
      exit(1);
    }
    (*emo)->vasen = (*emo)->oikea = NULL;
    (*emo)->tila = 0;
    (*emo)->luku = luku;
  } else if(luku < (*emo)->luku) {
    
    lisaa_solmu(&(*emo)->vasen, luku, etp); 
    if(*etp != 0) { /* jos ollaan onnistuneesti luotu uusi node, *etp=1 eli !=0 -> päästään switch rakenteeseen, jossa vaihdetaan emon 											tilaa */
      
      switch((*emo)->tila) {		/*tarkastellaan EMON tilaa, eli sitä solmua mihin lisätään uusi */
	
      case -1:			
	(*emo)->tila = 0; /*lisättiin vasemmalle, joten +1, näin ollen tilaksi tulee 0 */
	*etp = 0; /*tasapainossa, joten vaihdetaan etp = 0, ei tarvitse enää käydä läpi. */
	break;
      case 0:
	(*emo)->tila = 1;		/* lisättiin vasemmalle, joten +1, tilanne oli sellainen , että k.o solmu oli tasapainossa. */ 											
	break;
      case 1:
	printf("Epätasapaino kohdattu avaimessa %d, puun rakenne epätasapainokohdasta ennen vasempaa kiertoa:\n",(*emo)->luku);
	print2D(*emo,0);
	vasen_kierto(emo, etp);	/*lisättiin vasemmalle, jonka seurauksena epätasapainossa, joten tehdään vasenkierto. */
      }
    }
  } else if(luku > (*emo)->luku) {
    
    lisaa_solmu(&(*emo)->oikea, luku, etp);
    
    if(*etp != 0) {
      
      switch((*emo)->tila) {
	
      case 1:
	(*emo)->tila = 0;
	*etp = 0;
	break;
      case 0:
	(*emo)->tila = -1;
	break;
      case -1:
	printf("Epätasapaino kohdattu avaimessa %d, puun rakenne epätasapainokohdasta ennen oikeaa kiertoa:\n",(*emo)->luku);
	print2D(*emo,0);
	oikea_kierto(emo, etp);
      }
    }
  } else {
    *etp = 0;
    printf("Luku %d on jo puussa\n", luku);
  }
}
void vasen_kierto(puuosoitin *emo, int *etp) {
  
  puuosoitin lapsi, lapsenlapsi;

  lapsi = (*emo)->vasen;
  if(lapsi->tila == 1) {  /* LL-kierto */
    printf("Tehdään LL-kierto.. Epätasapaino havaittu.\n");
    (*emo)->vasen = lapsi->oikea;
    lapsi->oikea = *emo;
    (*emo)->tila = 0;
    (*emo) = lapsi;
    
  } else { /* LR-kierto */
    lapsenlapsi = lapsi->oikea;
    printf("Tehdään LR-kierto. Epätasapaino havaittu.\n");
    lapsi->oikea = lapsenlapsi->vasen;
    lapsenlapsi->vasen = lapsi;
    (*emo)->vasen = lapsenlapsi->oikea;
    lapsenlapsi->oikea = *emo;
    switch(lapsenlapsi->tila) {
    case 1:
      (*emo)->tila = -1;
      lapsi->tila = 0;
      break;
    case 0:
      (*emo)->tila = lapsi->tila = 0;
      break;
    case -1:
      (*emo)->tila = 0;
      lapsi->tila = 1;
    }
    *emo = lapsenlapsi;
  }
  (*emo)->tila = 0;
  *etp = 0;
}
void oikea_kierto(puuosoitin *emo, int *etp) {
  puuosoitin lapsi, lapsenlapsi;
  lapsi = (*emo)->oikea;
  if(lapsi->tila == -1) { /* RR-kierto */
    printf("Tehdään RR-kierto.. Epätasapaino havaittu.\n");
    (*emo)->oikea = lapsi->vasen;
    lapsi->vasen = *emo;
    (*emo)->tila = 0;
    (*emo) = lapsi;
  } else { /* RL-kierto */
    lapsenlapsi = lapsi->vasen;
    printf("Tehdään RL-kierto.. Epätasapaino havaittu.\n");
    lapsi->vasen = lapsenlapsi->oikea;
    lapsenlapsi->oikea = lapsi;
    (*emo)->oikea = lapsenlapsi->vasen;
    lapsenlapsi->vasen = *emo;
    
    switch(lapsenlapsi->tila) {
    case -1:
      (*emo)->tila = 1;
      lapsi->tila = 0;
      break;
    case 0:
      (*emo)->tila = lapsi->tila = 0;
      break;
    case 1:
      (*emo)->tila = 0;
      lapsi->tila = -1;
    }
    *emo = lapsenlapsi;
  }
  (*emo)->tila = 0;
  *etp = 0;
}
puuosoitin lisauspuuhun(puuosoitin puu,Solmu *pAlku) {
  int etp = 0;
  Solmu *ptr = pAlku;
  if (ptr == NULL) {
    printf("Lista on tyhjä.\n");
  } else {
    printf("Lisätään avaimet puuhun.\n");
    getchar();
    while (ptr != NULL) {
      printf("Lisää seuraava tiedostosta löytyvä avain (%d) puuhun painamalla ENTER...\n",ptr->luku);
      getchar(); 
      lisaa_solmu(&puu, ptr->luku, &etp);
      printf("Puun avaimet sekä tasapainot:\n");
      tulosta_puu(puu);  /*tasapainojen tulostus*/ 
      printf("\n\n");
      printf("Puun rakenne:\n");
      print2D(puu,0);		/*itse puun tulostus */
      printf("\n\n");
      ptr = ptr->pNext;
    }
  }
  return puu;
}
puuosoitin yksitlisaus(puuosoitin puu) {
  int i = 1,etp =0;
  while (i != 0) { 				/* toistorakenne avaimien lisäämiseen yksikerrallaan puuhun */ 
    printf("Anna lisättävät avaimet puuhun (0 lopettaa):");
    if (scanf("%d",&i) == 1) {
		  if (i == 0) { 
		    break;
			}
		  printf("\n\n");
		  lisaa_solmu(&puu,i,&etp); /* puuhun lisäys */
		  /*info tulostuksia*/
		  printf("Puun avaimet sekä tasapainot:\n");
		  tulosta_puu(puu);  /*tasapainojen tulostus */
		  printf("\n\n");
		  printf("Puun tasapainotettu rakenne:\n");
		  print2D(puu,0);		/*itse puun tulostus */
		  printf("\n\n");
		  printf("--------------------------------------------------------------------\n");
		} else {
			printf("Väärä syöte.\n");
			exit(1);
		}	
  }
  return puu;
}
void tulosta_puu(puuosoitin solmu) {
  
  if(solmu == NULL) {
    return;
  }
  printf("%d ja tasapaino %d\n", solmu->luku,solmu->tila);
  tulosta_puu(solmu->vasen);
  tulosta_puu(solmu->oikea);
}
void print2D(puuosoitin ptr, int wspace) { /* LÄHDE https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/ */
  
  int k=11,i; /*base case */
  
  if (ptr == NULL) {
    return;
  }
  /* lisätään etäisyyttä tasojen välille */
  
  wspace += k;
  /*oikean puolen lapsi ensin */
  
  print2D(ptr->oikea, wspace);
  
  printf("\n");
  for (i = k; i < wspace; i++) {	/* tulostetaan nykyinen node wspacen jälkeen (välilyöntejä) */
    printf(" ");
  }
  printf("%d\n", ptr->luku);
  /* vasemman puolen lapsi */
  print2D(ptr->vasen, wspace);
}
puuosoitin search(puuosoitin puu, int key) { /*Koodin lähde https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/ */
  /* solmu on NULL tai avain löytyy */
  if (puu == NULL || puu->luku == key) {
    return puu; 
  }
  /* Avain on isompi kuin solmun avain */
  if (puu->luku < key) {
    return search(puu->oikea, key); 
  } 
  /* avain on pienempi kuin solmun avain */
  return search(puu->vasen, key); 
} 
void freememory(puuosoitin solmu) { /*puurakenteen muistin vapautus */
  if(solmu == NULL) {
    return;
  }
  freememory(solmu->vasen);
  freememory(solmu->oikea);
  free(solmu);
}
