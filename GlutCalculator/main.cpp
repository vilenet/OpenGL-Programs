#include  <GL/glut.h>
#include <string> 
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <iostream>


float W = 500.0;
float H = 300.0;

int x,y;
char* ch;

int leftClik = 0;

int textX = 10;
int textY = 30;
int n=0;

char* arr="0";
char  s1[100];

int size=0;

std::vector<char*> v;

std::string leftop = ""; // ????? ???????
std::string operation = ""; // ???? ????????
std::string rightop = ""; // ?????? ???????
//-----------------------------------------------------------------
template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss<< val;
    return oss.str();
}
////////////////////////////////////////////////////////////////////////
class Button
{     float R,G,B;
      float X1, X2, Y1, Y2;
      char* simvol;
      bool state;
      int Clik;
      
  public: 
    Button(): R(0.5), G(0.5), B(0.5), state(false), Clik(0){}  
    
    void setText(char* string){
      glColor3f(0,0,0);  
      char* c;
      glRasterPos2f((X1+X2)/2,(Y1+Y2)/2);
      for (c = string; *c != '\0'; c++) { glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c); }
    }
    //----------------------------------------------------------------    
    void Update_RightOp()
    {
        int num1 = atoi(leftop.c_str());
        int num2 = atoi(rightop.c_str());
       
        if(operation == "+")rightop = toString(num1 + num2);
        if(operation == "-")rightop = toString(num1 - num2);
        if(operation == "*")rightop = toString(num1 * num2);
        if(operation == "/")rightop = toString(num1 / num2);
         
      }    
    //----------------------------------------------------------------    
    void Draw(float x1, float y1, float x2, float y2, char* string, int ax, int ay, bool clik)
    { 
       X1=x1; X2=x2; Y1=y1; Y2=y2;
       Clik=clik;
       simvol=string;
            
       if((ax >= X1 && ax <= X2) && (ay >= Y1 && ay <= Y2)){  glColor3f(0.7,0.7,0.7);}
       else{ glColor3f(0.8,0.8,0.8); }
          
       if(((ax >= X1 && ax <= X2) && (ay >= Y1 && ay <= Y2)) && Clik==1)
       { 
            v.push_back(simvol);     
            strcat(s1, v[size]);
            size++;
            leftClik=0; 
            
    
            if(simvol == "clear"){ 
              v.clear();  
              size=0;
              for(int i=0; i<100; i++)
                strcpy(s1, "");
            }
            // - - - - - - - - - - - - - - - - - - - - - - - - 
            // если текст - это число
            if( isdigit(*simvol))
            {
                
                // если операция не задана
                if (operation == ""){
                    // добавляем к левому операнду
                    leftop += *simvol;
                }
                else{
                    // иначе к правому операнду
                    rightop += *simvol;
                }
            }
            // Если текст - это не число
            else
            {
               // Если равно то выводим результат операции
               if (simvol == "=")
               {
                 Update_RightOp();
                 
                 char *chrstr = new char[rightop.length() + 1];
                 strcpy(chrstr, rightop.c_str());
                 //v.push_back(chrstr);
                 //size++;
                 strcat(s1, chrstr);
                 
                 operation = "";
                 delete [] chrstr; 
               }  
               // получаем операцию
               else
               {
                  if (rightop != "")
                  {
                    Update_RightOp();
                    leftop = rightop;
                    rightop = "";
                  }
                  operation = *simvol;  
               }
            }
            // - - - - - - - - - - - - - - - - - - - - - - - -
       }  
       glRectf(x1,y1,x2,y2);
       
       setText(string);
       
       glBegin(GL_LINES); 
         glVertex2f(X1,Y1); 
         glVertex2f(X2,Y1);     
         glVertex2f(X2,Y1); 
         glVertex2f(X2,Y2); 
         glVertex2f(X1,Y2); 
         glVertex2f(X2,Y2);   
         glVertex2f(X1,Y1); 
         glVertex2f(X1,Y2);      
       glEnd();   
    }  
};
////////////////    MOUSE    ////////////////////////////////////////
void MouseMove(int ax,int ay){
     int radix = 10;  
     char buffer[20]; 
     char *p;  
     p = itoa(ay+1,buffer,radix);
     glutSetWindowTitle(p);
     
     x=ax;
     y=ay;
}

