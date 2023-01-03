/*
 * Board.h
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <GL/glut.h>
#include <iostream>
#include "util.h"
#include "Bomb.h"
// #define WITH_TEXTURES
using namespace std;
class Board
{
private:
	int m_iXCellsize, m_iYCellsize;
	int m_iWidth, m_iHeight;
	ColorNames pcolor, bcolor, gcolor;
	int m_iCurrentX, m_iCurrentY; // current bomberman position
	int m_iScore;	//score
	int m_iLife;	//Life
	inline static int m_iTime;	//Time left

public:
	static const int BOARD_X;
	static const int BOARD_Y;
	Board(int xsize = 8, int ysize = 8);

	~Board(void);
	void InitalizeBoard(int, int);
	// draw the board
	void Draw();

	static const int GetBoardX()
	{
		return BOARD_X;
	}
	static const int GetBoardY()
	{
		return BOARD_Y;
	}
	int GetMidX()
	{
		return BOARD_X * m_iXCellsize / 2.0;
	}
	int GetMidY()
	{
		return BOARD_Y * m_iYCellsize / 2.0;
	}
	int GetCellSizeX()
	{
		return m_iXCellsize;
	}
		int GetCellSizeY()
	{
		return m_iYCellsize;
	}
	int GetCellSize()
	{
		return m_iXCellsize;
	}
	void GetInitBombermanPosition(int &x, int &y)
	{
		x = m_iXCellsize + m_iXCellsize / 2;
		y = m_iYCellsize + m_iYCellsize / 2;
	}

	void UpdateBombermanPosition(int &x, int &y)
	{

		x = x + (m_iXCellsize * this->m_iCurrentX);
		y = y + (m_iYCellsize * this->m_iCurrentY);
	}
	bool check(int x, int y);	//checks weather the position x, y is empty
	string getScore();	//returns current score in string
	void updateScore(int);	//sets score
	string getLife();	//returns number of lives left
	void updateLife(int);	//sets the number of lives
	void GetInitTextPosition(int &x, int &y);
	void GetInitPinkyPosition(int &x, int &y);
	void destroyBrick();	//destroys brick at x, y
	int getScoreI();	//get score in int
	static void updateTime(int m);	//update time
	static string getTime();	//gets time in string
	void powerup();	//putting powerups under bricks
	void Finished();	//end of game
	//	int GetMidx
};

#ifdef WITH_TEXTURES
void RegisterTextures();
#endif

#endif