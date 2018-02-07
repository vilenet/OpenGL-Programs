#include <GL/glut.h>
#include <string> 
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <iostream>

float W = 500.0;
float H = 300.0;

char* int_to_char(int n){
     int radix = 10;  
     char buffer[20]; 
     char *p;  
     p = itoa(n+1,buffer,radix);
     return p;
}
//////////////////////////////////////////////////////////////////////////////
class Button
{
    private:
        float X1, X2, Y1, Y2; 
        char* str;
        float R,G,B;  
        bool drawn_button;
        int TEXT_INDEX;
    public: 
       Button(): X1(0), X2(0), Y1(0), Y2(0), 
                 str(""), 
                 R(0.6),G(0.8),B(0.9),
                 drawn_button(false)
                 {}
       
       Button(int x, int y, char* stroke): 
                 X1(x), X2(80+x), Y1(y), Y2(25+y),
                 str(stroke),
                 R(0.6),G(0.8),B(0.9),
                 drawn_button(false) 
                 {}
       
       void resize(int x, int y){ X2=x; Y2=y; }
       void setcolor(float r, float g, float b){ R=r; G=g; B=b; }
       
       int callback( int button, int updown, int x, int y ){
         int UPorDown=0;
         switch(button){
           case GLUT_LEFT_BUTTON:  
             if(((x >= X1 && x <= X2) && (y >= Y1 && y <= Y2)) && updown==GLUT_DOWN  && drawn_button==true)
                UPorDown = 1;
             else
                UPorDown = 0;
           break;   
           case GLUT_RIGHT_BUTTON:  break;  
         }//state {GLUT_UP, GLUT_DOWN}        
         return UPorDown; 
       }
       
       void setText(char* string){
         int count = strlen(string);    
         glColor3f(0,0,0);  
         char* c;
         glRasterPos2f((X1+X2)/2-((count+1)*4),(Y1+Y2)/2+5);
         for (c = string; *c != '\0'; c++) { glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c); }
       }
       void draw(){      
         drawn_button=true;     
         glColor3f(R,G,B);   
         glRectf(X1,Y1,X2,Y2);
         setText(str); 
          
         glLineWidth(1.5f);
    
         glBegin(GL_LINES); 
           glColor3f(0.9,0.9,0.9); 
           glVertex2f(X1,Y1); 
           glVertex2f(X2,Y1);  
           glVertex2f(X1,Y1); 
           glVertex2f(X1,Y2);    
             
           glColor3f(0.5,0.5,0.5);                
           glVertex2f(X2,Y1); 
           glVertex2f(X2,Y2); 
           glVertex2f(X1,Y2); 
           glVertex2f(X2,Y2);           
         glEnd();   
       }   
};

////////////////////////////////////////////////////////////////////////////////////
void line(int x,int y,int x2,int y2, float thickness)
{
  glLineWidth(thickness);  
  glBegin(GL_LINES); 
    glVertex2f(x,y); 
    glVertex2f(x2,y2);   
  glEnd();      
}


/////////////////////// TEXT BOX  ///////////////////////////////////////////////
/*class TextBox
{
    private:
        float X1, X2, Y1, Y2; 
        std::vector<std::string> TEXT;
        int TEXT_INDEX;
        int ENDL;
        int KEY;
    public: 
       TextBox(): X1(0), X2(0), Y1(0), Y2(0), TEXT_INDEX(0),ENDL(1),KEY(0) {}
       TextBox(int x, int y): X1(x), X2(150+x), Y1(y), Y2(30+y), TEXT_INDEX(0),ENDL(1),KEY(0) {}
       //---------------
       void resize(int x, int y){ X2=x; Y2=y; }
       
       //---------------   
       void setText(int x, int y, std::string str){
         glColor3f(0,0,0);  
         const char* c;
         glRasterPos2f(x,y);
         for (c = &str[0]; *c != '\0'; c++) { glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c); }
       }
       
       //--------------
       void inputText(char str, int key){  
            
         TEXT.push_back("");   
         KEY = key;  
          
         if(KEY == 13){
           TEXT_INDEX++;
           TEXT.push_back("\n");
           //TEXT[TEXT_INDEX] += "\n";          
         }
         
         TEXT[TEXT_INDEX] += str;
       }
       
       //---------------
       void drawText(){    
         for(int i=0; i < TEXT.size(); i++){    
            if(TEXT[i] == "\n")  
              ++ENDL;
              
            setText(5+X1+(i*20), Y1+(20*ENDL), TEXT[i]);    
         }
      }
       //---------------
       void draw(){      
         glColor3f(1,1,1);   
         glRectf(X1,Y1,X2,Y2);
         
         glLineWidth(0.1f);
         glColor3f(0.4,0.4,0.4); 
         glBegin(GL_LINES); 
           glVertex2f(X1,Y1); 
           glVertex2f(X2,Y1);  
           glVertex2f(X1,Y1); 
           glVertex2f(X1,Y2);                  
           glVertex2f(X2,Y1); 
           glVertex2f(X2,Y2); 
           glVertex2f(X1,Y2); 
           glVertex2f(X2,Y2);           
         glEnd();   
         
         drawText();
       }   
       
       
};
*/
