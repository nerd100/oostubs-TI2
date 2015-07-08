/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                         S C H E D U L E R                                     *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   INCLUDES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "thread/scheduler.h"
#include "locking/scopedLock.h"
#include "common/null.h"
#include "object/lock.h"
#include "object/log.h"
#include "object/cpu.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   METHODS                       #
\* * * * * * * * * * * * * * * * * * * * * * * * */

Scheduler::Scheduler() : started(false){}

Scheduler::~Scheduler(){
  started=false;
}

void Scheduler::start(){
	ScopedLock scopedLock(lock);
	  started=true;
	  Thread* next = static_cast<Thread*>(threads.pop_front());
	  if(next){
	    log << "System starts first Thread " << next << endl;
	    Dispatcher::start(*next);
	  }else{
	    log << "System starts idle Thread " << endl;
	    Dispatcher::start(idle);

	  }

  // todo
}

void Scheduler::insert(Thread& that){
	//ScopedLock scopedLock(lock);
		threads.push_back(that);
	  log << "Thread " << &that << " is ready" << endl;
  // todo
}

void Scheduler::next()
{
  Thread* next = static_cast<Thread*>(threads.pop_front()); //threads ist unsere queue
  if(!next){
    log << "No more threads, finished!" << endl;
    cpu.halt();
  }
  dispatch(*next);
}

void Scheduler::exit(){
	 ScopedLock scopedLock(lock);
	  log << "Thread " << active() << " ended" << endl;
	  next();
  // todo
}

bool Scheduler::kill(Thread& that){
	if(&that==active()){
	    threads.remove(that);
	    next();
	    return true;
	  }
	  return threads.remove(that);
  // todo
  // and also change the return value

  return true;
}

void Scheduler::yield(){
	ScopedLock scopedLock(lock);
	  preempt();
  // todo
}

void Scheduler::preempt(){
	if(!started)
	    return;
	  if(active())
	    threads.push_back(*active());
	  next();
  // todo
}
void Scheduler::Idle::action(){
  while(true){
    cpu.halt();
    yield();
  }
}
