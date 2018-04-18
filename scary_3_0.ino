/*
  ____________________

  Welcome to ScArY (Scientific RPN Calculator based on an ATTINY)
  Version 3.0 ... (c) 2018 by deetee/zooxo

  ScArY is free software. You can redistribute it and/or modify it under the terms
  of the GNU General Public License as published by the Free Software Foundation.

  ____________________

        PREAMBLE
  ____________________

    It is amazing how much calculator power a simple microcontroller like the
    ATTINY85 is able to perform. This 8 pin 8-bit core microcontroller provides
    only 8 kilobytes of flash memory to store program code, 512 bytes of RAM
    to handle variables and 512 bytes of EEPROM to save settings and user data
    permanently. So every byte is valuable and it took me many hours to optimize
    the code and to decide which function or feature to choose.

    In general, functionality and functions outweighted comfort and error handling
    which can be seen, for instance, looking at the permanent scientific display
    format or a "non interpretable" display after dividing by zero. Thus the
    user has to follow the calculation process more strictly than on conventional
    RPN calculators.

    Enjoy!
    deetee
  ____________________

     INTRODUCTION
  ____________________

    ScArY is a scientific calculator based on an ATTINY85 microcontroller and a
    QYF-TM1638-board (8 digit LED display with 16 buttons controlled with 3 pins).

    ScArY is capable of basic arithmetical functions and familiar operations
    of RPN calculators (ie stack operations) as well as a wide range of
    scientific functions and probability or statistic operations.

    In addition ScArY has some special features like saving its state, handling
    user defined constants and saving sequences of keypresses to EEPROM
    permanently ("Type Recorder").

  ____________________

    THE CALCULATOR
  ____________________

    8-DIGITS SCIENTIFIC DISPLAY (permanent SCI notation):

        mantissa  exponent
        |         |
      - m.m m m - e e.
      |         |    |
      sign  EE-sign  Indicator for recording


    KEYBOARD LAYOUT:

      f[] [zZZ RESCUE]   7 [MENU]    8 [REC]        9 [/]
       EE [SUM] (UP)     4 [CONST]   5 [SAVE]       6 [*]
      CHS [ROT] (DOWN)   1 [RCL]     2 [STO]        3 [-]
      CLX [brightness]   0 [SHOW]    . [SWAP]   ENTER [+]


    MENU:

       E      F      G      H       ... User Menus ("Type Recorder")
       a      b      c      d
       EXP    SQRT   POW    INV     ... Basic Functions
       LN     ANNU   ->P    ->R     ... Logarithm, Annuity, Polar/Rectangular
       GAMMA  GAUSS  STAT   LR      ... Probability, Statistics, Linear Regression
       (t)    SIN    COS    TAN     ... Trigonometric Functions
       (t.)   ASIN   ACOS   ATAN
       (h)    SINH   COSH   TANH    ... Hyperbolic Functions
       (h.)   ASINH  ACOSH  ATANH


  ENTERING NUMBERS:

    1 Enter mantissa (with '.' if applicable)
      Press ENTER to push mantissa to stack
    2 To enter power of ten:
      Enter exponent and (if applicable) change sign of exponent with CHS
    3 Press EE to link the mantissa with the exponent
    4 If applicable: Toggle sign of number with CHS

  ____________________

  OPERATIONS and KEYS
  ____________________

    BASIC KEYS:
      0 1 2 3 4 5 6 7 8 9 . ... Digits and decimal point
      CHS EE                ... Change sign and enter exponent (actually Y*10^X)
      ENTER                 ... Enter number (push stack)
      C                     ... Clear X, clear entry or escape/stop
      f                     ... Function or shift to choose shifted keys

    F-KEYS:
      + - * /    ... Basic operations
      STO RCL    ... Store number to respectively recall number from memory
      SHOW       ... Show full mantissa of number (7 digits without decimal point)
      SWAP       ... Swap X and Y register of stack (X<->Y)
      ROT        ... Rotate stack (X=Y Y=Z Z=T T=X)
      SUM        ... Enter X-data for statistics or X,Y-data for linear regression
      MENU       ... Browse menu
      REC        ... Records 8x52 keypresses (to recall via user menu "abcdEFGH")
      CONST      ... Browse up to 10 user saved constants
      SAVE       ... Save up to 10 user saved constants
      zZZ RESCUE ... Toggle screensaver and save calculator state to EEPROM
      BRIGHTNESS ... Set brightness of display (0...7)

    MENU-FUNCTIONS:
      EXP LN SQRT POWER INV            ... Basic scientific operations
      ANNU ->P ->R                     ... Annuity, polar/rectangular ... x)
      GAMMA GAUSS                      ... Gamma/!, Probability(PDF/CDF)  ... x)
      STAT LR                          ... Statistics, linear regression
      SIN  COS  TAN  ASIN  ACOS  ATAN  ... Trigonometric
      SINH COSH TANH ASINH ACOSH ATANH ... Hyperbolic ... x)
      a b c d E F G H                  ... user menu (play recorded keypresses)

      x) ... Some functions (ANNU, ->P, ->R, GAMMA, GAUSS, HYP) may affect the
             whole stack as they are calculated with basic operations.


  ____________________

     SPECIALITIES
  ____________________

    PREPARING ScArY AFTER FLASHING:

      As ScArY saves the state (stack and brightness values) when pressing the
      f-key twice (screensaver) it also loads the state after switching on.
      But flashing the ATTINY may clear the EEPROM. So the loaded state when
      switching on the first time after flashing gets undefined values
      (... and maybe a dark or "non interpretable" display).

      So the following procedure may help to bring ScArY in a defined state:
        1 Press CLX (X=0)        ... even if the display remains dark
        2 Set brightness (f-CLX) ... a "non interpretable" display is readable
        3 Press CLX (X=0)        ... value of 0 should be readable
        4 Press ENTER 3 times    ... clears the stack (X=Y=Z=T=0)
        5 Press STO (f-2)        ... clears mem
        6 Press f twice (f-f)    ... saves state to EEPROM (activates screensaver)
        7 Press f                ... (re)activates the screen


    WORKING WITH CONSTANTS:

      ScArY is capable to save up to 10 constants to permanently to the
      EEPROM memory. Additional to each constant up to three characters can be
      saved to recall and browse the constants very comfortable.
      See "Appendix - Physical Constants" for some physical constants.

      Example to write PI to slot O:
        1 3.141593 STO        ... store PI
        2 0 ENTER 115 ENTER 6 ... enter 3 characters (" PI"), see "Appendix -
                                  Identifiers of 7-Segment Displays"
        3 ENTER 0             ... enter slot 0
        4 SAVE                ... save constant to EEPROM

      Example to load stored constant:
        1 CONST         ... enter the catalogue of constants
          Use UP/DOWN-keys for browsing or enter a number directly (0...9)
        2 ENTER         ... load constant to stack


    TYPE RECORDER:

      ScArY is able to record 8 user defined sequences of keypresses
      (up to 52 each) and "replay" them by selecting the appropriate
      user menu entry. These user defined key sequences or formulas are stored
      to the EEPROM memory permanently.

      Example to record temperature conversion (Fahrenheit -> Celsius):
        1 3 REC      ... record to slot 3 (user menu c)
        2 32 - 1.8 / ... convert to celsius
        3 REC        ... stop recording

      Convert Fahrenheit to Celsius:
        1 50 MENU->c ... play recorded user formula in slot c (=3)
        2 X=10       ... 50 Fahrenheit are 10 Celsius


    ANNUITY (PRESENT VALUE):

      Example to calculate the present value of a $1 5 year return with an
      interest rate of 8%:
        1 .08 ENTER 5 ANNU ... annuity factor for 5 years and 8%
        2 X=3.99 ... 5 years $1 each are equal to ~$4 invested with 8%


    GAUSS:
                     y
                     ^
                     |
                   1 ------------------------
                     |       +++++++ CDF (Cumulative Distribution Function)
                     |   +
                     | +                     (x)         .
                     |+              CDF = integral(PDF) = 1/(1+exp(-0.07*x^3-1.6*x))
                     +                      (-inf)
                   **+**
                **  +|   **
                  +  |     *         PDF = 1/sqrt(2*PI)*exp(-x*x/2)
             ** +    |      **
      +*+*+*+        |         ***** PDF (Probability Density Function)
      ---------------+------------------------> x

      Example to calculate PDF and CDF at x=0:
        1 0 GAUSS
        2 PDF=0.3989=1/sqrt(2*PI)
        3 SWAP
        4 CDF=0.5


    STATISTICS, LINEAR REGRESSION:
        y
        ^                /
        |  Ypredict(x=1.5)=4
      4 - <----------- /
        |             /
        |            / ^
        |           /  |
        |          /
      3 -        [*] P2=(1|3)
        |        /
        |       /      ^
        |      /       |
        |     /
      2 -   [*] P1=(0.5|2)
        |   /
        |_ /           ^
        | /|           |
        |/ |           |
      1 -  |           |
       /|  |           |
      / |  |           |
     /  |  | Xpredict(y=1.5)=0.25
        |  v           |
    ----+----+----|----+----|-> x
        0       | 1         2
                |
                Xmean=0.75
             |  |
           ->|--|<- Standard Deviation S=0.354

      Example to calculate mean value and standard deviation:
        1 0.5 SUM 1 SUM ... enter X-data
        2 STAT
        3 Xmean=0.75 (mean value)
        4 SWAP
        5 S=0.354 (standard deviation)

      Example to calculate a linear regression:
        1 2 ENTER 0.5 SUM ... enter YX-data of first node
        2 3 ENTER 1 SUM   ... enter YX-data of second node
        3 1.5 LR          ... enter desired x/y-value
        4 X=0.25          ... predicted x-value for y=1.5
        5 SWAP
        6 Y=4             ... predicted y-value for x=1.5

      Example to calculate the line of best fit:
        1 2 ENTER 0.5 SUM ... enter YX-data of first node
        2 3 ENTER 1 SUM   ... enter YX-data of second node
        3 1 LR SWAP       ... enter x-value of 1
        4 Y=3             ... predicted y-value for x=1
        5 0 LR ROT        ... enter x-value of 0
        6 Y=1             ... predicted y-value for x=0 (y-axis-intercept)
        7 -               ... substract y(1) and y(0) (=slope)
        8 X=2             ... slope of best-fit-line
        9 y = 2 * x + 1   ... formula of best-fit-line


  ____________________

       APPENDIX
  ____________________

    HARDWARE:
                                   __________________
            -.---------           | 8.8.8.8.8.8.8.8. |
           | 1()   ()8 |-VCC  GND-|GND               |
           | 2(3) (2)7 |----------|DIO   *   *   *   |
           | 3(4) (1)6 |----------|CLK   *   *   *   |
       GND-| 4()  (0)5 |----------|STB   *   *   *   |
            -----------       VCC-|VCC   *   *   *   |
              ATTINY85             ------------------
       VCC=5V                          QYF-TM1638


    USAGE OF EEPROM (512 bytes):

      | Brightness|   Stack   | |   CONSTANTS  | |  RECORDER |
      |           | X Y Z T M | | C0 C1 ... C9 | | 8*REC(52) |
      0           1          20 21            90 91        507
      |     1     |     20    | |      70      | |    416    |


    ASCII TABLE:

      DEC     |  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
          HEX |  0 1 2 3 4 5 6 7 8 9 a b c d e f
      ------------------------------------------
      032 20  |    ! " # $ % & ' ( ) * + , - . /
      048 30  |  0 1 2 3 4 5 6 7 8 9 : ; < = > ?
      064 40  |  @ A B C D E F G H I J K L M N O
      080 50  |  P Q R S T U V W X Y Z [ \ ] ^ _
      096 60  |  ` a b c d e f g h i j k l m n o
      112 70  |  p q r s t u v w x y z { | } ~


    IDENTIFIERS OF 7-SEGMENT DISPLAY:
    (i.e. code to display digit 3 =  79 = 4f)

      DEC       0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
          HEX   0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f
                    _       _       _       _       _       _       _       _
                         |   |           |   |           |   |           |   |
      000 00                     |   |   |   |  _   _   _   _   _|  _|  _|  _|
                    _       _       _       _       _       _       _       _
                         |   |           |   |           |   |           |   |
      016 10   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|
                    _       _       _       _       _       _       _       _
               |   |   | | | | |   |   | | | | |   |   | | | | |   |   | | | |
      032 20                     |   |   |   |  _   _   _   _   _|  _|  _|  _|
                    _       _       _       _       _       _       _       _
               |   |   | | | | |   |   | | | | |   |   | | | | |   |   | | | |
      048 30   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|
                    _       _       _       _       _       _       _       _
                _   _   _|  _|  _   _   _|  _|  _   _   _|  _|  _   _   _|  _|
      064 40                     |   |   |   |  _   _   _   _   _|  _|  _|  _|
                    _       _       _       _       _       _       _       _
                _   _   _|  _|  _   _   _|  _|  _   _   _|  _|  _   _   _|  _|
      080 50   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|
                    _       _       _       _       _       _               _
               |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_|
      096 60                     |   |   |   |  _   _   _   _   _|  _|  _|  _|
                    _       _       _       _       _       _       _       _
               |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_|
      112 70   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|


    PHYSICAL CONSTANTS:

      Constant      ID  Name
      ---recommended:-------------------------------------------
      3.141593      PI  Number PI
      0.01745329    RpD Radians per Degrees
      ---from WP34S-Manual:-------------------------------------
      365.2425      A   Gregorian year
      5.291772E-11  Ao  Bohr radius
      384.4E6       Am  Semi-major axis of the Moon's orbit
      1.495979E11   Ae  Semi-major axis of the Earth's orbit
      2.997942E8    c   Speed of light
      3.741772E-16  C1  First radiation constant
      0.01438777    C2  Second radiation constant
      1.602177E-19  e   Electron charge
      96485.34      F   Faraday constant
      2.502908      Fa  Feigenbaum's alpha
      4.669202      Fd  Feigenbaum's delta
      9.80665       g   Standard earth accelleration
      6.674083E-11  G   Newtonian constant of gravitation
      7.748092E-5   Go  Conductance quantum
      0.9159656     Gc  Catalan's constant
      -2.002232     Ge  Lande's electron g-factor
      6.626069E-34  h   Planck constant
      1.38065E-23   k   Boltzmann constant
      4.835979E14   Kj  Josephson constant
      1.616199      lP  Planck length
      9.109383E-31  me  Electron mass
      7.349E22      mM  Mass of the Moon
      1.674927E-27  mn  Neutron mass
      1.672622E-27  mp  Proton mass
      2.17651E-8    mP  Planck mass
      1.660539E-27  mu  Atomic mass unit
      1.492417E-10  Muc Energy equivalent of atomic mass unit
      1.883541E-28  mm  Muon mass
      1.9891E30     mS  Mass of the Sun
      5.9736E24     mE  Mass of the Earth
      6.022141E23   NA  Avogadro's number
      101325        po  Standard atmospheric pressure
      1.875546E-18  qP  Planck charge
      8.314472      R   Molar gas constant
      2.81794E-15   re  Electron radius
      25812.81      RK  Von Klitzing constant
      1.73753E6     RM  Mean radius of the Moon
      1.097373E7    Ryd Rydberg constant
      6.96E8        rS  Mean radius of the Sun
      6.37101E6     rE  Mean radius of the Earth
      273.15        To  Standard temperature
      5.39106E-44   tP  Planck time
      1.416833E-32  TP- Planck temperature
      0.02241397    Vm  Molar volume of an ideal gas
      376.7303      Zo  Impedance of vacuum
      7.297353E-3   _A  Fine structure constant
      0.5772157     _GE Euler-Mascheroni constant
      2.675222E8    _GP Proton gyromagnetic ratio
      8.854188E-12  _Eo Electric constant or vacuum permitivity
      2.42631E-12   _Le Compton wavelength of the electron
      1.319591E-15  _Ln Compton wavelength of the neutron
      1.32141E-15   _Lp Compton wavelength of the proton
      1.256673E-6   _mo Magnetic constant or vacuum permeability
      9.274009E-24  _mB Bohr's magneton
      -9.284764E-24 _me Electron magnetic moment
      -9.662364E-27 _mn Neutron magnetic moment
      1.410607E-26  _mp Proton magnetic moment
      5.050783E-27  _mu Nuclear magneton
      -4.490448E-26 _mm Muon magnetic moment
      5.670373E-8   _SB Stefan-Boltzmann constant
      1.618034      _P  Golden ratio
      2.067834E-15  _Po Magnetic flux quantum

  ____________________
*/


