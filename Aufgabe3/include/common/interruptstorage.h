/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                               I N T E R R U P T _ S T O R A G E                               * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __interrupt_storage_include__
#define __interrupt_storage_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "common/interrupthandler.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** 
 * \~german
 * \brief Administrationseinheit für die Interruptweitergabe
 * 
 * Diese Klasse abstrahiert die Verwaltung und Ausführung von Interrupts. Sie ermöglicht dem
 * System für jeden Hardware- und jeden Softwareinterrupt eine entsprechende 
 * Behandlungsroutine zu vergeben und auszuführen.
 * 
 * \~english
 * \brief Interrupt forwarding administration unit
 *
 * This class is an abstraction of the administration and exeuction of interrupts. It
 * enables the system to define an appropriate handling routine for every hard
 * and software interrupt and execute it.
 **/
class InterruptStorage {  

  public:
    /** 
     * \~german
     * \brief Standardkonstruktor
     * 
     * Er initialisiert das Array von Handler-Zeigern mit dem \ref Panic -Handler.
     * 
     * \~english
     * \brief Default constructor
     *
     * initialising the map with the Panic -Handler. 
     **/
    InterruptStorage ();
    
    /** 
     * \~german
     * \brief bindet ein \ref InterruptHandler Objekt an einen speziellen Interrupt
     * 
     * \param iNum 
     *   Zahl des Interrupts, welche mit dem Handler behandelt werden soll
     * \param handler 
     *   Referenz auf den Handler für den Interrupt
     * 
     * \~english
     * \brief assign a Handle to a specific interrupt
     *
     * \param iNum 
     *   number of the interrupt the Handle object will be assigned to
     * \param handler 
     *   reference of the Handle containing the handling routine for the interrupt
     */
    void assign(int iNum, InterruptHandler& handler) ;
    
    /** 
     * \~german
     * \brief Führt den Handler für einen speziellen Interrupt aus
     *
     * \param iNum 
     *   Nummer des aufgetretenen Interrupts
     * 
     * \~english
     * \brief execute the handler of a specific interrupt
     *
     * \param iNum
     *   number of occured interrupt
     */
    void handle(int iNum);

    /** \brief Fetch the currently active interrupt if there is one
     *
     *   If an interrupt is currently active true is returned and its number is stored in iNum, otherwise false is returned and iNum is left untouched.
     *
     *  \param iNum a reference to store the interrupt's number to
     **/
     bool currentInterrupt(int& iNum);
  };

#endif
