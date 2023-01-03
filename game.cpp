//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Brick Slayer...
//============================================================================

#ifndef Bomberman_CPP_
#define Bomberman_CPP_
#include "Board.h"
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include"BomberMan.h"
#include "Bomb.h"
#include <unistd.h>	//for sleep function
using namespace std;
bool bombStatus = false;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
void DrawEnemy(int x/*starting x*/, int y/*starting y*/,
		ColorNames color/*color*/, float gw = 6/*Enemy Width in Units*/,
		float gh = 7/*Enemy Height in Units*/) {
	int ogw = 6, ogh = 7;

	glPushMatrix();
	float sx = (float) gw / ogw, sy = (float) gh / ogh;
	glTranslatef(x, y, 1);
	glScalef(sx, sy, 1);

	// Draw Enemy
	DrawRoundRect(0, 1, 6, 3, colors[color]);
	DrawCircle(3, 4, 3.01, colors[color]);
	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	//  legs
	DrawCircle(0.75, 1, 0.75, colors[color]);
	DrawCircle(3.25, 1, 0.75, colors[color]);
	DrawCircle(5.85, 1, 0.75, colors[color]);

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

//Number of Vertices used to draw Bomberman Circle...
// x= r cos (theta), y= r sin(theta)
/*const int npmvertices = 1220;
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
*/

//void DrawBomberman(float sx/*center x*/, float sy/*center y*/,
//		float radius/*Radius*/,
//		const ColorNames &colorname/*Bomberman Colour*/) {

//	glColor3fv(colors[colorname]); // set the circle color
//	InitPMVertices(radius);
//	glBegin (GL_TRIANGLE_FAN);
//	glVertex4f(sx, sy, 0, 1);
//	for (int i = 0; i < npmvertices; ++i)
//		glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
//	glEnd();
//	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
//			radius / 10, colors[BLACK]);
//}

/*
 * Main Canvas drawing function.
 * */
Board *b;
BomberMan *p1;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	//

	b->Draw();
	p1->DrawPlayer();
	p1->DrawBomb();

	int x, y;
	b->GetInitPinkyPosition(x, y);
	cout << x << "  y= " << y << endl << flush;
	DrawEnemy(x, y, PINK, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());


	p1->DrawBomberman(b->GetCellSize() / 2 - 2);
//	p1->DrawBomb();
	b->destroyBrick();

	b->updateScore(b->getScoreI());

	b->GetInitTextPosition(x, y);
	cout << endl <<"Text Position = "<< x << "  y= " << y << endl << flush;
	DrawString(x, y, "Score = ", colors[5]);
	DrawString(x + 80, y, b->getScore(), colors[5]);
	DrawString(x + 800, y, "Life = ", colors[5]);
	DrawString(x + 880, y, b->getLife(), colors[5]);
	DrawString(x + 400, y, "Time: ", colors[5]);
	DrawString(x + 480, y, b->getTime(), colors[5]);
	//	glPopMatrix();
	

	glutSwapBuffers(); // do not modify this line..


}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	//	if(board_array[p1.GetBomberManPosition_x()][p1.GetBomberManPosition_y()] == NULL)
		p1->MoveLeft(b->check(p1->GetBomberManPosition_x() - b->GetCellSizeX(), p1->GetBomberManPosition_y()));

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
				cout << "BMPX: " << p1->GetBomberManPosition_x() << " BMPY: " << p1->GetBomberManPosition_y() << endl;
				p1->MoveRight(b->check(p1->GetBomberManPosition_x() + b->GetCellSizeX(), p1->GetBomberManPosition_y()));

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
				p1->MoveUp(b->check(p1->GetBomberManPosition_x(), p1->GetBomberManPosition_y() + b->GetCellSizeY()));

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
			cout << "HEEKNKS";
			p1->MoveDown(b->check(p1->GetBomberManPosition_x(), p1->GetBomberManPosition_y() - b->GetCellSizeY()));

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	
	 glutPostRedisplay();
	 
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
				p1->PlaceBomb();
				

	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	p1->DrawBomb();
	glutPostRedisplay();

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0/60, Timer, 0);
}

void GoMenu(int id)
{
	switch(id)
	{
		case 1: cout << "Continue";
				break;
		case 2: cout << "New Game";
				break;
		case 3: cout << "PAUSE";
				break;
		case 4: exit(0);
				break;
	}
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	b = new Board(60, 60); // create a new board object to use in the Display Function ...
	p1 = new BomberMan(YELLOW, SLOW, b->GetCellSizeX(), b->GetCellSizeY());

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CP's Bomber Bomberman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
#ifdef WITH_TEXTURES
	RegisterTextures();
#endif
	glutAddMenuEntry("Continue", 1);
	glutAddMenuEntry("New Game", 2);
	glutCreateMenu(GoMenu);
	glutAddMenuEntry("Pause", 3);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	glutTimerFunc(1000, Board::updateTime, 0);
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000, Bomb::Blast, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Bomberman_CPP_ */