/*
 * game_algorithm.hpp
 *
 *  Created on: Mar 26, 2013
 *      Author: rps
 */

#ifndef GAME_ALGORITHM_HPP_
#define GAME_ALGORITHM_HPP_



// a class which works as the brain
//  of the game
class GameBrain
{

public:

    GameBrain();

    void setupArena();

};

// a class to represent a point
class GamePoint
{
public:

	int x;
	int y;
	int value;

	GamePoint(int x1,int y1)
	{
		x=x1;
		y=y1;
		value = 0;
	}

	void setValue(int val);


};

#endif /* GAME_ALGORITHM_HPP_ */
