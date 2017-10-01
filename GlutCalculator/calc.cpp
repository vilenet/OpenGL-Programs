#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
using namespace std;

float W = 500.0;
float H = 300.0;
//////////////////////////////////////////////////////////////////////////////////
class Circle
{
 public:
     float x1,y1,x2,y2;
     Circle(float X1=0.0,float Y1=0.0,float X2=0.0,float Y2=0.0): x1(X1), y1(Y1), x2(X2), y2(Y2)
     {}
     void draw();       
};

void Circle::draw()
{
    //glBegin(GL_LINE_LOOP);
        glColor3ub( 133, 133, 133);
        glRectf(this->x1, this->y1, this->x2, this->y2);
        //glRectf(0, 0, 40, 40);
    //glEnd();    
}
///////////////////////////////////////////////////////////////////////////////////

Circle c1(-W, -H/2, 20, 20);
Circle c2(0, 0, 20, 20);
Circle c3(0, 0, 20, 20);
Circle c4(0, 0, 20, 20);
//------------------------------
void Draw()
{    
    glClear(GL_COLOR_BUFFER_BIT);
       
        c1.draw();
        
       glColor3ub( 0, 0, 0); 
       
       glBegin(GL_LINES);

         glVertex2d(-W, -90);
         glVertex2d(W,  -90);
         
         glVertex2d(-W, -30);
         glVertex2d(W,  -30);
         
         glVertex2d(-W, 30);
         glVertex2d(W,  30);
         
         glVertex2d(-W, 90);
         glVertex2d(W,  90);


         
       glEnd();
    glutSwapBuffers();
}
//------------------------------
void Initialize()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-W/2, W/2, -H/2, H/2, -200.0, 200.0); 
    //glOrtho(-W, W, -H, H, -W, H); 
    glMatrixMode(GL_MODELVIEW);
}
//////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(100, 200);
    glutCreateWindow("lesson 3");
    glutDisplayFunc(Draw);
    Initialize();
    glutMainLoop();
    return 0;   
}
