/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */

#include "Board.h"
#include <cstdio>

const int Board::BOARD_X = 17;
const int Board::BOARD_Y = 14;
//here's Bomberman's crazy board

// Note that all these enum constants from NILL onwards
// have been given numbers in increasing order
// e.g. NILL=0, and so on
// and these numbers are represented in the board array...
enum BoardParts {
	NILL, S_BRICK, G_BRICK, R_BRICK, SPD_X2
};
// defining some utility functions...

static int board_array[Board::BOARD_Y][Board::BOARD_X] = { { 0 } };

#ifdef WITH_TEXTURES
const int nbricks = 3;

GLuint texture[nbricks];
GLuint tid[nbricks];
string tnames[] = {"solid.png", "brick.png", "brick-green.png"};
GLuint mtid[nbricks];
int cwidth = 60, cheight = 60; // 60x60 pixels bricks...

void RegisterTextures()
/*Function is used to load the textures from the
 * files and display*/
{
	// allocate a texture name
	glGenTextures(nbricks, tid);

	vector<unsigned char> data;
	//ofstream ofile("image-data.bin", ios::binary | ios::out);
	// now load each bricks data...

	for (int i = 0; i < nbricks; ++i) {

		// Read current brick

		ReadImage(tnames[i], data);
		if (i == 0) {
			int length = data.size();
			//ofile.write((char*) &length, sizeof(int));
		}
		//ofile.write((char*) &data[0], sizeof(char) * data.size());

		cout << " Texture Id=" << tid[i] << endl;
		mtid[i] = tid[i];
		// select our current texture
		glBindTexture(GL_TEXTURE_2D, tid[i]);

		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		bool wrap = true;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
				wrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
				wrap ? GL_REPEAT : GL_CLAMP);

		// build our texture MIP maps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, cwidth, cheight, GL_RGB,
				GL_UNSIGNED_BYTE, &data[0]);
	}
	//ofile.close();

}
void Drawbrick(const BoardParts &cname, float fx, float fy, float fwidth,
		float fheight)
/*Draws a specfic brick at given position coordinate
 * sx = position of x-axis from left-bottom
 * sy = position of y-axis from left-bottom
 * cwidth= width of displayed brick in pixels
 * cheight= height of displayed bricki pixels.
 * */
{

	glPushMatrix();
	glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mtid[cname - 1]);
//	glTranslatef(0, 0, 0);
//	glRotatef(-M_PI / 2, 0, 0, 1);
	glBegin (GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();

	glColor4f(1, 1, 1, 1);

//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}
#endif
// Destructor
Board::~Board(void) {
}
void Board::InitalizeBoard(int w, int h) {
	m_iWidth = w;
	m_iHeight = h;	

	for (int i = 0; i < BOARD_Y - 1; ++i) {
		for (int j = 0; j < BOARD_X; ++j) {
			if (i == 0 || i == BOARD_Y - 2 || j == 0 || j == BOARD_X - 1)
				board_array[i][j] = S_BRICK;
			else if (i % 2 == 0 && j % 2 == 0)
				board_array[i][j] = S_BRICK;
			else
				board_array[i][j] =
						(GetRandInRange(0, 10)) < 8 ? NILL :
						(GetRandInRange(0, 10)) < 8 ? G_BRICK : R_BRICK;
		}
	}

}
//Constructor
Board::Board(int xsize, int ysize) {
	m_iXCellsize = xsize;
	m_iYCellsize = ysize;
	pcolor = CHOCOLATE;
	bcolor = ORANGE_RED;
	gcolor = PINK;
	m_iCurrentX = 0;
	m_iCurrentY = 0;
	this->m_iScore = 0;
	this->m_iLife = 3;
	this->m_iTime = 200;
//set up board
}

void Board::Draw() {
	glColor3f(0, 0, 1);
	glPushMatrix();

#ifdef WITH_TEXTURES
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += m_iXCellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (m_iYCellsize)) {
			//			cout << " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
				case NILL:
				// Empty space
				break;
				case S_BRICK:
				case G_BRICK:
				case R_BRICK:
				float fwidth = (float) (m_iXCellsize) / width * 2, fheight =
				(float) m_iYCellsize / height * 2;
				float fx = (float) (x - 10) / width * 2 - 1, fy = (float) y
				/ height * 2 - 1;

				/*Drawbrick((BoardParts) board_array[i][j], fx, fy, fwidth,
				 fheight);*/
				Drawbrick((BoardParts) board_array[i][j], (float)x/width-1, (float)y/height-1, fwidth,
						fheight);
				break;
			}
		}
	}
#else
	for (int i = 0, y = 0; i < BOARD_Y - 1; ++i, y += m_iXCellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (m_iYCellsize)) {
						cout <<      " " << board_array[3][4] << " " <<		 " ";
			switch (board_array[i][j]) {
			case NILL:
				// Empty space
				break;
			case S_BRICK:
				DrawRectangle(x - 10, y, m_iYCellsize, m_iXCellsize,
						colors[SLATE_GRAY]);
				//DrawLine(x - 10, y, x - 10 + m_iYCellsize, y, 4, colors[BLACK]);
				break;
			case G_BRICK:
				DrawRectangle(x - 10, y, m_iYCellsize, m_iXCellsize,
						colors[LIGHT_GREEN]);
				break;
			case R_BRICK:
				DrawRectangle(x - 10, y, m_iYCellsize, m_iXCellsize, colors[RED]);
				break;
			case SPD_X2:
				DrawCircle(6 * this->GetCellSizeX() + this->GetMidX(), 3 * this->GetCellSizeY() + this->GetMidY(), 10, colors[ORANGE]);
				break;
			}
		}
	}
