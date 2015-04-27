/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                 S T R I N G B U F F E R                                       *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/strbuf.h"

/** \todo implement **/
Stringbuffer::Stringbuffer(){
   pos = 0;
  /* ToDo: Insert Your Code Here */
}


/** \todo implement **/
Stringbuffer::~Stringbuffer(){
  /* ToDo: Insert Your Code Here */
}
/** \todo implement **/
void Stringbuffer::put (char c) {
  buffer[pos] = c;
      pos++;

    if (pos>=BUFFERSIZE-1) {
      flush();
    }
  }