// INCLUDES AND DEFINES

#include <EEPROM.h>

// Pin assignment
//#define STROBE 11 // Strobe pin // Arduino/Genuino Micro
//#define CLOCK   6 // Clock pin
//#define DATA    3 // Data pin
#define DATA   2 // 5 green    // ATTINY85
#define CLOCK  1 // 6 yellow   // HW-pins: 8 7 6 5  SW-pins: 3 2 1 0
#define STROBE 0 // 7 orange   //          1 2 3 4           4 5 6 7

// Commands for QYF-TM1638-board
#define PRINTCMD 0x40 // Command code for display printing
#define READCMD  0x42 // Command code for key reading

// Constants
#define DIGITS            8 // Number of digits
#define SEGMENTS          8 // Number of segments per digit
#define KEYS             16 // Number of keys
#define STACKSIZE         5 // Size for stack (x, y, z, t, mem)
#define TINYNUMBER     1e-7 // Number for rounding to 0
#define MAXEE            38 // Maximal EE for Y10X
#define FIX               3 // Display 3 decimals
#define FIXMANT           3 // FIX in 10th-exponent
#define FIXSHOW           6 // FIX for SHOW
#define FIXMANTSHOW       6 // FIX in 10th-exponent
#define BRIGHTMAX         7 // Maximal value for brightness
#define MAXITERATE      100 // Maximal number of Taylor series loops to iterate
#define MAXMENU           8 // Number of MENUs (including 0)
#define NUMBEROFF        15 // Number of casted f-keys
#define EEADDRBRIGHTNESS  0 // Starting EE-address for saving brightness
#define EEADDRSTACK       1 // Starting EE-address for saving stack and mem with screensaver
#define EEADDRCONST      21 // Starting EE-address for constants
#define EEADDRREC        91 // Starting EE-sddress for saving "type recorder"
#define EECONSTCHAR       3 // Number of characters for one constant
#define EESTEP            7 // Number of bytes per EEPROM-slot (3 characters, 4 for one double)
#define EECONSTMAX        9 // Maximal number of 7-byte-entries in EEPROM (512k) (including 0)
#define MAXREC           52 // Number of record steps per slot
#define MAXRECSLOT        8 // Maximal slots to record
#define RAD        57.29578 // 180/PI

