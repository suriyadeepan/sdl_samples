#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//the surfaces
SDL_Surface *image = NULL;
SDL_Surface *screen = NULL;

// event obj
SDL_Event event;


void applySurface( int x, int y, SDL_Surface* src, SDL_Surface* dest )
{
    //Temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Get the offsets
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( src, NULL, dest, &offset );
}

SDL_Surface* loadOptimizedImage(char* fileName)
{

	SDL_Surface* loadedImg = NULL;
	SDL_Surface* optimizedImg = NULL;

	loadedImg = IMG_Load(fileName);

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


bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Event testing", NULL );

    //If everything initialized fine
    return true;
}


void clean_up()
{
    //Free the image
    SDL_FreeSurface( image );

    //Quit SDL
    SDL_Quit();
}



int main(int argc, char *argv[])
{

	//Initialize
	if( init() == false ){
		printf("Initialization failed!");
		return -1;
	}

	// load image
	image = loadOptimizedImage("/home/rps/Pictures/SDL/bg-green.jpg");
	//bgImg = IMG_Load("/home/rps/Pictures/SDL/bg-green.jpg");

	if(image == NULL){
		printf("\nbgImg is null!\n");
		return -1;
	}

	applySurface(20,20,image,screen);

	// update window
	SDL_Flip(screen);

	while(1)
	{
		while(SDL_PollEvent(&event))
		{

			if(event.type == SDL_KEYDOWN)
				printf("Key pressed: %s",SDL_GetKeyName(event.key.keysym.sym));

			else if(event.type == SDL_QUIT)
			{
				printf("Quit pressed!");
				goto the_end;
			}


		}
	}

	the_end:

	clean_up();

	return 0;

}
