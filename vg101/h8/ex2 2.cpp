#include "ex2.h"
void TimeStep(int n)
{
    glutTimerFunc((unsigned int)n, TimeStep, n);
    glutPostRedisplay();
}
void glDraw()
{
    Triangle t1 = Triangle({-5, 0}, {0, 5}, {5, 0}, (float)0.5, (float)0.1, (float)0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    t1.draw();
    glutSwapBuffers();
    glFlush();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Triangle");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(-10, 10, -10, 10);  //important
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(glDraw);
    glutTimerFunc(25, TimeStep, 1);
    glutMainLoop();
}
