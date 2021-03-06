/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                 S C O P E D - L O C K                                         *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __scoped_lock_include__
#define __scoped_lock_include__

#include "locking/lock.h"

/** \~german
 *
 * \~english
 * \brief Scoped lock
 *
 * This lock interface locks the supplied lock on creation and unlocks it, when the interface is destroyed.
 */
class ScopedLock {
  private:
    Lock& lock;
    bool nested;
  public: 
    /** \~german
     *  \~english
     *  \brief Constructor locking the supplied lock
     **/
    ScopedLock(Lock& lock) : lock(lock), nested(lock.locked()){
      if(!nested) {
        lock.lock();
      }
    }
    
    /** \~german
     *  \~english
     *  \brief Desctructor unlocking the registered lock
     **/
    ~ScopedLock(){
      if(!nested) {
        lock.unlock();
      }
    }
};

#endif
