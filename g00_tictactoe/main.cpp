#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "game_algorithm.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

// an array to represent the arena
int arenaArr[3][3];

int currX;
int currY;

// moves
int usrMovesX[5];
int usrMovesY[5];
int usrMoveIndex=0;

int comMovesX[5];
int comMovesY[5];
int comMoveIndex=0;


/*
 * 	--------- SDL -----------
 */
//Screen attributes
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

//the surfaces
SDL_Surface* usrIcon = NULL;
SDL_Surface* comIcon = NULL;
SDL_Surface* bgImg = NULL;

SDL_Surface* screen = NULL;

// event obj
SDL_Event event;
/****************************/



/*
 * 	----------------- SDL METHODS -------------------
 *
 */
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
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT,
    		SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }


    SDL_EnableUNICODE(1);


    //Set the window caption
    SDL_WM_SetCaption( "Event testing", NULL );

    //If everything initialized fine
    return true;
}


void clean_up()
{
    //Free the images
    SDL_FreeSurface( usrIcon);
    SDL_FreeSurface( comIcon);

    //Quit SDL
    SDL_Quit();
}

void updateScreen(int x,int y,int type)
{

	if(type == 0)
	applySurface(x*200,y*200,usrIcon,screen);

	else
	applySurface(x*200,y*200,comIcon,screen);


	// update window
	SDL_Flip(screen);

}
/******************************************************/

void initArena()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			arenaArr[i][j]=0;
}

void showArena()
{

		for(int j=0;j<3;j++)
		{
			for(int i=0;i<3;i++)
			{
				printf("%d ",arenaArr[i][j]);
			}
			printf("\n");
		}


}



void getRandomFreePoint()
{
	int rx,ry;

	while(1)
	{
	rx= rand() % 3;
	ry= rand() % 3;

	if(arenaArr[rx][ry]==0)
	{
		currX=rx;
		currY=ry;

		break;
	}
	}

}

bool find3rdPoint(int prevX0,int prevY0)
{

	int px1 = currX;
	int py1 = currY;


	int slope;

	if((px1-prevX0)!=0)
	 {
		slope = (py1-prevY0)/(px1-prevX0);

		for(int j=0;j<3;j++)
		{
			for(int i=0;i<3;i++)
			{
				if(j == (slope*(i-prevX0))+prevY0 && arenaArr[i][j]==0)
					{
						currX = i;
						currY = j;

						return true;
					}

			}
		}
	 }

	// if denom of slope = 0
	else
	 {
		slope = 0;

		for(int j=0;j<3;j++)
			if(arenaArr[prevX0][j]==0)
				{
					currX=prevX0;
					currY=j;
					return true;
				}
	 }// end of else

	return false;

}


bool find3rdPoint1(int prevX0,int prevY0,int px1,int py1)
{



	int slope;

	if((px1-prevX0)!=0)
	 {
		slope = (py1-prevY0)/(px1-prevX0);

		for(int j=0;j<3;j++)
		{
			for(int i=0;i<3;i++)
			{
				if(j == (slope*(i-prevX0))+prevY0 && arenaArr[i][j]==0)
					{
						currX = i;
						currY = j;

						return true;
					}

			}
		}
	 }

	// if denom of slope = 0
	else
	 {
		slope = 0;

		for(int j=0;j<3;j++)
			if(arenaArr[prevX0][j]==0)
				{
					currX=prevX0;
					currY=j;
					return true;
				}
	 }// end of else

	return false;

}


void updateUsrStack()
{
	// store usr move
	usrMovesX[usrMoveIndex] = currX;
	usrMovesY[usrMoveIndex] = currY;

	usrMoveIndex++;


	printf("\nUser Move Index: %d\n",usrMoveIndex);

	for(int i=0;i<usrMoveIndex;i++)
		printf("(%d , %d) ",usrMovesX[i],usrMovesY[i]);

	printf("\n\n");

}

void updateComStack()
{
	// store computer's move
	comMovesX[comMoveIndex] = currX;
	comMovesY[comMoveIndex] = currY;

	comMoveIndex++;

	printf("\nCom Move Index: %d\n",comMoveIndex);

	for(int i=0;i<comMoveIndex;i++)
		printf("(%d , %d) ",comMovesX[i],comMovesY[i]);

	printf("\n\n");

}

void computeMove()
{
	for(int i=0;i<comMoveIndex-1;i++)
	{
		if(find3rdPoint1(comMovesX[i],comMovesY[i],comMovesX[comMoveIndex-1],comMovesY[comMoveIndex-1]))
		{
			printf("\n$1\n");
			return;
		}
	}


	for(int i=0;i<usrMoveIndex;i++)
	{
		if(find3rdPoint(usrMovesX[i],usrMovesY[i]))
		{
			break;
		}
		else
		 if(i == usrMoveIndex-1)
			 getRandomFreePoint();
	}

	arenaArr[currX][currY]=2;
	updateComStack();



}

void playerMove()
{
	/*
	do{

			printf("\nMove: P%d\n",usrMoveIndex+1);

			printf("x:");
			scanf("%d",&currX);
			printf("y:");
			scanf("%d",&currY);

			}while(arenaArr[currX][currY]!=0);

	*/
			// set P2 point in arena
			arenaArr[currX][currY]=1;

			updateUsrStack();

}

void computeInitMove()
{
	printf("\nMove: C1\n");

	int prevY0=currY;
	int prevX0=currX;

	currX = abs(prevX0-2);
	currY = abs(prevY0-2);


	// get the best I point
	arenaArr[currX][currY]=2;


	updateComStack();

}

void waitForEvent()
{
	while(1){
	 while(SDL_PollEvent(&event)){
		 if(event.type == SDL_KEYDOWN)
		 {
			 if(event.type == SDL_QUIT)
			 {
				 exit(0);
			 }
		 }

		 else if(event.type == SDL_MOUSEBUTTONDOWN)
		 {
			 currX=(int)(event.button.x/201);
			 currY=(int)(event.button.y/201);
			 return;
		 }
	 }

	}
}// end of waitForEvent()...



int main(int argc, char *argv[])
{

	initArena();


	//Initialize
	if( init() == false ){
		printf("Initialization failed!");
		return -1;
		}

	SDL_FillRect(screen,NULL,0xffffff);


	// load images
	bgImg = loadOptimizedImage("/home/rps/Pictures/SDL/grid.bmp");
	usrIcon = loadOptimizedImage("/home/rps/Pictures/SDL/usr_icon.bmp");
	comIcon = loadOptimizedImage("/home/rps/Pictures/SDL/com_icon.bmp");

	applySurface(0,0,bgImg,screen);

	// update window
	SDL_Flip(screen);



	for(int i=0;i<5;i++)
	{
		waitForEvent();
		updateScreen(currX,currY,0);
		playerMove();

		if(i==0)
		{
			computeInitMove();
			updateScreen(currX,currY,1);

		}

		else
			if(i<5)
			{
				computeMove();
				updateScreen(currX,currY,1);
			}

		//showArena();
	}

	clean_up();

	return 0;

}














