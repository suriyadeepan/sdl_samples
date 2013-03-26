#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//the surfaces
SDL_Surface* message = NULL;
SDL_Surface* screen = NULL;

// event obj
SDL_Event event;

// Font - attributes
//  the font that's going to be used
TTF_Font *font = NULL;

//the color of the font
SDL_Color textColor = { 0,0,0xFF };




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


		if(optimizedImg!=NULL)
		{
			//Map the color key
			Uint32 colorkey = SDL_MapRGB( optimizedImg->format, 0xFF,0xFF,0xFF);
			//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
			SDL_SetColorKey( optimizedImg, SDL_SRCCOLORKEY, colorkey );
		}


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

    //Initialize SDL_ttf
    if( TTF_Init() == -1 ){
    	return false;
    }


    //Set the window caption
    SDL_WM_SetCaption( "Event testing", NULL );

    //If everything initialized fine
    return true;
}


void clean_up()
{
    //Free the images
    SDL_FreeSurface( bgImg );
    SDL_FreeSurface( message );

    // Quit TTF
    TTF_Quit();

    TTF_CloseFont(font);

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

	SDL_FillRect(screen,NULL,0xffffff);

	// load image
	//bgImg = loadOptimizedImage("/home/rps/Pictures/SDL/bg-red.bmp");


	// load font
	font = TTF_OpenFont( "/usr/share/fonts/liberation/LiberationMono-Regular.ttf", 28 );

	if(font == NULL)
		{
			printf("font is null");
			return -1;
		}


	// render text
	message = TTF_RenderText_Solid(font,"Hey! I'm rendering TTF! Awesome!!!",textColor);


	if(message == NULL){
		printf("\n Image (message) loaded is null!\n");
		return -1;
	}


	// blit rendered message to screen
	 applySurface(50,50,message,screen);

	// update window
	SDL_Flip(screen);

	while(1){
    	while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT)
			{
				goto the_end;
			}
    	}
	}

	the_end:

	clean_up();

	return 0;

}
