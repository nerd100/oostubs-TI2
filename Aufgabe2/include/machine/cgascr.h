/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __screen_include__
#define __screen_include__

/* INCLUDES */

// for communication with the video controller
#include "machine/io_port.h"

// for colors
#include "common/colors.h"

/* DEFINES */

#define CGA_COLS 80
#define CGA_ROWS 25
#define CGA_ADDRESS 0xB8000

/* CLASSES */

union cga_attribute {
  unsigned char byte;
  struct {
    unsigned char fgColor :4, bgColor :3, blink :1;
  } bitfield;
};

struct cga_element {
  char character;
  cga_attribute attribute;
};


/** \brief CGA-Dispaly driver
 *
 * CGA_Screen enables the basic control of the screen of a computer by accessing
 * the screen memory and I/O ports directly.
 */
class CGA_Screen {
  protected:
    cga_element (&screenBuffer)[CGA_ROWS][CGA_COLS];
    cga_attribute defaultAttributes;
    IO_Port ioIndex;
    IO_Port ioData;
  public:
    
    /** 
     * \brief Constructor
     *
     * Sets up memory mapping of CGA driver, sets default attribute for output and clears the screen.
     */
    CGA_Screen();
    
    /** 
     * \brief Destructor 
     *
     * Prints a warning that the os ended.
     */
    ~CGA_Screen();
    
    /** \brief set the cursor position
     *
     * @param x column number of new position 
     * @param y row number of new position
     */
    void setpos(unsigned short x, unsigned short y);
    
    /** \brief get the cursor position
     *
     * @param x reference for column number of current position
     * @param y reference for row number of current position
     */
    void getpos(unsigned short& x, unsigned short& y) const;
    
    /** \brief print a character to a specific position
     *
     * @param x column number of display position
     * @param y row number of display position
     * @param character character to be displayed
     * @param attribute display attributes
     */
    void show(unsigned short x, unsigned short y, char character, unsigned char attribute);
    
    /** 
     * \~german
     * \brief gibt eine Zeichenkette an der aktuellen Position aus
     * 
     * Als Attribute werden die hinterlegten, aktuellen, Standardwerte verwendet.
     * 
     * @param string 
     *    Zeichenkette, die ausgegeben werden soll
     * @param n 
     *    Anzahl an Zeichen, die von \c string ausgegeben werden soll
     * 
     * 
     * \~english
     * \brief print a string to the current position
     * 
     * @param string 
     *    string of characters to be displayed
     * @param n 
     *    number of characters in string
     */
    void print(const char* string, unsigned int n);
    
    /** 
     * \~german
     * \brief das aktuelle Display wird eine Zeile nach oben gescrollt
     *
     * Die so entstandene neue Zeile wird mit Leerzeichen aufgefüllt.
     * Die Attribute dafür sind die aktuellen Standardwerte.
     * 
     * \~english
     * \brief scroll the display one line upwards
     *
     * The new row at the bottom of the screen is filled with spaces. The default 
     * attributes are used.
     */
    void scrollup();
    
    /** 
     * \~german
     * \brief leert den aktuellen Bildschirm
     * 
     * Dabei werden alle Zeilen mit Leerzeichen gefüllt. Als Attribute werden die
     * in einer Variable hinterlegten, aktuellen Standardwerte verwendet.
     * 
     * \~english
     * \brief clear the screen 
     */
    void clear();
    
    /** 
     * \~german
     * \brief ändert die aktuellen Standardattribute
     * 
     * Diese aktuellen Standardattribute werden von den meisten Funktionen dieser Klasse 
     * beim Setzen der CGA-Attribute genutzt.
     * 
     * \param fgColor
     *    Vordergrundfarbe
     * 
     * \param bgColor
     *    Hintergrundfarbe
     * 
     * \param blink
     *    Soll der Text blinken? (true = blinken)
     * 
     * \~english
     * \brief changes the used default attribute values 
     * 
     * Most of the function uses these attribute values to determine which values the new printed
     * text should have.
     * 
     * \param fgColor
     *    foregorund color
     * 
     * \param bgColor
     *    backgorund color
     * 
     * \param blink
     *    indecates if the text should blink (true = should blink)
     */
    void setAttributes(int fgColor, int bgColor, bool blink);
};

#endif
