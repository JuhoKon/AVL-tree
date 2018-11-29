/*Juho Kontiainen */
/* Opiskelija numero: 0503209 */
/* pvmr 9.11.2018 */
#ifndef puu_included
#define puu_included
typedef struct puusolmu_t {
  int luku;
  short tila; /* tasapainoilmaisin */
  struct puusolmu_t *vasen, *oikea;
} puusolmu, *puuosoitin;
void lisaa_solmu(puuosoitin *, int, int *);
void vasen_kierto(puuosoitin *, int *);
void oikea_kierto(puuosoitin *, int *);
puuosoitin lisauspuuhun(puuosoitin ,Solmu *pAlku);
puuosoitin yksitlisaus(puuosoitin);
void tulosta_puu(puuosoitin);
void print2D(puuosoitin , int);
puuosoitin search(puuosoitin puu, int key);
void freememory(puuosoitin);
#endif /*puu.h*/
/* EOF */