// Segment flags
#define _7A 0x00 //  --a--
#define _7B 0x02 // |     |
#define _7C 0x04 // f     b
#define _7D 0x06 // |--g--|
#define _7E 0x08 // e     c
#define _7F 0x0a // |     |
#define _7G 0x0c //  --d--  (h)
#define _7H 0x0e

// Keyboard codes
#define _K9  0x0001 //  _K1  _K2  _K3  _K4
#define _K1  0x0002 //  _K5  _K6  _K7  _K8
#define _K10 0x0004 //  _K9  _K10 _K11 _K12
#define _K2  0x0008 //  _K13 _K14 _K15 _K16
#define _K11 0x0010
#define _K3  0x0020
#define _K12 0x0040
#define _K4  0x0080
#define _K13 0x0100
#define _K5  0x0200
#define _K14 0x0400
#define _K6  0x0800
#define _K15 0x1000
#define _K7  0x2000
#define _K16 0x4000
#define _K8  0x8000

// assign 2-nibble byte code to sign
// hgfe-dcba 8421-8421
#define _7SPACE 0x00
#define _7QUOTATIONMARK 0x22
#define _7APOSTROPHELEFT 0x20
#define _7APOSTROPHERIGHT 0x02
#define _7COMMALEFT 0x10
#define _7COMMARIGHT 0x04
#define _7MINUS 0x40
#define _7FULLSTOP 0x80
#define _7SOLIDUS 0x52
#define _7DIGIT0 0x3f
#define _7DIGIT1 0x06
#define _7DIGIT2 0x5b
#define _7DIGIT3 0x4f
#define _7DIGIT4 0x66
#define _7DIGIT5 0x6d
#define _7DIGIT6 0x7d
#define _7DIGIT7 0x07
#define _7DIGIT8 0x7f
#define _7DIGIT9 0x6f
#define _7LESSTHANSIGN 0x18
#define _7EQUALSSIGN 0x48
#define _7GREATERTHANSIGN 0x0c
#define _7LETTERA 0x77
#define _7LETTERb 0x7c
#define _7LETTERc 0x58
#define _7LETTERC 0x39
#define _7LETTERd 0x5e
#define _7LETTERE 0x79
#define _7LETTERF 0x71
#define _7LETTERG 0x3d
#define _7LETTERh 0x74
#define _7LETTERH 0x76
#define _7LETTERI 0x30
#define _7LETTERJ 0x0e
#define _7LETTERL 0x38
#define _7LETTERn 0x54
#define _7LETTERo 0x5c
#define _7LETTERP 0x73
#define _7LETTERq 0x67
#define _7LETTERr 0x50
#define _7LETTERS 0x6d
#define _7LETTERt 0x78
#define _7LETTERu 0x1c
#define _7LETTERU 0x3e
#define _7LETTERy 0x6e
#define _7LEFTSQUAREBRACKET 0x39
#define _7REVERSESOLIDUS 0x64
#define _7RIGHTSQUAREBRACKET 0x0f
#define _7LOWLINE 0x08
#define _7MIDDLELINE 0x40
#define _7HIGHLINE 0x01
#define _7DEGREESIGN 0x63
#define _7PARALLELSIGN 0x36
#define _7HIGHEQUALSIGN 0x41
#define _7THREELINES 0x49
#define _7LOWHIGHLINE 0x09


