#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//the surfaces
SDL_Surface* bgImg = NULL;
SDL_Surface* objImg = NULL;
SDL_Surface* screen = NULL;

// event obj
SDL_Event event;

// x,y values to denote ball pos
int ballPosX = SCREEN_WIDTH/2;
int ballPosY = SCREEN_HEIGHT/2;

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

    //Set the window caption
    SDL_WM_SetCaption( "Event testing", NULL );

    //If everything initialized fine
    return true;
}


void clean_up()
{
    //Free the images
    SDL_FreeSurface( bgImg );
    SDL_FreeSurface( objImg );

    //Quit SDL
    SDL_Quit();
}


void updateBallPosition()
{

	SDL_FillRect(screen,NULL,0xff0000);

	// blit objImg (ball) to screen
	applySurface(ballPosX,ballPosY,objImg,screen);

	// update window
	SDL_Flip(screen);

}


int main(int argc, char *argv[])
{

	//Initialize
	if( init() == false ){
		printf("Initialization failed!");
		return -1;
	}

	// load image
	bgImg = loadOptimizedImage("/home/rps/Pictures/SDL/bg-red.bmp");
	objImg = loadOptimizedImage("/home/rps/Pictures/SDL/ball-blue.bmp");


	if(bgImg == NULL || objImg == NULL){
		printf("\n Image loaded is null!\n");
		return -1;
	}

	// blit background img to screen
	applySurface(0,0,bgImg,screen);

	// blit objImg (ball) to screen
	applySurface(ballPosX,ballPosY,objImg,screen);

	// update window
	SDL_Flip(screen);

	while(1)
	{
		while(SDL_PollEvent(&event))
		{

			if(event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_DOWN:
					if(ballPosY<460)
						ballPosY+=10;
					updateBallPosition();
					break;

				case SDLK_UP:
					if(ballPosY>20)
						ballPosY-=10;
					updateBallPosition();
					break;

				case SDLK_LEFT:
					if(ballPosX>20)
						ballPosX-=10;
					updateBallPosition();
					break;

				case SDLK_RIGHT:
					if(ballPosX<620)
						ballPosX+=10;
					updateBallPosition();
					break;

				default:

					break;
				}
			}


			else if(event.type == SDL_QUIT)
			{

				goto the_end;
			}


		}
	}

	the_end:

	clean_up();

	return 0;

}