#endif
	glPopMatrix();
}

void Board::GetInitPinkyPosition(int &x, int &y) {
	x = m_iXCellsize * 3;
	y = (BOARD_Y - 3) * m_iYCellsize;
}
void Board::GetInitTextPosition(int &x, int &y) {
	x = m_iXCellsize;
	y = (BOARD_Y - 1) * m_iYCellsize + m_iYCellsize / 2;
}

bool Board::check(int x, int y)
{
	if(board_array[y/this->GetCellSizeY()][x/this->GetCellSizeX()] == NULL)
		return 1;
	
	else
		return 0;
}

string Board::getScore()
{
	stringstream score;
	string _score;

	score << this->m_iScore;

	score >> _score;

	return _score;
}

string Board::getLife()
{
	stringstream life;
	string _life;

	life << this->m_iLife;

	life >> _life;

	return _life;
}

void Board::updateScore(int score)
{
	this->m_iScore = score;
}

void Board::updateLife(int life)
{
	if(this->m_iLife != 3)
		this->m_iLife = life;
	else
		;
}

void Board::destroyBrick()
{

	int _x = Bomb::getX()/this->m_iXCellsize;
	int _y = Bomb::getY()/this->m_iYCellsize;

	cout << "  _X:  " << _x << " " << "   _Y:   " << _y << endl;

	if(board_array[_y][_x + 1] == G_BRICK)
		{
			board_array[_y][_x + 1] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y][_x - 1] == G_BRICK)
		{
			board_array[_y][_x - 1] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y + 1][_x] == G_BRICK)
		{
			board_array[_y + 1][_x] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y - 1][_x] == G_BRICK)
		{
			board_array[_y - 1][_x] = 0;
			this->m_iScore += 100;
		}


	//Red Brick
		if(board_array[_y][_x + 1] == R_BRICK)
		{
			board_array[_y][_x + 1] = 0;

			_x = _x + 1;
			

				if(board_array[_y][_x + 1] == G_BRICK)
		{
			board_array[_y][_x + 1] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y][_x - 1] == G_BRICK)
		{
			board_array[_y][_x - 1] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y + 1][_x] == G_BRICK)
		{
			board_array[_y + 1][_x] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y - 1][_x] == G_BRICK)
		{
			board_array[_y - 1][_x] = 0;
			this->m_iScore += 100;
		}
			this->m_iScore += 200;
		}

	if(board_array[_y][_x - 1] == R_BRICK)
		{
			board_array[_y][_x - 1] = 0;
			_x = _x -1;
				if(board_array[_y][_x + 1] == G_BRICK)
		{
			board_array[_y][_x + 1] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y][_x - 1] == G_BRICK)
		{
			board_array[_y][_x - 1] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y + 1][_x] == G_BRICK)
		{
			board_array[_y + 1][_x] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y - 1][_x] == G_BRICK)
		{
			board_array[_y - 1][_x] = 0;
			this->m_iScore += 100;
		}
			this->m_iScore += 200;
		}

	if(board_array[_y + 1][_x] == R_BRICK)
		{
			board_array[_y + 1][_x] = 0;

			_y = _y + 1;

				if(board_array[_y][_x + 1] == G_BRICK)
		{
			board_array[_y][_x + 1] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y][_x - 1] == G_BRICK)
		{
			board_array[_y][_x - 1] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y + 1][_x] == G_BRICK)
		{
			board_array[_y + 1][_x] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y - 1][_x] == G_BRICK)
		{
			board_array[_y - 1][_x] = 0;
			this->m_iScore += 100;
		}

			this->m_iScore += 200;
		}

	if(board_array[_y - 1][_x] == R_BRICK)
		{
			board_array[_y - 1][_x] = 0;

			_y = _y - 1;

				if(board_array[_y][_x + 1] == G_BRICK)
		{
			board_array[_y][_x + 1] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y][_x - 1] == G_BRICK)
		{
			board_array[_y][_x - 1] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y + 1][_x] == G_BRICK)
		{
			board_array[_y + 1][_x] = 0;
			this->m_iScore += 100;
		}

	if(board_array[_y - 1][_x] == G_BRICK)
		{
			board_array[_y - 1][_x] = 0;
			this->m_iScore += 100;
		}
			this->m_iScore += 200;
		}
	

//	glutTimerFunc(2000, destroyBrick, 0);
}

int Board::getScoreI()
{
	return this->m_iScore;
}

string Board::getTime()
{
	stringstream time;
	string _time;

	time << m_iTime;

	time >> _time;

	return _time;
}

void Board::updateTime(int m)
{
	m_iTime--;

	glutTimerFunc(1000, updateTime, 0);
}

void Board::powerup()
{
	if(board_array[3][6] == NULL)
	{
		board_array[3][6] = SPD_X2;
	}

}