// Commands and corresponding ascii signs
#define STO ' '
#define RCL '!'
//#define '"' // do not use
#define SWAP '#'
#define SHOW '$'
#define BRIGHTNESS'%'
#define ROT '&'
//#define '\'' // do not use
#define CHS'('
#define EE ')'
#define MULTIPLY '*'
#define ADD '+'
#define ENTER ','
#define SUBSTRACT '-'
#define DOT '.'
#define DIVIDE '/'
#define DIGIT0 '0' // --- Continuous: Digits
#define DIGIT1 '1' // ^
#define DIGIT2 '2' // |
#define DIGIT3 '3' // |
#define DIGIT4 '4' // |
#define DIGIT5 '5' // |
#define DIGIT6 '6' // |
#define DIGIT7 '7' // |
#define DIGIT8 '8' // v
#define DIGIT9 '9' // ---
#define SHIFT ':'
#define EXP ';'
#define LN '<'
#define POW '='
#define SQRT '>'
#define INV '?'
#define MENU '@'
//#define  'A'
//#define  'B'
#define CLX 'C'
#define CE 'D'
#define SUM 'E'
#define STAT 'F'
#define LR 'G'
//#define  'H'
//#define  'I'
//#define  'J'
//#define  'K'
//#define  'L'
//#define  'M'
//#define  'N'
//#define  'O'
//#define  'P'
//#define  'R'
//#define  'S'
//#define  'T'
//#define 'U'
//#define  'V'
//#define 'W'
//#define 'X'
//#define  'Y'
//#define  'Z'
#define PLAYSTRING '['
//#define '\\'
#define LOAD ']'
#define SAVE '^'
#define CONST '_'
#define REC '`'
#define PLAYa 'a' // --- CONTINUOUS: User menus
#define PLAYb 'b' // ^
#define PLAYc 'c' // |
#define PLAYd 'd' // |
#define PLAYe 'e' // |
#define PLAYf 'f' // |
#define PLAYg 'g' // v
#define PLAYh 'h' // ---
#define SIN 'i'   // --- CONTINUOUS: Trigonometric
#define COS 'j'   // ^
#define TAN 'k'   // |
#define ASIN 'l'  // |
#define ACOS 'm'  // v
#define ATAN 'n'  // ---
#define SINH 'o'  // --- CONTINUOUS: Playstring-functions (Hyperbolic, other)
#define COSH 'p'  // ^
#define TANH 'q'  // |
#define ASINH 'r' // |
#define ACOSH 's' // |
#define ATANH 't' // |
#define GAUSS 'u' // |
#define ANNU 'v'  // |
#define R2P 'w'   // |
#define P2R 'x'   // v
#define GAMMA 'y'   // --- (GAMMA is upper limit in "playstring-if")
//#define  'z' //
//#define  '{' //
//#define  '|' //
//#define  '}' //
//#define  '~' //

static const byte digit[] = {
  _7DIGIT0             , _7DIGIT1             , _7DIGIT2             , _7DIGIT3,
  _7DIGIT4             , _7DIGIT5             , _7DIGIT6             , _7DIGIT7,
  _7DIGIT8             , _7DIGIT9
};


// GLOBAL VARIABLES
static double stack[STACKSIZE];
static byte dispbuf[DIGITS] = {0, _7DIGIT0, _7DIGIT0, _7DIGIT0, _7DIGIT0, 0, _7DIGIT0, _7DIGIT0}; // Display buffer
static int recptr = 0;        // Pointer to recording step
static byte recslot = 0;      // Slot number for recording to EEPROM
static byte decimals = 0;     // Number of decimals entered - used for input after decimal dot
static byte selectnr = 0;     // Number of selected menu/const item
static byte brightness = 0;   // Value for brightness of display (0...7)
static double sx = 0.0, sxx = 0.0, sy = 0.0, sxy = 0.0; // Statistical/LR variables
static byte sn = 0;

// flags
static boolean isnewnumber = true; //* True if stack has to be lifted before entering a new number
static boolean ispushed = false;   // True if stack was already pushed by ENTER
static boolean isfpressed = false; // Function key pressed
static boolean isdot = false;      // True if dot was pressed and decimals will be entered
static boolean ismenu = false;     // True, if MENU was demanded
static boolean isprintmenu = true; // True if MENU/CONST should be printed
static boolean isdisplaydeactivated = false; // True if display is deactivated
static boolean isselectconst = false; // True if CONST browsing is demanded
static boolean isshow = false;     // True, if SHOW was demanded
static boolean isrec = false, isplay = false; // True, if "Type Recorder" records or plays
static boolean isplaystring = false; // True, if "string-program" plays

