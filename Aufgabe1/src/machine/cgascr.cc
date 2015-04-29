/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cgascr.h"
#include "machine/io_port.h"

/** \todo implement **/
CGA_Screen::CGA_Screen(){
  screen = (unsigned char*) (0xb8000);
    setAttributes(7, 0, 0);
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

  IO_Port indexreg(0x3d4);
  IO_Port datareg(0x3d5);

  int position = (x+(y*80));

  indexreg.outb(15);
  datareg.outb(position & 0xff);
  indexreg.outb(14);
  datareg.outb((position >> 8) & 0xff);

  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const{
      IO_Port indexreg(0x3d4);
      IO_Port datareg(0x3d5);

      indexreg.outb(15);
      char cursor1 = datareg.inb();
      indexreg.outb(14);
      char cursor2 = datareg.inb();

      int position = (cursor1 & 0xff) | ((cursor2 & 0xff) << 8);

      x = (position)%80;
      y = (position)/80;
  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::show (unsigned short x, unsigned short y, char character, unsigned char attribute) {
  short position = 2 * (x + y * 80);

    screen[position] = character;
    screen[position+1] = attribute;

  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::print (const char* string, unsigned int n) {
  for(unsigned int i = 0; i < n; i++){
      unsigned short x,y;
      getpos(x,y);

      if(string[i] == '\n'||x >= 80){
        x = 0;
        y++;
      }
      else
        show(x++, y, string[i], attribute);

      if(y >= 25){
        scrollup();
        y = 25 - 1;
      }
      setpos(x, y);
    }

  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::scrollup () {
  for(int i = 0; i < 24; i++){
      for(int j = 0; j < 80; j++){
        short position = 2 * (i * 80 + j);
        screen[position] = screen[position + 80 * 2];
        screen[position + 1] = screen[position + 80 * 2 + 1];
      }
    }

    for(int i = 0; i < 80; i++)
      show(i, 24, ' ', attribute);



  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::clear () {
  /* ToDo: Insert Your Code Here */
}

/** \todo implement **/
void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink){
  fgColor %= 16;
    bgColor %= 8;

    if(blink){
           blink = 1;
       }

       this->attribute = (char)(fgColor | (bgColor<<4) | (blink<<7));
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
