/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/o_stream.h"

/** \brief \todo implement **/
O_Stream::O_Stream() : Stringbuffer(), fgColor(WHITE), bgColor(BLACK), blink(false), base(dec){
  //nothing to do
  /* ToDo: Insert Your Code Here */
}

/** \brief \todo implement **/
O_Stream::~O_Stream(){
  //nothing to do
  /* ToDo: Insert Your Code Here */
}

/** \brief \todo implement **/
O_Stream& O_Stream::operator << (char value) {
  put(value);
  /* ToDo: Insert Your Code Here */
  return *this;
}

O_Stream& O_Stream::operator << (unsigned char value) {
  return *this << (char)value;
}

O_Stream& O_Stream::operator << (char* value) {
  return *this << (const char*)value;
}

/** \brief \todo implement **/
O_Stream& O_Stream::operator << (const char* value) {
  for(int n = 0; value[n]!='\0'; n++) {
      put(value[n]);
    }
  return *this;
}

O_Stream& O_Stream::operator << (short value) {
  return *this << (long)value;
}

O_Stream& O_Stream::operator << (unsigned short value) {
  return *this << (unsigned long)value;
}


O_Stream& O_Stream::operator << (int value) {
  return *this << (long)value;
}


O_Stream& O_Stream::operator << (unsigned int value) {
  return *this << (unsigned long)value;

}

void O_Stream::help(unsigned long v){

  if (v < base) {
        if (v < dec) {
            put( (char) ('0' + v) );
        } else {
            put( (char) ('7' + v) );
        }
    } else {
        help((unsigned long) (v / base));
        help((unsigned long) (v % base));
    }
}


/** \brief \todo implement **/
O_Stream& O_Stream::operator << (long value) {
  if(base > 10){
        put('0');
        put('x');
      }else if(value < 0){
        put('-');
        value *= -1;
      }

      if (base > 10) {
        int length = 0;
        const int numOfDigits = 8;

        int t = value;
        while (t != 0) {
          t /= 16;
          length++;
        }

        if (value == 0) length++;

        if (length < numOfDigits) {
          for (int i = 0; i < numOfDigits - length; i++)
            put('0');
        }
      }

      help((unsigned long) value);

      return *this;
}

/** \brief \todo implement **/
O_Stream& O_Stream::operator << (unsigned long value) {
  if(base > 10){
      put('0');
      put('x');
    }

    help(value);
  return *this;
}

/** \brief \todo implement **/
O_Stream& O_Stream::operator << (void* value) {
  *this << (unsigned long) value;
  /* ToDo: Insert Your Code Here */
  return *this;
}

O_Stream& O_Stream::operator << (FGColor color){
  flush();
  fgColor = color.color;
  setAttributes(fgColor, bgColor, blink);
  return *this;
}


O_Stream& O_Stream::operator << (BGColor color){
  flush();
  bgColor = color.color;
  setAttributes(fgColor, bgColor, blink);
  return *this;
}


O_Stream& O_Stream::operator << (Blink blink){
  flush();
  this->blink = blink.blink;
  setAttributes(fgColor, bgColor, this->blink);
  return *this;
}

/** \brief \todo implement **/
O_Stream& endl (O_Stream& os) {
  os.put('\n');
    os.flush();
  /* ToDo: Insert Your Code Here */
  return os;
}


O_Stream& bin (O_Stream& os) {
  os.base = O_Stream::bin;
  return os;
}


O_Stream& oct (O_Stream& os) {
  os.base = O_Stream::oct;
  return os;
}


O_Stream& dec (O_Stream& os) {
  os.base = O_Stream::dec;
  return os;
}


O_Stream& hex (O_Stream& os) {
  os.base = O_Stream::hex;
  return os;
}

O_Stream& O_Stream::operator << (O_Stream& (*f) (O_Stream&)) {
  return f(*this);
}