// Menu variables
static const byte _msgs[MAXMENU + 1][DIGITS] = { // Menu display characters
  {_7LETTERE, 0, 0x33, 0, _7LETTERP, 0, _7LETTERr, 0},           // exp_sqrt_pow_1/x
  {_7LETTERL, 0, _7LETTERA, 0, _7MINUS, _7LETTERP, _7MINUS, _7LETTERr}, // ln_annu_r2p_p2r
  {0x31, 0, _7LETTERG, 0, 0x5d, 0, _7LETTERL, _7LETTERr},        // gamma_gauss_stat_LR
  {_7LETTERt, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0},      // _sin_cos_tan
  {_7LETTERt | _7FULLSTOP, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0}, // _asin_acos_atan
  {_7LETTERh, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0},      // _sinh_cosh_tanh
  {_7LETTERh | _7FULLSTOP, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0}, // _asinh_acosh_atanh
  {_7LETTERE, 0, _7LETTERF, 0, _7LETTERG, 0, _7LETTERH, 0},      // E_F_G_H user menu
  {_7LETTERo, 0, _7LETTERb, 0, _7LETTERc, 0, _7LETTERd, 0},      // a_b_c_d user menu
};
static const byte _menuchar[MAXMENU + 1][4] = { // Menu keycodes
  {EXP, SQRT, POW, INV},        // exp_sqrt_pow_1/x
  {LN, ANNU, R2P, P2R},         // ln_annu_r2p_p2r
  {GAMMA, GAUSS, STAT, LR},     // gamma_gauss_stat_LR
  {0, SIN, COS, TAN},           // _sin_cos_tan
  {0, ASIN, ACOS, ATAN},        // _asin_acos_atan
  {0, SINH, COSH, TANH},        // _sinh_cosh_tanh
  {0, ASINH, ACOSH, ATANH},     // _asinh_acosh_atanh
  {PLAYe, PLAYf, PLAYg, PLAYh}, // E_F_G_H user menu
  {PLAYa, PLAYb, PLAYc, PLAYd}, // a_b_c_d user menu
};

// Playstring variables
const char s00[] PROGMEM = ";,?(+2/"; // SINH: EXP ENTER INV CHS + 2 /
const char s01[] PROGMEM = ";,?+2/"; // COSH: EXP ENTER INV + 2 /
const char s02[] PROGMEM = ";,,?(+#,?+/"; // TANH: EXP ENTER ENTER INV CHS + SWAP ENTER INV + /
const char s03[] PROGMEM = ",,*1+>+<"; // ASINH: ENTER ENTER * 1 + SQRT + LN
const char s04[] PROGMEM = ",,*1->+<"; // ACOSH: ENTER ENTER * 1 - SQRT + LN
const char s05[] PROGMEM = ",,1+#(1+/><"; // ATANH: ENTER ENTER 1 + SWAP CHS 1 + / SQRT LN
const char s06[] PROGMEM = ",,,**.07*(#1.6*(+;1+?#,*(2/;.3989*";
// GAUSS-CDF: ENTER ENTER ENTER * * .07 * CHS SWAP 1.6 * CHS + EXP 1 + INV
// SWAP
// GAUSS-PDF: ENTER * CHS 2 / EXP 0.3989423 *
const char s07[] PROGMEM = "#,,1+#&#=?(1+&&&/"; // ANNU: SWAP ENTER ENTER 1 + SWAP ROT SWAP PWR INV CHS 1 + ROT ROT ROT /
const char s08[] PROGMEM = ",&&#&,&#/n&&*&&*+>"; // R2P: ENTER ROT ROT SWAP ROT ENTER ROT SWAP / ATAN ROT ROT * ROT ROT * + SQRT
const char s09[] PROGMEM = ",&&#&,&#&j*&i*&&&"; // P2R: ENTER ROT ROT SWAP ROT ENTER ROT SWAP ROT COS * ROT SIN * ROT ROT ROT
const char s10[] PROGMEM = "1+,,?;,?(+2/*#6=810*?+<*2/#(+&&<#.5-*+.9189358+;";
// GAMMA: 1 + ENTER ENTER INV EXP ENTER INV CHS + 2 / * SWAP 6 PWR 810 * INV + LN * 2 /
// SWAP CHS + ROT ROT LN SWAP .5 - * + .9189385 + EXP
// Lower precision:
// GAMMA: 1 + ENTER ENTER INV EXP ENTER INV CHS + 2 / * LN * 2 /
// SWAP CHS + ROT ROT LN SWAP .5 - * + .9189385 + EXP

const char* const s_table[] PROGMEM = {s00, s01, s02, s03, s04, s05, s06, s07, s08, s09, s10};
char buffer[50]; // Holds sii[]


// SUBROUTINES

// Macros
#define _abs(x) ((x<0)?(-x):(x)) // abs()-substitute macro
#define _ones(x) ((x)%10)        // Calculates ones unit
#define _tens(x) (((x)/10)%10)   // Calculates tens unit

static void cmd(byte val) { // Send command to shield
  digitalWrite(STROBE, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, val);
  digitalWrite(STROBE, HIGH);
}

static unsigned int getbuttons() { // Get button code (only one key at a time) - 16 bits
  unsigned int buttons = 0;
  byte val = 0;
  digitalWrite(STROBE, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, READCMD); // Demand key input
  pinMode(DATA, INPUT); // Switch data line to INPUT
  for (byte i = 0; i < 4; i++) {
    val = shiftIn(DATA, CLOCK, LSBFIRST) >> 1; // Get button value (and half it)
    if (val > 2) val >>= 2; // Reduce values 16 and 32 to 4 and 8
    buttons |= val << (4 * i); // Write value-nibble to buttons-nibbles (4,3,2,1)
  }
  pinMode(DATA, OUTPUT); // Switch data line back to output
  digitalWrite(STROBE, HIGH);
  return (buttons);
}

static byte buttoncode() { // Returns byte value with key number
  unsigned int c = getbuttons(); //  1  3  5  7
  if (c & 0x1) return (16);      //  9 11 13 15
  byte ans = NULL;               // 16  2  4  6
  while (c >>= 1) ans++;         //  8 10 12 14
  return (ans);
}

static byte buttoncast() { // Get button pattern and return keycode
  byte keycast[KEYS + 1] = {  // 1 added (0 vs. NULL)
    0,                                                          // Key number:
    SHIFT, DIGIT1, DIGIT7, DIGIT2, DIGIT8, DIGIT3, DIGIT9, CLX, // 1 10 2 11 3 12 4 13
    EE,    DIGIT0, DIGIT4, DOT,    DIGIT5, ENTER,  DIGIT6, CHS  // 5 14 6 15 7 16 8 9
  };
  return (keycast[buttoncode()]);
}

static byte getkey() { // Get one debounced key
  static byte oldkey = 0; // Needed for debouncing
  byte key1 = buttoncast(), key2 = 0;
  if (key1 != oldkey) key2 = buttoncast();
  if (key1 == key2) {
    oldkey = key1;
    return (key1);
  }
  return (NULL);
}

