/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                            P I C                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/pic.h"
#include "machine/io_port.h"
#include "object/cpu.h"
#include "object/kout.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */


PIC::PIC() {
  IO_Port ctrl_1(0x20), ctrl_2(0xa0), mask_1(0x21), mask_2(0xa1);


  ctrl_1.outb(0x11);
  ctrl_2.outb(0x11);
  

  mask_1.outb(32);
  mask_2.outb(40);
  

  mask_1.outb(4);
  mask_2.outb(2);
  

  mask_1.outb(2);
  mask_2.outb(2);
  

  mask_1.outb(0xFB);
  mask_2.outb(0xFF);


}

PIC::~PIC(){

}

void PIC::allow(Interrupts interrupt){
  IO_Port mask_1(0x21), mask_2(0xa1);
  unsigned char help;
  unsigned short i = interrupt-32;
  if(i<8) {
	  help = mask_1.inb();		//kopiere aktuelle maske
	  help &= ~(1<<i);		//shifte um interrupt und bitweise negation/ durch "und" wird interrupt auf jedenfall erlaubt
	  mask_1.outb(help);		//gibt neue maske zurück

    //master
  } else {
	  help = mask_2.inb();
	  help &= ~(1<<(i-8));
	  mask_2.outb(help);
    //slave
  }
}


void PIC::forbid(Interrupts interrupt){
  IO_Port mask_1(0x21), mask_2(0xa1);
  unsigned char help;
  unsigned short i = interrupt-32;
  if(i<8) {
	  help = mask_1.inb();		//kopiere aktuelle maske
	  help |= (1<<i);		// durch "oder" wird immer der interrupt verboten
	  mask_1.outb(help);		// gib maske zurück
    //master
  } else {
	  help = mask_2.inb();
	  help |= (1<<(i-8));
	  mask_2.outb(help);
    //slave
  }
}

void PIC::ack(Interrupts interrupt){  //0x20 = EOI(end of interrupt) muss gesetzt werden um
  IO_Port ctrl_1(0x20), ctrl_2(0xa0);	//anzuzeigen das interrupt beendet ist
  ctrl_1.outb(0x20);
  if (interrupt>=40) {
    ctrl_2.outb(0x20);
  }
}
