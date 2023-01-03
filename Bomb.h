#ifndef BOMB_H
#define BOMB_H

#include "util.h"



class Bomb
{
private:
    inline static bool m_bBomb;
    inline static int m_iX;
    inline static int m_iY;

public:


    Bomb()  //constructor
    { 
        m_bBomb = 0;
    }

    bool getBombStatus()
    {
        return m_bBomb;
    }

    void SetBombStatus(bool status)
    {
        m_bBomb = status;
    }

    void setX(int x)
    {
        m_iX = x;
    }

    void setY(int y)
    {
        m_iY = y;
    }

    static int getX()
    {
        return m_iX;
    }

    static int getY()
    {
        return m_iY;
    }

    static void Blast(int m)
    {
        if(m_bBomb == 1)
        {
            DrawCircle(Bomb::m_iX, Bomb::m_iY, 15, colors[RED]);

        }
        else
            ;

         m_bBomb = 0;

        
    glutPostRedisplay();
        
   //countdown of 2 seconds until bomb explodes
    glutTimerFunc(2000, Blast, 0); 

    };

};


    
#endif