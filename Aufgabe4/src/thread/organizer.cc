#include "thread/organizer.h"
#include "object/lock.h"
#include "locking/scopedLock.h"
#include "common/null.h"
#include "object/log.h"

void Organizer::block(Waitingroom& room){
    room.push_back(*active());
    active()->waiting_in(&room);
    log << "Suspending Thread " << active() << endl;
    next();
}
 
/** \todo implement **/
void Organizer::wakeup(Customer& customer){
  
   log << "Reactivating Thread " << &customer << endl;
}

/** \todo implement **/
bool Organizer::kill(Customer& that){
   
   return true;  //<-- Platzhalter
}

Customer* Organizer::active() const{
    return static_cast<Customer*>(Scheduler::active());
}
