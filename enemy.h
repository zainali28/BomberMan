#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include <time.h>
using namespace std;

class Enemy: public Board{
private:
    int enemyPos_x;
    int enemyPos_y;
    ColorNames color;
    //for the draw function
    float height;
    float width;
    int Movement[4][2] = {{0,1},{0,-1}, {1,0}, {-1,0}};
    //enemy width etc can also be added here
public:
    Enemy(){
	    this->enemyPos_x = this->GetCellSizeX() * 2 - this->GetCellSizeX() / 2;
	    //this->enemyPos_y = (BOARD_Y - 3) * this->GetCellSize();
        this->enemyPos_y = this->GetCellSizeY() * 2 - this->GetCellSizeY() / 2;
        this->color = CYAN;
        this->height = 7;
        this->width = 6;
    }

    Enemy(int X,int Y){
        this->enemyPos_x = X;
        this->enemyPos_y = Y;
    }
    
    int GetEnemyPosition_x() const {return this->enemyPos_x;}
    int GetEnemyPosition_y() const {return this->enemyPos_y;}

    void Move(){
        bool validMove = false;
        int x =  this->enemyPos_x, y = this->enemyPos_y;
        srand(time(0));
        int index;
        while(!validMove){
            index = rand() % 4;
            x = x + this->Movement[index][0] * this->GetCellSize();
            y = y + this->Movement[index][1] * this->GetCellSize();
            if(!check(x,y)){
                x = x - this->Movement[index][0] * this->GetCellSize();
                y = y - this->Movement[index][1] * this->GetCellSize();
            }
            else{
                this->enemyPos_x = x;
                this->enemyPos_y = y;
                validMove = true;
                break;
            }
        }
    }
    
void DrawEnemy() {
        int ogw = 6, ogh = 7;
	    glPushMatrix();
	    float sx = (float) this->width / ogw, sy = (float) this->height / ogh;
	    glTranslatef(this->enemyPos_x, this->enemyPos_y, 1);
	    glScalef(sx, sy, 1);

	    // Draw Enemy
	    DrawRoundRect(0, 1, 6, 3, colors[this->color]);
	    DrawCircle(3, 4, 3.01, colors[this->color]);
	    glPushMatrix();
	    glScalef(0.9, 1.1, 1);
	    //  legs
    	DrawCircle(0.75, 1, 0.75, colors[this->color]);
	    DrawCircle(3.25, 1, 0.75, colors[this->color]);
	    DrawCircle(5.85, 1, 0.75, colors[this->color]);

	    glPopMatrix();
	    //	glPopMatrix();

	    // eyes

	    glPushMatrix();
    	glScalef(0.9, 1.1, 1);
	    DrawCircle(1.85, 3.95, 0.75, colors[WHITE]);
	    DrawCircle(4.95, 3.95, 0.75, colors[WHITE]);
	    glPopMatrix();

	    // eyes
	    DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
	    DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);
	    glPopMatrix();
    }

    ~Enemy(){}

};
#endif