void MousePressed(int button, int state, int x, int y){ 
    switch(button){
      case GLUT_LEFT_BUTTON: leftClik=state;  glutSetWindowTitle("left Button pressed"); break;
      case GLUT_RIGHT_BUTTON: glutSetWindowTitle("Right Button pressed"); break;  
    }
    //state {GLUT_UP, GLUT_DOWN}
}

void MousePressedMove(int ax, int ay){
    glutSetWindowTitle("MousePressedMove called");
}
//-------------------  END MOUSE  ------------------------------------
void init(void) 
{ 
   glClearColor(1.0,1.0,1.0,0.0); 
   //glShadeModel(GL_FLAT); 
    glShadeModel(GL_SMOOTH); 
} 
//---------------------------------------------------------------
Button ButtonMas[16];
//----------------------------------------------------------------------  
void setText(char* string){
      glColor3f(0,0,0);  
      char* c;
      glRasterPos2f(textX,textY);
      for (c = string; *c != '\0'; c++) { glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c); }
}
//-----------------------------------------------------------------------
void display(void) 
{ 
   glClear(GL_COLOR_BUFFER_BIT);  

   ButtonMas[0].Draw(0, H/5*4 , W/4, H/5*5,"0", x,y,  leftClik);
   ButtonMas[1].Draw(0, H/5*3 , W/4, H/5*4,"1", x,y,  leftClik);
   ButtonMas[2].Draw(0, H/5*2 , W/4, H/5*3,"4", x,y,  leftClik);
   ButtonMas[3].Draw(0, H/5*1 , W/4, H/5*2,"7", x,y,  leftClik);
   ButtonMas[4].Draw(W/4, H/5*3 , W/4*2, H/5*4,"2", x,y,  leftClik);
   ButtonMas[5].Draw(W/4*2, H/5*3 , W/4*3, H/5*4,"3", x,y,  leftClik);
   ButtonMas[6].Draw(W/4, H/5*2 , W/4*2, H/5*3,"5", x,y,  leftClik);
   ButtonMas[7].Draw(W/4*2, H/5*2 , W/4*3, H/5*3,"6", x,y,  leftClik);
   ButtonMas[8].Draw(W/4, H/5*1 , W/4*2, H/5*2,"8", x,y,  leftClik);
   ButtonMas[9].Draw(W/4*2, H/5*1 , W/4*3, H/5*2,"9", x,y,  leftClik);
   ButtonMas[10].Draw(W/4, H/5*4 , W/4*2, H/5*5,"=", x,y,  leftClik);
   ButtonMas[11].Draw(W/4*2, H/5*4 , W/4*3, H/5*5,"clear", x,y,  leftClik);
   ButtonMas[12].Draw(W/4*3, H/5*4 , W/4*4, H/5*5,"-", x,y,  leftClik);
   ButtonMas[13].Draw(W/4*3, H/5*3 , W/4*4, H/5*4,"+", x,y,  leftClik);
   ButtonMas[14].Draw(W/4*3, H/5*2 , W/4*4, H/5*3,"/", x,y,  leftClik);
   ButtonMas[15].Draw(W/4*3, H/5*1 , W/4*4, H/5*2,"*", x,y,  leftClik);

     
   setText(s1);
   
    
   glFlush(); 
} 
//-----------------          RESHAPE       ------------------------------------  
void reshape(int w,int h) 
{ 
   glViewport(0,0,(GLsizei) w, (GLsizei) h); 
   glMatrixMode(GL_PROJECTION); 
   glLoadIdentity();  
   gluOrtho2D(0.0, (GLfloat) W, (GLfloat) H, 0.0);   
   glMatrixMode(GL_MODELVIEW);  
} 
//------------------         TIMER        ------------------------------------
void timer(int = 0)
{
   display();
   glutTimerFunc(10, timer, 0);   
}
//==================          MAIN        ==================================
int main(int argc, char **argv) 
{   
   glutInit(&argc,argv); 
   glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 
   glutInitWindowSize(W,H); 
   glutInitWindowPosition(100,100); 
   glutCreateWindow("Line Stipple Patterns"); 
   
   glutMotionFunc(MousePressedMove);
   glutPassiveMotionFunc(MouseMove);
   glutMouseFunc(MousePressed);
   
   init(); 
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   timer();
   glutMainLoop(); 
   
   return 0; 
}
/////////////////////////////////////////////////////////////////////////////






