#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
void draw_shape()
{
    //static Car a;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //a.draw();
    //a.move();
    glColor3f(0.0f,0.0f, 0.0f);
    
    glBegin(GL_LINES);     
    glVertex2f(0.0f, 0.0f);        //直线起始坐标 
    glVertex2f(60.0f, 0.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);     
    glVertex2f(0.0f, 0.0f);        //直线起始坐标 
    glVertex2f(60.0f, 0.0f);         //直线结束坐标
    glEnd();

    glBegin(GL_LINES);     
    glVertex2f(-15.0f, 80.0f);        //直线起始坐标 
    glVertex2f(-15.0f, -5.0f);         //直线结束坐标
    glEnd(); 

    glBegin(GL_LINES);     
    glVertex2f(-15.0f, -5.0f);        //直线起始坐标 
    glVertex2f(0.0f, -5.0f);         //直线结束坐标
    glEnd(); 
    
    glBegin(GL_LINES);     
    glVertex2f(0.0f, -5.0f);        //直线起始坐标 
    glVertex2f(0.0f, 20.0f);         //直线结束坐标
    glEnd(); 

    // glBegin(GL_LINES);     
    // glVertex2f(10.0f, 0.0f);        //直线起始坐标 
    // glVertex2f(10.0f, 20.0f);         //直线结束坐标
    // glEnd(); 

    // glBegin(GL_LINES);     
    // glVertex2f(20.0f, 0.0f);        //直线起始坐标 
    // glVertex2f(20.0f, 20.0f);         //直线结束坐标
    // glEnd(); 

    // glBegin(GL_LINES);     
    // glVertex2f(30.0f, 0.0f);        //直线起始坐标 
    // glVertex2f(30.0f, 20.0f);         //直线结束坐标
    // glEnd(); 

    // glBegin(GL_LINES);     
    // glVertex2f(40.0f, 0.0f);        //直线起始坐标 
    // glVertex2f(40.0f, 20.0f);         //直线结束坐标
    // glEnd(); 

    // glBegin(GL_LINES);     
    // glVertex2f(50.0f, 0.0f);        //直线起始坐标 
    // glVertex2f(50.0f, 20.0f);         //直线结束坐标
    // glEnd(); 

    for (int i=0; i<=50;i+=10){
    glBegin(GL_LINES);     
    glVertex2f(i, 0.0f);        //直线起始坐标 
    glVertex2f(i, 20.0f);         //直线结束坐标
    glEnd(); 
    }

    glBegin(GL_LINES);     
    glVertex2f(60.0f, 0.0f);        //直线起始坐标 
    glVertex2f(60.0f, 80.0f);         //直线结束坐标
    glEnd(); 

    glBegin(GL_LINES);     
    glVertex2f(60.0f, 80.0f);        //直线起始坐标 
    glVertex2f(-15.0f, 80.0f);         //直线结束坐标
    glEnd();     

    glBegin(GL_LINES);     
    glVertex2f(0.0f, 60.0f);        //直线起始坐标 
    glVertex2f(0.0f, 80.0f);         //直线结束坐标
    glEnd(); 



    // glBegin(GL_LINES);     
    // glVertex2f(10.0f, 60.0f);        //直线起始坐标 
    // glVertex2f(10.0f, 80.0f);         //直线结束坐标
    // glEnd();     

    // glBegin(GL_LINES);     
    // glVertex2f(20.0f, 60.0f);        //直线起始坐标 
    // glVertex2f(20.0f, 80.0f);         //直线结束坐标
    // glEnd(); 

    // glBegin(GL_LINES);     
    // glVertex2f(30.0f, 60.0f);        //直线起始坐标 
    // glVertex2f(30.0f, 80.0f);         //直线结束坐标
    // glEnd(); 

    // glBegin(GL_LINES);     
    // glVertex2f(40.0f, 60.0f);        //直线起始坐标 
    // glVertex2f(40.0f, 80.0f);         //直线结束坐标
    // glEnd(); 

    // glBegin(GL_LINES);     
    // glVertex2f(50.0f, 60.0f);        //直线起始坐标 
    // glVertex2f(50.0f, 80.0f);         //直线结束坐标
    // glEnd(); 

    for (int i=0; i<=50;i+=10){
    glBegin(GL_LINES);     
    glVertex2f(i, 60.0f);        //直线起始坐标 
    glVertex2f(i, 80.0f);         //直线结束坐标
    glEnd(); 
    }

    glColor3f(100.0f,100.0f, 0.0f);

    glRectf(0.0f, 38.0f, 45.0f, 42.0f);

    glFlush();
}

void timestep(int n)
{
    glutTimerFunc((unsigned)n, timestep, n);
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE|GLUT_DEPTH);
    glutCreateWindow("parkinglot");
    glClearColor(255, 255, 255, 0.0);
    gluOrtho2D(-20, 70, -30, 85);
    glutDisplayFunc(draw_shape);
    glutTimerFunc(25, timestep, 25);
    glutMainLoop();
}