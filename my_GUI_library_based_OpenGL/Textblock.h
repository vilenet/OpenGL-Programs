#include <GL/glut.h>
#include <string> 
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <iostream>

///////////////////////////////////////////////////////////////
class TextBox
{
    private:
        float X1, X2, Y1, Y2; 
        std::vector<std::string> TEXT;
        int TEXT_INDEX;
        int ENDL;
        int KEY;
        int RASTERPOS[2];
        int LINE_WIDTH;
        int LINE_HEIGHT;
        int MARGIN;
    public: 
       TextBox(): 
            X1(0), X2(0), Y1(0), Y2(0), 
            TEXT_INDEX(0),ENDL(1),KEY(0),
            LINE_WIDTH(9),LINE_HEIGHT(15),
            MARGIN(10)
            {}
            
       TextBox(int x, int y): 
            X1(x), X2(150+x), Y1(y), Y2(30+y), 
            TEXT_INDEX(0),ENDL(1),KEY(0),
            LINE_WIDTH(9),LINE_HEIGHT(15),
            MARGIN(10) 
            {}
       //---------------
       void resize(int x, int y){ X2=x; Y2=y; }
       
       //---------------   
       void setText(int x, int y, std::string str)
       {
         glColor3f(0,0,0);  
         
         const char* c;
         glRasterPos2i(x,y);
         for (c = &str[0]; *c != '\0'; c++)
         {
           glGetIntegerv(GL_CURRENT_RASTER_POSITION, RASTERPOS);
           if (*c != '\n') 
           {
             //if (RASTERPOS[0] > X2-(4*LINE_WIDTH)) 
             if (RASTERPOS[0] > X2-10) 
             {
                y += LINE_HEIGHT*15;
                glRasterPos2f(x, y);
             }
             glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
           }
         }
       }
       //--------------
       void inputText(unsigned char str, int key){  
         switch(str)
         {  
           case 13:  TEXT_INDEX++; TEXT.push_back("\n"); break;
           
           default:    
            if (TEXT.size() == 0) {  TEXT.push_back(""); } 
         
            int stride = (X2- (3*LINE_WIDTH))/LINE_WIDTH - 3;
            if (TEXT[TEXT_INDEX].length() >= stride) {
                TEXT_INDEX++;
                TEXT.push_back("");
            }
         
            TEXT[TEXT_INDEX] += str;
            break;
          }
       }
       //---------------
       void drawInputText()
       {
         int visibleLines = (H * 0.3) / LINE_HEIGHT - 1;
         int x = 1;
         int i = 0;
         if (TEXT.size() > visibleLines) {
           i = TEXT.size() - visibleLines;
         }
         for(; i != TEXT.size(); i++) {
           setText(X1+MARGIN/2, Y1 + LINE_HEIGHT * (x*18), TEXT[i]);
           x++;
         }   
       }
       //------------------
       void draw(){      
         glColor3f(1,1,1);   
         glRectf(X1,Y1,X2,Y2);
         
         drawInputText();
       }   
};
//////////////////////////////////////////////////////////////
















