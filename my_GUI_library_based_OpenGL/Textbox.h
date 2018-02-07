#include <GL/glut.h>
#include <string> 
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <iostream>

void *font=(int*)GLUT_BITMAP_9_BY_15;
////////////////////////////////////////////////////////////////////////////
class TextBox
{ 
  private:
    int X,Y,X2,Y2;    
    int RASTERPOS[2];
    int LINE_HEIGHT;
    int LINE_WIDTH;
    int MARGIN;  
    int TEXT_INDEX;    
    std::vector<std::string> TEXT;
    
  public:  
    TextBox():
         X(0),Y(0),X2(0),Y2(0),
         LINE_HEIGHT(0),
         LINE_WIDTH(0),
         TEXT_INDEX(0),
         MARGIN(0)
         {}
         
    TextBox(int x, int y):
         X(x),Y(y),X2(150+x),Y2(40+y),
         LINE_HEIGHT(15),
         LINE_WIDTH(9),
         TEXT_INDEX(0),
         MARGIN(10)
         {}     
    
    void resize(int x, int y){ X2=x; Y2=y; }          
    void setText(int x, int y, std::string str);
    void inputText(unsigned char key);
    void draw(); 
};
//////////////////////////////////////////////////////////////////////////
void TextBox::setText(int x, int y, std::string str){
    const char *c;
    glRasterPos2f(x, y);
    for (c=&str[0]; *c != '\0'; c++){
      glGetIntegerv(GL_CURRENT_RASTER_POSITION, RASTERPOS);
      if (*c != '\n') {
        if (RASTERPOS[0] > X2-(4*LINE_WIDTH+10)) {
          y += LINE_HEIGHT*15;
          glRasterPos2f(x, y);
        }           
        glutBitmapCharacter(font, *c);
}}}
//-------------------------------------------------------
void TextBox::inputText(unsigned char key){
    switch (key){
      // ESCAPE
      case 27:  exit (0);  break;
      // ENTER
      case 13: TEXT_INDEX++; TEXT.push_back("\n"); break;
      // BACKSPACE
      case 8:
        if(TEXT.size() > 0 && TEXT[TEXT_INDEX].length() > 0) {
          TEXT[TEXT_INDEX] = TEXT[TEXT_INDEX].substr(0, TEXT[TEXT_INDEX].size() - 1);
        }break;
      //input text
      default:
        if (TEXT.size() == 0) {  TEXT.push_back(""); }
        
        int stride = (W - (4*LINE_WIDTH))/LINE_WIDTH - 3;
        if (TEXT[TEXT_INDEX].length() >= stride) {
            TEXT_INDEX++;
            TEXT.push_back("");
        }
        
        TEXT[TEXT_INDEX] += key;
        break;
} }
//-------------------------------------------------------
void TextBox::draw(){
    glColor4f(1, 1, 1, 1);
    glRectf(X, Y, X2, Y2);
    
    glLineWidth(0.1f);
    glColor3f(0.4,0.4,0.4); 
    glBegin(GL_LINES); 
      glVertex2f(X,Y); 
      glVertex2f(X2,Y);  
      glVertex2f(X,Y); 
      glVertex2f(X,Y2);                  
      glVertex2f(X2,Y); 
      glVertex2f(X2,Y2); 
      glVertex2f(X,Y2); 
      glVertex2f(X2,Y2);           
    glEnd();   
     
    glColor3f(0,0,0);
    int visibleLines = (Y2 - LINE_HEIGHT) / LINE_HEIGHT - 3;
    int x = 1;
    int i = 0;
    if(TEXT.size() > visibleLines) {
      i = TEXT.size() - visibleLines;
    }
    for(; i != TEXT.size(); i++) {
	  setText(X+MARGIN, (Y + 5) + LINE_HEIGHT * (x*15), TEXT[i]);
      x++;
    }
}
//--------------------------------------------------------------




















