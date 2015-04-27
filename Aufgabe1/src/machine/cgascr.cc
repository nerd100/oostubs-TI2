/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cgascr.h"
#include "machine/io_port.h"

#define X_MAX 80
#define Y_MAX 25

static IO_Port cgi_i(0x3d4);
static IO_Port cgi_d(0x3d5);
/** \todo implement **/
CGA_Screen::CGA_Screen(){
  screen = (unsigned char*) (0xb8000);
    setAttributes(7, 0, 0);

    // init cursor
    //cgi_i.outb(14);
    //cgi_d.outb(0);

    //cgi_i.outb(15);
    //cgi_d.outb(0);
    setpos(0 ,0);
    clear();

  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
CGA_Screen::~CGA_Screen(){
  //nothing to do
  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::setpos (unsigned short x, unsigned short y) {
  if(x >= X_MAX) x = X_MAX - 1;

    if(y >= Y_MAX) y = Y_MAX - 1;

    if(x < 0) x = 0;

    if(y < 0) y = 0;

    unsigned short p = x + (y * X_MAX); // calc position
    unsigned char h = (unsigned char) (p >> 8);
    unsigned char l = (unsigned char) p;

    cgi_i.outb(14);
    cgi_d.outb(h);

    cgi_i.outb(15);
    cgi_d.outb(l);

  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const{
  cgi_i.outb(14);
    unsigned char h = cgi_d.inb();

    cgi_i.outb(15);
    unsigned char l = cgi_d.inb();

    unsigned short p = h; // calc position like in setpos
    p <<= 8;
    p |= l;

    y = p / X_MAX;
    x = p % X_MAX;

  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::show (unsigned short x, unsigned short y, char character, unsigned char attribute) {
  short pos = 2 * (x + y * X_MAX);

    screen[pos] = character;
    screen[pos + 1] = attribute;

  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::print (const char* string, unsigned int n) {
  for(unsigned int i = 0; i < n; i++){
      unsigned short x,y;
      getpos(x,y);

      if(string[i] == '\n'){
        x = 0;
        y++;
      }
      else
        show(x++, y, string[i], attribute);

      // adjusting cursor position
      if(x >= X_MAX){
        x = 0;
        y++;
      }
      if(y >= Y_MAX){
        scrollup();
        y = Y_MAX - 1;
      }
      setpos(x, y);
    }

  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::scrollup () {
  for(int i = 0; i < Y_MAX - 1; i++){
      for(int ii = 0; ii < X_MAX; ii++){
        short pos = 2 * (i * X_MAX + ii);
        screen[pos] = screen[pos + X_MAX * 2];
        screen[pos + 1] = screen[pos + X_MAX * 2 + 1];
      }
    }

    for(int i = 0; i < X_MAX; i++)
      show(i, Y_MAX - 1, '\0', attribute);

    // adjusting cursor position
    unsigned short x,y;
    getpos(x,y);
    if(y-- == 0){
      y = 0;
      x = 0;
    }
    setpos(x,y);
  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::clear () {
  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink){
  fgColor %= 16; // cutting off not used bits
    bgColor %= 8;

    CGA_Screen::fgColor = fgColor;
    CGA_Screen::bgColor = bgColor;
    CGA_Screen::blink = blink;

    unsigned char at = 0;

    if(blink) at++;
    at <<= 3;
    at += bgColor;
    at <<= 4;
    at += fgColor;

    attribute = at;
  }

  void CGA_Screen::setFG(int v){
    setAttributes(v, CGA_Screen::bgColor, CGA_Screen::blink);
  }

  void CGA_Screen::setBG(int v){
    setAttributes(CGA_Screen::fgColor, v, CGA_Screen::blink);
  }

  void CGA_Screen::setBL(bool v){
    setAttributes(CGA_Screen::fgColor, CGA_Screen::bgColor, v);
  }
