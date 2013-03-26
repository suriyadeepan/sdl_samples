#include <SDL/SDL.h>
#include <SDL/SDL_image.h>



SDL_Surface* loadOptimizedImage(char* fileName)
{

	SDL_Surface* loadedImg = IMG_Load(fileName);
	SDL_Surface* optimizedImg = NULL;

	if(loadedImg!=NULL)
	{
		//Create an optimized image
		optimizedImg = SDL_DisplayFormat( loadedImg );

		//Free the old image
		SDL_FreeSurface( loadedImg );
	}

	else
	{
		printf("\n Loaded Img is null!");

	}

	return optimizedImg;
}



int main(int argc, char *argv[])
{
	SDL_Surface* bgImg = NULL;
	SDL_Surface* screen = NULL;

	// init SDL libs
	SDL_Init(SDL_INIT_EVERYTHING);

	// load bgImg
	//bgImg = loadOptimizedImage("/home/rps/Pictures/SDL/bg-green.jpg");
	bgImg = IMG_Load("/home/rps/Pictures/SDL/bg-green.jpg");

	if(bgImg == NULL)
	{
		printf("\nbgImg is null!\n");
		return -1;
	}
	// setup screen
	screen= SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

	SDL_Rect offset;

	offset.x = 40;
	offset.y = 70;

	// blit image to screen
	SDL_BlitSurface(bgImg,NULL,screen,&offset);

	// set window caption
	SDL_WM_SetCaption("Blitting a JPG!",NULL);


	// update window
	SDL_Flip(screen);

	// wait
	SDL_Delay(10000);

	// free memory from surfaces
	SDL_FreeSurface(bgImg);


	// quit SDL
	SDL_Quit();

	return 0;

}
