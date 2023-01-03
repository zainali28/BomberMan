#include <iostream>
#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1);

    glBegin(GL_LINES);

        for(int i = -2.5; i <= 2.5; i += 0.25)
        {       
            glColor3f(i, 0, 2.5);
            glColor3f(i, 0, -2.5);
            glColor3f(2.5, 0, i);
            glColor3f(-2.5, 0, i);
        }

    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0.1, 0.39, 0.88, 1.0);

    glColor3f(1.0, 1.0, 1.0);

    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glFrustum(-2, 2, -1.5, 1.5, 1, 40);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef(0, 0, -3);

    glRotatef(50, 1, 0, 0);

    glRotatef(70, 0, 1, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(80, 80);
    
    glutInitWindowSize(640, 480);

    glutCreateWindow("TEST");

    glutDisplayFunc(display);

    init();

    glutMainLoop();
}