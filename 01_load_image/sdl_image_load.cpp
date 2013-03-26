#include <SDL/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

	SDL_Surface* textImg = NULL;
	SDL_Surface* bgSurf= NULL;

	//Start SDL
	SDL_Init( SDL_INIT_EVERYTHING );


	//Set up screen
	bgSurf = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

	//Load image
	textImg = SDL_LoadBMP( "/home/rps/GAME_ENGINE/SDL/workspace/01_load_image/im-in.bmp" );

	if(textImg == NULL)
	{
		printf("error in loading image...");
		return -1;
	}

	SDL_BlitSurface(textImg,NULL,bgSurf,NULL);

	//Update Screen
	SDL_Flip( bgSurf );


	// delay
	SDL_Delay(10000);

	//Free the loaded image
	SDL_FreeSurface( bgSurf );

	//Quit SDL
	SDL_Quit();



	 return 0;

}