static void printbuf() { // Write buffer "dispbuf" to screen
  byte digbuf;
  if (!ismenu && !isselectconst) {
    if (!isshow) dispbuf[1] |= _7FULLSTOP; // Dot for normal print
    else dispbuf[0] = _7APOSTROPHELEFT; // Sign for show
  }
  if (isrec) dispbuf[7] = dispbuf[7] | _7FULLSTOP; // Show REC light

  cmd(PRINTCMD); // Demand write command
  for (byte j = 0; j < SEGMENTS; j++) { // Write segment of all digits
    digbuf = 0;
    for (byte i = 0; i < DIGITS; i++) {
      digbuf = (digbuf << 1) | ((dispbuf[i] & (0x01 << j)) ? 0x01 : 0x00);
    }
    for (byte i = 0; i < DIGITS; i++) { // Print segments for each digit
      digitalWrite(STROBE, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, 0xc0 | 2 * j); // Address - segment
      shiftOut(DATA, CLOCK, LSBFIRST, 0x00 | digbuf); // Data - digit
      digitalWrite(STROBE, HIGH);
    }
  }
}

static void printfloat(void) { // Prints X (stack[0]) to dispbuf[]
  static const byte digits[] = { // Character set to display numbers
    _7DIGIT0, _7DIGIT1, _7DIGIT2, _7DIGIT3, _7DIGIT4,
    _7DIGIT5, _7DIGIT6, _7DIGIT7, _7DIGIT8, _7DIGIT9
  };
  memset(dispbuf, NULL, sizeof(dispbuf));
  double f = stack[0];
  long m; // Mantissa
  int8_t e; // Exponent

  byte dot = 2; // Set local variables for "normal print"
  byte mantdigits = 4;
  byte fix = FIX;
  byte fixmant = FIXMANT;

  if (isshow) { // Set local variables for "SHOW print" if SHOW was demanded
    dot = 0;
    mantdigits = 7;
    fix = FIXSHOW;
    fixmant = FIXMANTSHOW;
  }

  if (f < 0.0) {
    f = - f;
    dispbuf[0] = _7MINUS;
  }
  e = log10(f); // Exponent
  m = (f / _pow10(e - fix)) + .5; // Mantissa
  if (m > 0 && m < _pow10(fixmant)) { // Change (n-1)-digit-mantissa to n digits
    e -= 1;
    m = (f / _pow10(e - fix)) + .5; // "New" mantissa
  }
  for (byte i = mantdigits; i > 0; i--) { // Print mantissa
    dispbuf[i] = digits[_ones(m)];
    m /= 10;
  }
  if (!isshow) { // Rest of "normal print"
    if (e < 0) { // Negative exponent
      dispbuf[5] = _7MINUS;
      e = -e;
    }
    if (e < 10) { // Print exponent
      dispbuf[6] = _7DIGIT0;
      dispbuf[7] = digits[e];
    }
    else {
      dispbuf[6] = digits[_tens(e)];
      dispbuf[7] = digits[_ones(e)];
    }
  }
  printbuf(); // Write buffer to display
}

static byte fcast(byte k) { // Returns f-key code for casting
  const byte _f_old[] = {DIGIT7,     DIGIT8, DIGIT9,            // f-cast from
                         EE,         DIGIT4, DIGIT5, DIGIT6,
                         CHS,        DIGIT1, DIGIT2, DIGIT3,
                         CLX,        DIGIT0, DOT,    ENTER
                        };
  const byte _f_new[] = {MENU,       REC,    DIVIDE,            // to
                         SUM,        LOAD,   SAVE,   MULTIPLY,
                         ROT,        RCL,    STO,    SUBSTRACT,
                         BRIGHTNESS, SHOW,   SWAP,   ADD
                        };
  for (byte i = 0; i < NUMBEROFF; i++) {
    if (k == _f_old[i]) return (_f_new[i]);
  }
  return (NULL);
}

static void push_upper(void) { // Push upper part of stack
  memmove(&stack[2], &stack[1], 2 * sizeof(double));
}

static void push(void) { // Push stack fully
  memmove(&stack[1], &stack[0], 3 * sizeof(double));
}

static void pull_upper(void) { // Pull upper part of stack
  memmove(&stack[1], &stack[2], 2 * sizeof(double));
}

void pull(void) { // Pull stack fully
  memmove(&stack[0], &stack[1], 3 * sizeof(double));
}

static double _pow10(int8_t e) { // Returns 10^e
  boolean ne = (e < 0);
  double f = 1.0;
  if (ne) while (e++)  f *= 10;
  else while (e--)  f *= 10;
  if (ne) f = 1 / f;
  return (f);
}

static double _exp_sin(double f, boolean isexp) { // Calculate exp or sin with Taylor series
  double result = f;
  double frac = f;
  if (isexp) result = frac = 1.0;
  for (byte i = 1; _abs(frac) > TINYNUMBER && i < MAXITERATE; i++) {
    if (isexp) frac *= f / i; // Fraction for exp
    else frac *=  f  / (-2 * i * (2 * i + 1)) * f; // Fraction for sin
    result += frac;
  }
  return (result);
}

static double _sqrt(double f) { // Calculating square root without using sqrt()
  return (_exp_sin(0.5 * log(f), true));
}


// SETUP and LOOP

void setup() {
  //int main(void) { //*** Replaces setup-loop with a main-while (looses serial connection)
  //init(); //***
  //{ //***
  pinMode(STROBE, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);

  //cmd(0x88); // Activate and brightness "1000 abbb" (a=1)
  cmd(0x88 | EEPROM.read(EEADDRBRIGHTNESS)); // Set and read brightness from EEPROM
  for (byte i = 0; i < STACKSIZE; i++)       // Read stack from EEPROM (saved with ff)
    EEPROM.get(EEADDRSTACK + i * sizeof(double), stack[i]);
  printfloat();
}


