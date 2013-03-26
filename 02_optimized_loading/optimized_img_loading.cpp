#include <stdio.h>
#include <SDL/SDL.h>

SDL_Surface* loadOptimizedImage(char* fileName)
{

	SDL_Surface* loadedImg = SDL_LoadBMP(fileName);
	SDL_Surface* optimizedImg = NULL;

	if(loadedImg!=NULL)
	{
		//Create an optimized image
		optimizedImg = SDL_DisplayFormat( loadedImg );

		//Free the old image
		SDL_FreeSurface( loadedImg );
	}

	return optimizedImg;
}

void apply_surface( int x, int y, SDL_Surface* src, SDL_Surface* dest )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;


    SDL_BlitSurface( src, NULL, dest, &offset );
}


int main(int argc, char *argv[]){

	// text to display
	SDL_Surface* text= NULL;

	// background image
	SDL_Surface* bgImg = NULL;

	// bg Surface => Screen
	SDL_Surface* bgSurface = NULL;

	// init all SDL libs
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		printf("\nSDL lib init failed!\n");
		return -1;
	}



	//Set up the screen
	// SDL_SWSURFACE => creates screen surface
	//  in system memory
	bgSurface = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );


	if(bgSurface == NULL)
	{
		printf("\nbgSurface => Null\n");
		return -1;
	}

	//Set the window caption
	SDL_WM_SetCaption( "Optimized Image Loading", NULL );


	// ---Load images---
	bgImg = loadOptimizedImage("/home/rps/Pictures/SDL/bg-green.bmp");
	text = loadOptimizedImage("/home/rps/Pictures/SDL/text.bmp");

	// blit bgImg to the screen, bgSurface
	apply_surface(100,100,bgImg, bgSurface);
	// blit text to screen
	apply_surface(200,200,text,bgSurface);


	// Update window
	SDL_Flip(bgSurface);

	// delay
	SDL_Delay(10000);

	//Free the surfaces
	SDL_FreeSurface( bgImg );
	SDL_FreeSurface( text);

	//Quit SDL
	SDL_Quit();

	//Return
	return 0;

}
