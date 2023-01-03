#ifndef BOMBER_MAN_H
#define BOMBER_MAN_H
#include <iostream>
#include"Board.h"
#include "Bomb.h"
using namespace std;

enum Speed {SLOW = 8, MEDIUM = 16, FAST = 32};	//speeds for bomberman
enum Energizers {SPEED, MULTI_BOMB, BOMB_AREA, SCATTER_ENEMIES, SCORE_X2, LIFE_REFILL, GOD_MODE};	//powerups for bomberman

class BomberMan : public Board
{
private:
    int m_iCurrentX;
    int m_iCurrentY;
	int speed;
	Energizers m_EngPowerUps;
    ColorNames color;
	Bomb m_Bomb;
	int m_iBombX;
	int m_iBombY;



public:
    BomberMan( ColorNames cl = YELLOW, int spd = SLOW, int X = 8, int Y = 8): Board(X, Y)
    {
		this->color = cl;
		this->speed = spd;
		this->m_iCurrentX = this->GetCellSizeX() * 2 - this->GetCellSizeX() / 2;
		this->m_iCurrentY = this->GetCellSizeY() * 2 - this->GetCellSizeY() / 2;
    };
    int GetBomberManPosition_x()const {return this->m_iCurrentX;}
    int GetBomberManPosition_y()const {return this->m_iCurrentY;}
    void setBomberManPosition(const int& x, const int& y){
        this->m_iCurrentX = x;
        this->m_iCurrentY = y;
    }

    void MoveRight(int c) // move in +x
	{
	//	if(this->m_iCurrentX >= 916)
	//	;
	//	else
	if(c == 1)
       { this->m_iCurrentX += 1 * this->GetCellSizeX();
	   		cout << endl << "X: " << this->m_iCurrentX << endl;
	   	
		}
	
	}

	void MoveUp(int c) // move in +y
	{
		if(c == 1)
		{
			this->m_iCurrentY += 1 * this->GetCellSizeY();
		cout << endl << "Y: " << this->m_iCurrentY << endl;
		}

	}

	void MoveLeft(int c) // move in -x
	{
	//	cout << endl << "X: " << this->m_iCurrentX;
	//	if(this->m_iCurrentX <= 76)
	//	;
	//	else
	
	if(c == 1)
		this->m_iCurrentX += -1 * this->GetCellSizeX();


	}

	void MoveDown(int c) // move in -y
	{
		if(c == 1)
		this->m_iCurrentY += -1 * this->GetCellSizeY();
	}

	const int static npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius) {

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / 6.0;
	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}

    void DrawBomberman(float sx/*center x*/, float sy/*center y*/,
		float radius/*Radius*/) {

	glColor3fv(colors[BLUE]); // set the circle color
	InitPMVertices(radius);
	glBegin (GL_TRIANGLE_FAN);
	glVertex4f(sx, sy, 0, 1);
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
	glEnd();
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
			radius / 10, colors[BLACK]);
}

 void DrawBomberman(float radius/*Radius*/) {

	glColor3fv(colors[this->color]); // set the circle color
	InitPMVertices(radius);
	glBegin (GL_TRIANGLE_FAN);
	glVertex4f(this->m_iCurrentX, this->m_iCurrentY, 0, 1);
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(this->m_iCurrentX + pmvertices[i][0], this->m_iCurrentY + pmvertices[i][1], 0, 1);
	glEnd();
	DrawCircle(this->m_iCurrentX - radius + radius / 2, this->m_iCurrentY + (radius - radius / 2),
			radius / 10, colors[BLACK]);
}

void DrawPlayer()
{
		this->DrawBomberman(this->GetCellSize() / 2 - 2);
    //    m_iCurrentX = this->GetCellSizeX() + this->GetCellSizeX() / 2;
		cout << endl << "bomberX: " << this->m_iCurrentX << endl;
	//	m_iCurrentY = this->GetCellSizeY() + this->GetCellSizeY() / 2;
		cout << endl << "bomberY: " << this->m_iCurrentY << endl;
}

void Initialize()
{
	this->DrawBomberman(76, 92, this->GetCellSize() / 2 - 2);
}
    
    //void PlaceBomb();
    //int GetX();
    //DrawBomberMan
    ~BomberMan(){
    }

	void PlaceBomb()
	{
		if(!this->m_Bomb.getBombStatus())
		{
		this->m_Bomb.SetBombStatus(1);
		this->m_Bomb.setX(this->m_iCurrentX);
		this->m_Bomb.setY(this->m_iCurrentY);
		}


		cout << "           mixXXX:      " << this->GetBomberManPosition_x() << endl;
	}

	void DrawBomb()
	{
		if(this->m_Bomb.getBombStatus())
		{
			DrawCircle(this->m_Bomb.getX(), this->m_Bomb.getY(), 15, colors[RED]);
		}

	}

	int getBombX()
	{
		return this->m_Bomb.getX();
	}

	int getBombY()
	{
		return this->m_Bomb.getY();
	}

};
#endif