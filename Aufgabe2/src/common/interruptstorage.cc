/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                               I N T E R R U P T _ S T O R A G E                               * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "common/interruptstorage.h"

#include "common/panic.h"

#include "config.h"

#include "object/kout.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

InterruptHandler* interrupts[16];
Panic panic;

InterruptStorage::InterruptStorage(){
	for(int i=0; i<16; i++) {
		interrupts[i] = &panic;



	}
}


void InterruptStorage::assign(int iNum, InterruptHandler& handler){ //iNUM 32-40 und handler ist unser keyboard
	 interrupts[iNum-MIN_INTERRUPT_NUMBER] = &handler; //zeiger von handler ins array
}

void InterruptStorage::handle(int iNum){
 	interrupts[iNum-MIN_INTERRUPT_NUMBER] -> trigger();
}
