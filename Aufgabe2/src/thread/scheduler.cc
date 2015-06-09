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
  // todo
}

void Scheduler::insert(Thread& that){
  // todo
}

void Scheduler::next()
{
  Thread* next = static_cast<Thread*>(threads.pop_front());
  if(!next){
    log << "No more threads, finished!" << endl;
    cpu.halt();
  }
  dispatch(*next);
}

void Scheduler::exit(){
  // todo
}

bool Scheduler::kill(Thread& that){
  // todo
  // and also change the return value

  return true;
}

void Scheduler::yield(){
  // todo
}

void Scheduler::preempt(){
  // todo
}
