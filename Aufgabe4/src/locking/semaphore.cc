#include "locking/semaphore.h"
#include "object/scheduler.h"
#include "object/lock.h"
#include "locking/scopedLock.h"

Semaphore::Semaphore(unsigned int value) : value(value){
}

void Semaphore::p(){
  ScopedLock scopedLock(lock);
	if(value==0) {
		scheduler.block(*this);
	} else {
		value--;
	}
}


/** \todo implement **/
void Semaphore::v(){
}

/** \todo implement **/
void  Semaphore::interrupt_signal(){
}