void loop() {
  //while (1) { //*** Replaces setup-loop with a main-while (looses serial connection)
  byte key = NULL;
  static byte oldkey = NULL; // Previous key to check end of recording

  key = getkey(); // Read character

  if (isrec && key != NULL) { // ### Record keys and write to EEPPROM
    if (oldkey == SHIFT) EEPROM.write(EEADDRREC + recptr - 1, oldkey = fcast(key)); // Rec shifted key
    else if (recptr < (recslot + 1)* MAXREC) EEPROM.write(EEADDRREC + recptr++, key); // Rec key
  }
  else if (isplay) { // ### Plays recorded keys
    if (key == CLX) isplay = false; // C stops playing
    else if ( recptr < (recslot + 1)* MAXREC) {
      key = EEPROM.read(EEADDRREC + recptr); // Read key from EEPROM
      if (key == DIGIT8 && oldkey == SHIFT) { // Last record reached
        isplay = false;
        isfpressed = false;
        key = NULL;
      }
      oldkey = key;
      recptr++;
    }
  }
  else if (isplaystring) { // ### Plays string
    if (buffer[recptr] == NULL) isplaystring = false;
    else key = buffer[recptr++];
  }

  if (ismenu || isselectconst) { // ### Selecting MENU or CONST
    memset(dispbuf, NULL, sizeof(dispbuf));
    byte maxnr = MAXMENU;
    if (isselectconst) maxnr = EECONSTMAX;
    if (isprintmenu) {
      if (ismenu) memmove(dispbuf, _msgs[selectnr], DIGITS * sizeof(byte)); // Show menu
      //if (ismenu) for (byte i = 0; i < 4; i++) dispbuf[2 * i] = _msgs[selectnr][i];  // Show menu
      else {
        dispbuf[0] = digit[_tens(selectnr)];
        dispbuf[1] = digit[_ones(selectnr)];
        for (byte i = 0; i < EECONSTCHAR; i++)
          dispbuf[i + DIGITS - EECONSTCHAR] = EEPROM.read(EEADDRCONST + selectnr * EESTEP + i);
      }
      printbuf();
      isprintmenu = false;
    }
    if (key == EE) { // Previous menu entry
      if (selectnr > 0) selectnr--;
      else selectnr = maxnr;
      isprintmenu = true;
    }
    else if (key == CHS) { // Next menu entry
      if (selectnr < maxnr) selectnr++;
      else selectnr = 0;
      isprintmenu = true;
    }
    else if (key == CLX) { // Exit menu
      selectnr = 0;
      ismenu = isselectconst = false;
      printfloat();
    }
    if (ismenu) {
      if (key >= DIGIT7 && key <= SHIFT) { // Choose option
        if (key == SHIFT) key = DIGIT6;
        key = _menuchar[selectnr][key - DIGIT6];
        ismenu = false;
      }
      else key = NULL;
    }
    else {
      if (key == ENTER) { // Enter - choose const
        push();
        EEPROM.get(EEADDRCONST + selectnr * EESTEP + EECONSTCHAR, stack[0]);
        isselectconst = false;
        isnewnumber = true;
        printfloat();
      }
      else if (key >= DIGIT0 && key <= DIGIT9) { // Enter constant number
        selectnr = key - '0';
        isprintmenu = true;
      }
      key = NULL;
    }
  }
  else if (key == SHIFT) { // ### Toggle function key f
    if (isfpressed) { // Activate screensaver
      cmd(0x80); // Deactivate display - "1000 abbb" (a=0)
      isdisplaydeactivated = true;
      isfpressed = false;
      EEPROM.write(EEADDRBRIGHTNESS, brightness);
      for (byte i = 0; i < STACKSIZE; i++) // Save stack to EEPROM
        EEPROM.put(EEADDRSTACK + i * sizeof(double), stack[i]);
    }
    else {
      if (isdisplaydeactivated) {
        isfpressed = isdisplaydeactivated = false;
        cmd(0x88 | brightness); // Activate display - "1000 abbb" (a=1)
      }
      else isfpressed = true;
    }
    key = NULL;
  }
  else if (key == DOT) { // ### Entering decimals demanded
    if (!isfpressed) {
      if (isnewnumber) { // Enable starting new number with .
        if (ispushed) ispushed = false;
        else push();
        stack[0] = 0.0;
        decimals = 0;
        isnewnumber = false;
      }
      isdot = true;
      key = NULL;
    }
  }

  if (key != NULL) { // ### EXECUTE key if valid ###
    if (isfpressed) { // Cast pressed key to f-key if function key f is active
      key = fcast(key);
      isfpressed = false;
    }
    else if (key == CLX && !isnewnumber) key = CE; // Cast CLX to CE when number entering
    if ((key >= DIGIT0) && (key <= DIGIT9)) { // Numeric input
      if (isnewnumber) { // New number
        if (ispushed) ispushed = false;
        else push();
        stack[0] = 0.0;
        decimals = 0;
        isdot = false;
        isnewnumber = false;
      }
      if (isdot) stack[0] += (key - '0') / _pow10(++decimals); // Append decimal to number
      else stack[0] = stack[0] * 10 + key - '0'; // Append digit to number
    }
    else if (key == ENTER) { // ENTER
      push();
      ispushed = true;
      isnewnumber = true;
    }
    else if (key == CLX) { // CLx - Clear x
      stack[0] = 0.0;
    }
    else if (key == CE) { // CE - clear entry
      if (isdot) {
        if (stack[0] > TINYNUMBER && decimals > 0)
          stack[0] -= ((long)(stack[0] * _pow10(decimals)) % 10) / _pow10(decimals--);
        else isdot = false;
      }
      else stack[0] = (long)(stack[0] / 10.0);
    }
    else if (key == CHS) { // CHS
      stack[0] = -stack[0];
      isnewnumber = true;
    }
    else if (key == SHOW) isshow = true; // SHOW demanded
    else if (key == MENU) { // Activate MENU
      selectnr = 0; // Uncomment if MENU should always start at first entry
      isprintmenu = true;
      ismenu = true;
    }
    else if (key == LOAD) { // CONST demanded
      selectnr = 0; // Uncomment if CONST should always start at first entry
      isprintmenu = true;
      isselectconst = true;
    }
    else if (key == REC) { // Toggle "Type recording" ON/OFF
      if (isrec) isrec = isplay = false; // Stop isplay too - if play was recorded
      else {
        recslot = (int)(_abs(stack[0])) - 1; // -1 to convert user's 1234-mind to 0123-slots
        if (recslot < MAXRECSLOT) {
          pull();
          recptr = recslot * MAXREC;
          isrec = true;
        }
      }
    }
    else if (key >= PLAYa && key <= PLAYh) { // Toggle player ON/OFF
      recslot = key - PLAYa;
      recptr = recslot * MAXREC;
      isplay = true;
      isnewnumber = true;
    }

    else { // Other commands - finally setting the ispushed false and isnewnumber true

      if (key == ADD) { // +
        stack[0] += stack[1];
        pull_upper();
      }
      else if (key == SUBSTRACT) { // -
        stack[0] = stack[1] - stack[0];
        pull_upper();
      }
      else if (key == MULTIPLY) { // *
        stack[0] *= stack[1];
        pull_upper();
      }
      else if (key == DIVIDE) { // /
        stack[0] = stack[1] / stack[0];
        pull_upper();
      }
      else if (key == EE) { // Y*10^X
        if (stack[0] <= MAXEE) {
          stack[0] = stack[1] * _pow10(stack[0]);
          pull_upper();
        }
      }
      else if (key == SWAP) { // SWAP
        double tmp = stack[0];
        stack[0] = stack[1];
        stack[1] = tmp;
      }
      else if (key == ROT) { // ROT down
        double tmp = stack[0];
        pull();
        stack[3] = tmp;
      }
      else if (key == STO) { // STO
        stack[4] = stack[0];
      }
      else if (key == RCL) { // RCL
        push();
        stack[0] = stack[4];
      }
      else if (key == SQRT) { // SQRT
        if (stack[0] > 0.0) stack[0] = _sqrt(stack[0]);
      }
      else if (key == EXP) { // EXP
        stack[0] = _exp_sin(stack[0], true);
      }
      else if (key == LN) { // LN
        stack[0] = log(stack[0]);
      }
      else if (key == POW) { // XpowerY
        stack[0] = _exp_sin(stack[0] * log(stack[1]), true);
        pull_upper();
      }
      else if (key == INV) { // 1/x
        stack[0] = 1 / stack[0];
      }
      else if (key >= SIN && key <= ATAN) { // Trigonometric
        double si = _exp_sin(stack[0] / RAD, false);
        double co = _sqrt(1 - si * si);
        double as = atan(stack[0] / _sqrt(1 - stack[0] * stack[0]));
        if (key == SIN) stack[0] = si;
        else if (key == ASIN) stack[0] = as * RAD;
        else if (key == COS) stack[0] = co;
        else if (key == ACOS) stack[0] = (PI / 2 - as) * RAD;
        else if (key == TAN) stack[0] = si / co;
        else stack[0] = atan(stack[0]) * RAD;
      }
      else if (key == SUM) { // SUM+
        sx += stack[0];
        sy += stack[1];
        sxx += stack[0] * stack[0];
        sxy += stack[0] * stack[1];
        stack[0] = ++sn;
      }
      else if (key == STAT) { // Statistics/LR
        push();
        stack[1] = _sqrt((sxx - sx * sx / sn) / (sn - 1)); // stdev
        stack[0] = sx / sn; // mean
      }
      else if (key == LR) { // Statistics/LR
        push();
        double tmp = (sxy / sn - sx * sy / sn / sn) / (sxx / sn - sx * sx / sn / sn);
        stack[1] = sy / sn - tmp * sx / sn + tmp * stack[0]; // ->y
        stack[0] = (stack[0] - sy / sn + tmp * sx / sn) / tmp; // ->x
      }
      else if (key == BRIGHTNESS) { // BRIGHTNESS
        brightness = stack[0] > BRIGHTMAX ? BRIGHTMAX : (int)stack[0];
        cmd(0x88 | brightness);
        pull();
      }
      else if (key == SAVE) { // Save signs (TZY) and number (mem) to slot X of EEPROM
        byte slotnr = _abs(stack[0]);
        if (slotnr < EECONSTMAX) {
          int addr = EEADDRCONST + slotnr * EESTEP;
          for (byte i = EECONSTCHAR; i > 0; i--) EEPROM.write(addr++, stack[i]);
          EEPROM.put(addr, stack[4]);
        }
      }
      else if (key >= SINH && key <= GAMMA) { // Call playstring functions
        recptr = 0;
        strcpy_P(buffer, (char*)pgm_read_word(&(s_table[key - SINH]))); // Copy playstring to buffer
        isnewnumber = true;
        isplaystring = true;
      }
      /*else if (key == GAUSS) { // GAUSS
        push_upper();
        stack[1] = _exp_sin(- log(1 + _exp_sin(-0.07 * stack[0] * stack[0] * stack[0] - 1.6 * stack[0], true)), true);
        //stack[1] = _exp_sin(- log(1 + _exp_sin(-0.07066 * stack[0] * stack[0] * stack[0] - 1.5976 * stack[0], true)), true);
        stack[0] = _exp_sin(-0.5 * log(2 * PI) - stack[0] * stack[0] / 2, true);
        }
        else if (key == SINH || key == ASINH || key == COSH || key == ACOSH || key == TANH || key == ATANH) { // Hyperbolic
        double ep = _exp_sin(stack[0], true);
        double em = _exp_sin(-stack[0], true);
        double tmp = stack[0] * stack[0] + 1;
        if (key == SINH) stack[0] = (ep - em) / 2;
        else if (key == ASINH) stack[0] = log(stack[0] + _sqrt(tmp));
        else if (key == COSH) stack[0] = (ep + em) / 2;
        else if (key == ACOSH) stack[0] = log(stack[0] + _sqrt(tmp - 2));
        else if (key == TANH) stack[0] = (ep - em) / (ep + em);
        else stack[0] = 0.5 * log((1 + stack[0]) / (1 - stack[0]));
        }
        else if (key == ROTUP) { // ROT up
        double tmp = stack[3];
        push();
        stack[0] = tmp;
        }
        else if (key == FACT) { // Factorial/Gamma
        //double tmp = 1.0; // Factorial with loops
        //for (byte i = 1; i <= stack[0]; i++) tmp *= i;
        //stack[0] = tmp;
        stack[0] += 1; // LN-Gamma function due to Nemes
        double t = 1 / stack[0];
        stack[0] = log(2 * PI) / 2 + stack[0] * ((t / 2 - 1) * log(t) - 1 + 0.5 * log(stack[0] * (_exp_sin(t, true) - _exp_sin(-t, true)) / 2 + 1 / 810 * t * t * t * t * t * t));
        stack[0] = _exp_sin(stack[0], true); // Gamma instead of LN-Gamma
        }
        /*else if (key == PEE) { // PI
        if (!ispushed) push();
        stack[0] = PI;
        }
        else if (key == ANNU) { // Annuity      ABANDONED FUNCTIONS (partly "programable")
        stack[0] = (1 - _exp_sin(-stack[0] * log(1 + stack[1]), true)) / stack[1];
        pull_upper();
        }
        else if (key == R2P) { // R->P
        double tmp = stack[1];
        stack[1] = atan(tmp / stack[0]) * rad;
        stack[0] = _sqrt(stack[0] * stack[0] + tmp * tmp);
        }
        else if (key == P2R) { // P->R
        double si = _exp_sin(stack[1] / rad, false);
        stack[1] = stack[0] * si;
        stack[0] = stack[0] * sqrt(1 - si * si);
        }
        case HMS2H: // H.MS->H
        lastx = x;
        x = (int)x + ((int)(100 * (x - (int)x))) / 60.0 + (100 * (100 * x - (int)(100 * x))) / 3600.0;
        break;
        case H2HMS: // H->H.MS
        lastx = x;
        x = (int)x + ((int)(60 * (x - (int)x))) / 100.0 + (60 * ((60 * (x - (int)x)) - (int)(60 * (x - (int)x)))) / 10000.0;
        break; */

      ispushed = false; // Common reset of isee, isnewnumber, ...
      isnewnumber = true;
    } //End of big IF ELSE

    //Serial.print(stack[0]); Serial.print(" "); Serial.print(stack[1]); Serial.print(" "); Serial.println(stack[2]);
    printfloat();
    isshow = false;
  }
}

//} //*** Replaces setup-loop with a main-while (looses serial connection)

