#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include <string.h>

FILE * fichier;
int rouge, bleu, vert, x, y, a, b;
int i=0,j =0;

  SDL_Surface* affichage;
  void initSDL(int n);
  void attendreTouche(void);
  void setPixel(int x, int y, Uint32 coul);
  void actualiser(void);

int main(int argc, char *argv[])
{
  int n = atoi(argv[2]);
//********************************************************Test d'ouverture*******************************************************************
  if(argc!=3)
  {
    printf("Entrez un argument\n");
    return EXIT_FAILURE;
  }
  
  fichier=fopen(argv[1], "r");
  
  if(fichier==NULL)
  {
    printf("Erreur à l'ouverture du fichier\n");
    return EXIT_FAILURE;
  }
  
//******************************************************Lecture du fichier .bin**************************************************************
  
/*Ce programme fonctionne comme un "curseur" qui parcourerait l'écran ligne par ligne, et y insérait un pixel à chaque étape de son parcours.
 *Dans l'ordre,avec la boucle1 le curseur va parcourir l'axe horizontal entre la dernière valeur connue de x et x+n en y créant un pixel à 
 * chaque tour de boucle. Une fois cette boucle finie, la boucle2 va s'incrémenter afin de parcourir la prochaine ligne de l'axe x, on recommence 
 * donc la boucle1. Les boucle3 et 4 sont des boucles classiques pour parcourir l'écran lignes par lignes  
  
*/
  fgetc(fichier);				//Ces deux lignes servent à lire les deux premiers octets du fichier
  fgetc(fichier);				//car ils ne contiennent pas d'informations sur les pixels

  initSDL(n);					
   for(y=0; y<128*n; y++)			//Boucle4. Cette boucle sert à parcourir l'axe des y
    {										
      for(x=0; x<128*n ; x++)			//Boucle3. Cette boucle sert à parcourir l'axe des x 
      {	
	rouge=fgetc(fichier);			//				
	vert=fgetc(fichier);			//Ces trois lignes servent à lire dans le fichier les valeur des couleurs de pixels
	bleu=fgetc(fichier);			//
	
	    for(j=y;j<y+n;j++)			//Boucle2. Cette boucle sert à parcourir l'axe des y entre la dernière valeur connue de y et ce même y +n
	    {
	      for(i=x; i<x+n;i++)		//Boucle1.Cette boucle sert à parcourir l'axe des x entre la dernière valeur connue de x et ce même x +n
						
	      {									
		setPixel(i, j, SDL_MapRGB(affichage->format, rouge, vert, bleu));	//On y crée un pixel à chaque tour de cette boucle
	      }	
	    }
	  x=x+n-1;
      }
	
y=y+n-1;
    }    
//*******************************************************************************************************************************************
  fclose(fichier);
  actualiser();
  attendreTouche();
  
  return EXIT_SUCCESS;
    
}

  void initSDL(int n){
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    atexit(SDL_Quit);
    affichage = SDL_SetVideoMode(128*n, 128*n, 32, SDL_SWSURFACE);

    if (affichage == NULL) {
      fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
      SDL_WM_SetCaption("Viewer P6", NULL);
  }

  void attendreTouche(void) {
    SDL_Event event;
    do
      SDL_WaitEvent(&event);
    while (event.type != SDL_QUIT && event.type != SDL_KEYDOWN);
  }
  
  void setPixel(int x, int y, Uint32 coul){
    *((Uint32*)(affichage->pixels) + x + y * affichage->w) = coul;
  }

  void actualiser(void){
    SDL_UpdateRect(affichage, 0, 0, 0, 0);
  }
    