/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                         T H R E A D                                           *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   INCLUDES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "thread/thread.h"
#include "object/lock.h"
#include "object/scheduler.h"
#include "object/log.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   METHODS                       #
\* * * * * * * * * * * * * * * * * * * * * * * * */

void Thread::kickoff(Thread* thread){
	 log << "Thread " << thread << " starts execution" << endl;
	  lock.unlock();
	  thread->yield();
	  while(true)
	    thread->exit();
  // todo
}

Thread::Thread() : context(this){}

Thread::~Thread(){
    exit();
}

void Thread::yield(){
  scheduler.yield();
}

void Thread::exit(){
 scheduler.exit();
}
