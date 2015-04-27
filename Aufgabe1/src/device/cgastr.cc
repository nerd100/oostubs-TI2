/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S T R E A M                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "device/cgastr.h"

/** \todo implement **/
void CGA_Stream::flush () {
  print(buffer, pos);
    pos = 0;
  /* ToDo: Insert Your Code Here */
}
/** \todo implement **/
void CGA_Stream::setAttributes(int fgColor, int bgColor, bool blink){
  CGA_Screen::setAttributes(fgColor, bgColor, blink);
  /* ToDo: Insert Your Code Here */
}
void CGA_Stream::setFG(int v){
  this->CGA_Screen::setFG(v);
}

void CGA_Stream::setBG(int v){
  this->CGA_Screen::setBG(v);
}

void CGA_Stream::setBL(bool v){
  this->CGA_Screen::setBL(v);
}
