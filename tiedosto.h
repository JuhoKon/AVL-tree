/*Juho Kontiainen */
/* Opiskelija numero: 0503209 */
/* pvmr 9.11.2018 */
#ifndef tiedosto_included
#define tiedosto_included
struct Node {
	int luku;
	struct Node *pNext;
};
typedef struct Node Solmu;
Solmu* tdstoluku(Solmu *pAlku);
void tulostalista(Solmu *pAlku);
Solmu* tyhjenna(Solmu *pAlku);
#endif /*tiedosto.h*/
/* EOF */
