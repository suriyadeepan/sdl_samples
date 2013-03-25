/*
 * sdl_init_test.cpp
 *
 *  Created on: Mar 26, 2013
 *      Author: rps
 */

#include "SDL/SDL.h"

#include <stdio.h>

int main( int argc, char* args[] )
{
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    //Quit SDL
    SDL_Quit();

    printf("cool");

    return 0;
}




