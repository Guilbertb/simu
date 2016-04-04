#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include <string.h>

FILE * fichier;
int rouge, bleu, vert, x, y;
char chaine[10000];

  SDL_Surface* affichage;
  void initSDL(void);
  void attendreTouche(void);
  void setPixel(int x, int y, Uint32 coul);
  void actualiser(void);

int main(int argc, char *argv[])
{
  if(argc!=2)
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
  
  fgetc(fichier);
  fgetc(fichier);

  initSDL();
  
  
    /* lecture d'un pixel */
    for(y=0; y<128; y++)
    {
      for(x=0; x <128 ; x++)
      {
	
	rouge=fgetc(fichier);
	vert=fgetc(fichier);
	bleu=fgetc(fichier);
	setPixel(x, y, SDL_MapRGB(affichage->format, rouge, vert, bleu));
      }
    }
  fclose(fichier);
  actualiser();
  attendreTouche();
  
  return EXIT_SUCCESS;
    
}

  void initSDL(void){
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    atexit(SDL_Quit);
    affichage = SDL_SetVideoMode(128, 128, 32, SDL_SWSURFACE);

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
    
    
  