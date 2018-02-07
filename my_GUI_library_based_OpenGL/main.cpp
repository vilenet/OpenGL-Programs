#include "gui.h"
#include "Textblock.h"

int mouseButton;
int mouseState;
int mouseX;
int mouseY;

TextBox textbox(10, 50);
////////////////    MOUSE    ////////////////////////////////////////
void MouseButton(int button,int state,int x,int y)
{
	mouseButton = button;
	mouseState  = state;
	mouseX      = x;
	mouseY      = y;
	
	glutPostRedisplay();  // перерисовать
}
//-------------------  END MOUSE  ------------------------------------
void init(void) 
{ 
   //glClearColor(1.0,1.0,1.0,0.0); 
   glClearColor(0.8,0.8,0.8,1.0); 
    glShadeModel(GL_SMOOTH); 
} 
//-----------------------------------------------------------
void keyboard(unsigned char key, GLint x, GLint y)
{
    int numkey = key;
    textbox.inputText(key, numkey);

    glutPostRedisplay();
}
//--------------------------------------------------------------------
void setText(int textX, int textY, char* string){
      glColor3f(0,0,0);  
      char* c;
      glRasterPos2f(textX,textY);
      for (c = string; *c != '\0'; c++) { glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c); }
}
//-----------------------------------------------------------------------
void display(void) 
{ 
   glClear(GL_COLOR_BUFFER_BIT);  
   

   Button menu1(0,0, "Run");
   menu1.resize(50,40);
   menu1.setcolor(0.0,0.8,0.0);
   menu1.draw();
   
   glColor3f(0.5,0.5,0.5); 
   line(0,41, W,41, 1.0f);
   

   Button button(10,H-40, "Ok");
   button.draw();
   int click = button.callback(mouseButton,mouseState,mouseX,mouseY);
   if(click == 1)
     setText(150, H-20, "Button clicked!");
     
   //TextBox textbox(10, 50);
   //textbox.resize(W-10, H-45); 
   //textbox.draw(); 
     
   
   textbox.resize(W-10, H-45); 
   textbox.draw();  
   
   
   
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
   
   glutMouseFunc(MouseButton);
   glutKeyboardFunc(keyboard);
   
   init(); 
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
  // timer();
   glutMainLoop(); 
   
   
   return 0; 
}
/////////////////////////////////////////////////////////////////////////////




















