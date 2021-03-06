/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                          D I S P A T C H E R                              *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __dispatch_include__
#define __dispatch_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "thread/thread.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \brief Managing currently active threads.
 *
 * The dispatcher changes the currently active thread if the system. It keeps
 * track of all effectively running therads and management the transition of
 * one thread to another. In the current setup only single CPU systems are
 * supported.
 *
 **/
class Dispatcher {
private:
  /** 
   * \~english
   * \brief The currently active thread
   */
   Thread* current;
  

public:
  /** 
   * \~english
   * \brief Default constructor.
   */
  Dispatcher() : current(0){}

  /** \brief Starts the scheduling
   *
   * The scheduling is started through a transition to the first thread
   * available in the system. This transition is one way. The original context
   * is not saved and can therefore never be restored.
   *
   * \param first Reference of the first thread scheduled in the system.
   */
  void start(Thread& first);

  /** \brief  Switch to another thread
   *
   * The new thread is specified as the parameter of the call. During the
   * transition the old thread context is saved and the new thread context is
   * installed on the CPU.
   *
   * \param next Reference to the new active thread.
   */
  void dispatch(Thread& next);

  /** \brief Returns the currently active thread.
   *
   * \return pointer to the currently active thread.
   */
  Thread* active() const{
		return current;
  }
};

#endif
