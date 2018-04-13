/*
  Welcome to ScArY (Scientific Calculator with RPN on an ATTINY)
  Version 2.0 ... (c) 2018 by deetee/zooxo
  Thanks to the mohpc-forum (particular Pauli) for saving bytes an providing ideas.

  What's new in version2?
  - ScArY saves its actual status (stack, brightness setting) permanantly to EEPROM.
    This is done when the screensaver is activated (keys f-f). Note the procedure
    to initialize these values after flashing the software (EEPROM was deleted).
  - It is possible to save up to 41 constants/numbers initialized with up to
    3 characters to EEPROM. The saved constants can be browsed and reloaded very
    convenient. See the section of recommended physical constants.
  - Some kind of "Type Recorder" was realized. It is possible to save 4 slots with
    up to 51 keypresses to the EEPROM and recall them with user defined menu entries.

  ScArY is a scientific calculator based on an ATTINY85 microcontroller and a
  QYF-TM1638-board (8 digit LED display with 16 buttons controlled with 3 pins).

  ScArY is capable of familiar functions of RPN calculators (ie stack operations)
  and many mathematical operations (ie trigonometic) as well as some special functions
  like gaussian distributions and gamma. In addition ScArY can save its state,
  physical constants and sequences of keypresses permanently to the EEPROM.

  Due to the memory restrictions of the ATTINY85 (8 kilobytes) some compromises were
  made to offer so many functions. So the numbers are shown in SCI notation only (see below).
  Another compromise is the lack of checking for errors - usually the display is
  unreadable if an error occurs.


  FIRST LAUNCH AFTER FLASHUNG THE ATTINY85:
    As ScArY saves the state (stack and brightness values) when pressing the
    f-key twice (screensaver) it also loads the state after switching on.
    But flashing the ATTINY may clear the EEPROM. So the loaded state when
    switching on the first time after flashing gets undefined values
    (... and maybe a dark or nonsense display).
  So the following procedure may help to bring ScArY in a defined state:
    1 Press CLX (X=0) ... even if the display remains dark
    2 Set brightness (f-CLX) ... at least a nonsense display should be readable
    3 Press CLX (X=0) ... value of 0 should be readable
    4 Press ENTER 3 times to clear the stack (X=Y=Z=T=0)
    5 Press STO (f-1) to clear mem
    6 Press f twice (f-f) to save the state to the EEPROM (activates screensaver too)
    7 Press f to (re)activate the screen
    8 Done! (till you flash the ATTINY again)


  KEYBOARD LAYOUT:

     f[] [zZZ RESCUE]    7 [RCL]     8 [STO]         9 [/]
      EE [MENU] (UP)     4 [CONST]   5 [SAVE]        6 [*]
     CHS [ROT] (DOWN)    1 [PI]      2 [REC]         3 [-]
       c [brightness]    0 [SWAP]    . [SHOW]    ENTER [+]


  MENU (f-EE):
       E (EXP)    S (SQRT)    P (POW)      r (1/x)
       L (LN)     G (GAUSS)   | (GAMMA)   dr (DEG/RAD)
                  S (SIN)     c (COS)      t (TAN)
       ^          S (ASIN)    c (ACOS)     t (ATAN)
       h          S (SINH)    c (COSH)     t (TANH)
       h^         S (ASINH)   c (ACOSH)    t (ATANH)
       a (PLAY0)  b (PLAY1)   c (PLAY2)    d (PLAY3)


  8-DIGITS SCIENTIFIC DISPLAY (SCI notation):

       mantissa  exponent
       |         |
     - m.m m m - e e.
     |         |    |
     sign  EE-sign  Indicator for recording


  ENTERING NUMBERS:
    1.) Enter mantissa (with '.' if applicable)
    2.) If applicable: Enter EE to enter exponent (limited to 29)
    3.) If applicable: Toggle sign of exponent with EE
    4.) If applicable: Toggle sign of number with CHS


  COMMANDS and KEYS:
    Basic keys:
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ., EE, CHS, ENTER, C/CE, f
    f-keys:
      +, -, *, / (basic operations)
      RCL, STO, SHOW, SWAP, ROT, SQRT, PI
      MENU (browse menu ... note user recorded menu "a b c d")
      REC (records 4x51 keypresses to recall via user menu "a b c d")
      CONST, SAVE (browse/load up to 41 user saved constants)
      zZZ RESCUE (toggle screensaver and save state to EEPROM)
      BRIGHTNESS (set brightness of display)
    MENU-functions:
      EXP, SQRT, POWER,1/X
      LN, GAUSS (density and distribution),
      GAMMA (Gamma/factorial), DEG/RAD (toggle)
      SIN, COS, TAN, ASIN, ACOS, ATAN
      SINH, COSH, TANH, ASINH, ACOSH, ATANH
      "a b c d" user menu (plays recorded keypresses from slot "1 2 3 4")


   USAGE OF EEPROM (512 bytes):
      Brightness  EEADDRSTACK   EEADDRCONST       EEADDRREC
      |           | x y z t m | | C0 C1 ... C41 | | 4*REC(51) |
      0           1          20 21            307 308       511
      |     1     |     20    | |      287      | |    204    |

      Constant Ci (EESTEP = 7 bytes): char1, char2, char3, double number (4 bytes)

  EXAMPLES FOR USER PROGRAM ("Type Recorder"):

    Example to "program" the annuity factor to program slot 0 (user menu "a"):
      - 1 REC (save to slot 1 = a)
      - SWAP ENTER ENTER 1 + SWAP ROT SWAP PWR 1/x CHS 1 + ROT ROT ROT /
      - REC
    To calculate the preset value for a given interest rate (8% = 0.08)
    and duration (5 years) enter:
      - 0.08 ENTER 5
      - MENU a (... f-EE EE f)
      - Results a present value of 3.99
      - Calculation duration: 1.5 s
    Interpretation:
      An annual rent of $1 for 5 years is equal to a present value of $3.99 invested
      with an interest rate of 8% (and vic versa).

    Example to "program" the conversion from rectangular to polar coordinates:
      - 2 REC (save to slot 2 = b)
      - ENTER ROT ROT SWAP ROT ENTER ROT SWAP
      - / ATAN ROT ROT * ROT ROT * + SQRT
      - REC
    To convert (1,1) to polar coordinates enter:
      - 1 ENTER 1
      - MENU b (... f-EE EE 6)
      - Results a lenght of SQRT(2) and with SWAP an angle of 45 degrees.
      - Calculation duration: 2.1 s

    Example to "program" the conversion from polar to rectangular coordinates:
      - 3 REC (save to slot 3 = c)
      - ENTER ROT ROT SWAP ROT ENTER ROT SWAP ROT
      - COS * ROT SIN * ROT ROT ROT
      - REC
    To convert (SQRT(2),45) to rectangular coordinates enter:
      - 45 ENTER 2 SQRT
      - MENU c (... f-EE EE 7)
      - Results a x-coordinate of 1 and with SWAP a y-coordinate of 1
      - Calculation duration: 2 s


  HOWTO WRITE PHYSICAL CONSTANTS TO EEPROM:
    1 Insert and store constant (f-8)
    2 Insert decimal values (Td, Zd, Yd) of characters (stack register TZY)
    3 Enter desired slot number (No) where to save the constant
    4 Enter SAVE (f-5)

  HOW TO READ STORED CONSTANT:
  Browse stored numbers with LOAD (f-4) and load to X with ENTER. For browsing use
  UP and DOWN keys or enter a number (2 digits) directly.

  PHYSICAL CONSTANTS, DECIMAL IDENTIFIER, NAME (source: WP34s manual):
    Constant         No  Td  Zd  Yd TZY Name
    ------------------------------------------------------------------------
    365.2425,     // 00 000 000 119   A Gregorian year
    5.291772E-11, // 01 000 119 092  Ao Bohr radius
    384.4E6,      // 02 000 119 073  Am Semi-major axis of the Moon's orbit
    1.495979E11,  // 03 000 119 123  Ae Semi-major axis of the Earth's orbit
    2.997942E8,   // 04 000 000 088   c Speed of light
    3.741772E-16, // 05 000 057 006  C1 First radiation constant
    0.01438777,   // 06 000 057 091  C2 Second radiation constant
    1.602177E-19, // 07 000 000 123   e Electron charge
    96485.34,     // 08 000 000 113   F Faraday constant
    2.502908,     // 09 000 113 119  Fa Feigenbaum's alpha
    4.669202,     // 10 000 113 094  Fd Feigenbaum's delta
    9.80665,      // 11 000 000 061   g Standard earth accelleration
    6.674083E-11, // 12 000 000 061   G Newtonian constant of gravitation
    7.748092E-5,  // 13 000 061 092  Go Conductance quantum
    0.9159656,    // 14 000 061 088  Gc Catalan's constant
    -2.002232,    // 15 000 061 123  Ge Lande's electron g-factor
    6.626069E-34, // 16 000 000 116   h Planck constant
    1.38065E-23,  // 17 000 000 114   k Boltzmann constant
    4.835979E14,  // 18 000 114 014  Kj Josephson constant
    1.616199,     // 19 000 056 115  lP Planck length
    9.109383E-31, // 20 000 073 123  me Electron mass
    7.349E22,     // 21 000 073 072  mM Mass of the Moon
    1.674927E-27, // 22 000 073 115  mn Neutron mass
    1.672622E-27, // 23 000 073 115  mp Proton mass
    2.17651E-8,   // 24 000 073 115  mP Planck mass
    1.660539E-27, // 25 000 073 028  mu Atomic mass unit
    1.492417E-10, // 26 073 028 088 Muc Energy equivalent of atomic mass unit
    1.883541E-28, // 27 000 073 073  mm Muon mass
    1.9891E30,    // 28 000 073 109  mS Mass of the Sun
    5.9736E24,    // 29 000 073 121  mE Mass of the Earth
    6.022141E23,  // 30 000 055 119  NA Avogadro's number
    101325,       // 31 000 115 092  po Standard atmospheric pressure
    1.875546E-18, // 32 000 103 115  qP Planck charge
    8.314472,     // 33 000 000 080   R Molar gas constant
    2.81794E-15,  // 34 000 080 123  re Electron radius
    25812.81,     // 35 000 080 114  RK Von Klitzing constant
    1.73753E6,    // 36 000 080 073  RM Mean radius of the Moon
    1.097373E7,   // 37 080 110 094 Ryd Rydberg constant
    6.96E8,       // 38 000 080 109  rS Mean radius of the Sun
    6.37101E6,    // 39 000 080 121  rE Mean radius of the Earth
    273.15,       // 40 000 120 092  To Standard temperature
    5.39106E-44,  // 41 000 120 115  tP Planck time
    1.416833E-32, // 42 120 115 115 TP- Planck temperature
    0.02241397,   // 43 000 062 073  Vm Molar volume of an ideal gas
    376.7303,     // 44 000 091 092  Zo Impedance of vacuum
    7.297353E-3,  // 45 000 008 119  _A Fine structure constant
    0.5772157,    // 46 008 061 121 _GE Euler-Mascheroni constant
    2.675222E8,   // 47 008 061 115 _GP Proton gyromagnetic ratio
    8.854188E-12, // 48 008 121 092 _Eo Electric constant or vacuum permitivity
    2.42631E-12,  // 49 008 056 123 _Le Compton wavelength of the electron
    1.319591E-15, // 50 008 056 084 _Ln Compton wavelength of the neutorn
    1.32141E-15,  // 51 008 056 115 _Lp Compton wavelength of the proton
    1.256673E-6,  // 52 008 073 092 _mo Magnetic constant or vacuum permeability
    9.274009E-24, // 53 008 073 124 _mB Bohr's magneton
    -9.284764E-24,// 54 008 073 123 _me Electron magnetic moment
    -9.662364E-27,// 55 008 073 084 _mn Neutron magnetic moment
    1.410607E-26, // 56 008 073 115 _mp Proton magnetic moment
    5.050783E-27, // 57 008 073 028 _mu Nuclear magneton
    -4.490448E-26,// 58 008 073 073 _mm Muon magnetic moment
    5.670373E-8,  // 59 008 109 124 _SB Stefan-Boltzmann constant
    1.618034,     // 60 000 008 115  _P Golden ratio
    2.067834E-15, // 61 008 115 092 _Po Magnetic flux quantum

  IDENTIFIERS OF SEVEN SEGMENT DISPLAY (ie code to display digit 3 =  79 = 4f):
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
                  _       _       _       _       _       _       _       _
             |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_|
    096 60                     |   |   |   |  _   _   _   _   _|  _|  _|  _|
                  _       _       _       _       _       _       _       _
             |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_|
    112 70   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|


  TODOs (if more memory could be allocated):
    - Clock, stopwatch
    - sleep mode
    - Statistics/L.R.,
    - SQR,LOG, 10x, Py,x, Cy,x,
    - ->P (convert to polar and ...), ->R (... rectangular coordinates)
    - ->H.MS (convert hours to hours, minutes, seconds ...), ->H (... and back)
    - ->RAD (convert degrees to radians), ->DEG (and back)


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
#define FIX               3 // Display 3 decimals
#define FIXMANT           3 // FIX in 10th-exponent
#define FIXSHOW           6 // FIX for SHOW
#define FIXMANTSHOW       6 // FIX in 10th-exponent
#define BRIGHTMAX         7 // Maximal value for brightness
#define MAXITERATE      100 // Maximal number of Taylor series loops to iterate
#define MAXMENU           6 // Number of MENUs (including 0)
#define NUMBEROFF        15 // Number of casted f-keys
#define EEADDRBRIGHTNESS  0 // Starting EE-address for saving brightness
#define EEADDRSTACK       1 // Starting EE-address for saving stack and mem with screensaver
#define EEADDRCONST      21 // Starting EE-address for constants
#define EEADDRREC       308 // Starting EE-sddress for saving "type recorder"
#define EECONSTCHAR       3 // Number of characters for one constant
#define EESTEP            7 // Number of bytes per EEPROM-slot (3 characters, 4 for one double)
#define EESLOTMAX        40 // Maximal number of 7-byte-entries in EEPROM (512k) (including 0)
#define MAXREC           51 // Number of record steps per slot
#define MAXRECSLOT        4 // Maximal slots to record

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
#define ENTER ' '
//#define '!'
//#define '"'
#define CHS '#'
//#define '$'
//#define '%'
//#define '&'
//#define '\''
#define REC '('
//#define PLAY ')'
#define MULTIPLY '*'
#define ADD '+'
//#define ','
#define SUBSTRACT '-'
#define DOT '.'
#define DIVIDE '/'
#define DIGIT0 '0'
#define DIGIT1 '1'
#define DIGIT2 '2'
#define DIGIT3 '3'
#define DIGIT4 '4'
#define DIGIT5 '5'
#define DIGIT6 '6'
#define DIGIT7 '7'
#define DIGIT8 '8'
#define DIGIT9 '9'
//#define ':'
//#define ';'
#define LOAD '<'
//#define '='
#define SAVE '>'
//#define '?'
//#define '@'
#define MENU 'A'
#define ACOSH 'B'
#define CE 'C'
//#define 'D'
#define EE 'E'
//#define 'F'
#define GAUSS 'G'
#define PLAYa 'H'
#define PLAYb 'I'
#define PLAYc 'J'
#define PLAYd 'K'
#define EXP 'L'
#define STO 'M'
#define ATANH 'N'
#define ACOS 'O'
#define POW 'P'
#define SQRT 'Q'
#define ROTUP 'R'
#define ASIN 'S'
#define ATAN 'T'
//#define 'U'
#define ASINH 'V'
//#define 'W'
//#define 'X'
//#define P2R 'Y'
//#define R2P 'Z'
//#define '['
//#define '\\'
//#define ']'
//#define '^'
//#define '_'
//#define '`'
#define ANNU 'a'
#define COSH 'b'
#define CLX 'c'
#define DEGRAD 'd'
//#define 'e'
#define SHIFT 'f'
#define FACT 'g'
//#define HMS2H 'h'
#define INV 'i'
//#define 'j'
//#define H2HMS 'k'
#define LN 'l'
#define RCL 'm'
#define TANH  'n'
#define COS 'o'
#define PEE 'p'
//#define 'q'
#define ROTDOWN 'r'
#define SIN 's'
#define TAN 't'
//#define 'u'
#define SINH 'v'
//#define 'w'
#define SWAP 'x'
#define SHOW 'y'
#define BRIGHTNESS 'z'
//#define '{'
//#define '|'
//#define '}'
//#define '~'

static const byte digit[] = {
  _7DIGIT0             , _7DIGIT1             , _7DIGIT2             , _7DIGIT3,
  _7DIGIT4             , _7DIGIT5             , _7DIGIT6             , _7DIGIT7,
  _7DIGIT8             , _7DIGIT9
};

// Keycodes (character produced by a buttonpress)
#define _KC1 'f'
#define _KC2 '7'
#define _KC3 '8'
#define _KC4 '9'
#define _KC5 'E'
#define _KC6 '4'
#define _KC7 '5'
#define _KC8 '6'
#define _KC9 '#'
#define _KC10 '1'
#define _KC11 '2'
#define _KC12 '3'
#define _KC13 'c'
#define _KC14 '0'
#define _KC15 '.'
#define _KC16 ' '


// GLOBAL VARIABLES

static double stack[STACKSIZE];
static byte recptr = 0;       // Pointer to recording step
static byte recslot = 0;      // Slot number for recording to EEPROM
static double rad = 180 / PI; // Multiplier for radiants
static byte decimals = 0;     // Number of decimals entered - used for input after decimal dot
static int8_t ee = 0;         // EExponent
static byte selectnr = 0;     // Number of selected menu/const item
static byte brightness = 0;   // Value for brightness of display (0...7)

// flags
static boolean isnewnumber = true; //* True if stack has to be lifted before entering a new number
static boolean ispushed = false;   // True if stack was already pushed by ENTER
static boolean isfpressed = false; // Function key pressed
static boolean isee = false;       // True if EE was pressed and exponent will be entered
static boolean isenteringnumber = false; //* Used to differ clear and clear-entry
static boolean isdot = false;      // True if dot was pressed and decimals will be entered
static boolean ismenu = false;     // True, if MENU was demanded
static boolean isprintmenu = true; // True if MENU/CONST should be printed
static boolean isdisplaydeactivated = false; // True if display is deactivated
static boolean isselectconst = false; // True if CONST browsing is demanded
static boolean isshow = false;     // True, if SHOW was demanded
static boolean isrec = false, isplay = false; // True, if "Type Recorder" records or plays

/*
  static double sx = 0.0, sxx = 0.0, sy = 0.0, sxy = 0.0; // Statistical/LR variables
  static byte sn = 0;
  #define SUM 'u'
  #define SUMc 'U'
  #define MEAN'j'
  #define CLRSUM'q'
  #define PREDICT 'W'
*/

// Menu variables
static const byte _msgs[MAXMENU + 1][DIGITS] = { // Menu display characters
  {_7LETTERE, 0, _7LETTERS, 0, _7LETTERP, 0, _7LETTERr, 0},          // exp_sqrt_pow_1/x
  {_7LETTERL, 0, _7LETTERG, 0, 0x31, 0, _7LETTERd, _7LETTERr},       // ln_gauss_gamma_deg/rad
  {0, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0},                  // _sin_cos_tan
  {_7HIGHLINE, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0},         // _asin_acos_atan
  {_7LETTERh, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0},          // _sinh_cosh_tanh
  {_7LETTERh, _7HIGHLINE, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0}, // _asinh_acosh_atanh
  {_7LETTERo, 0, _7LETTERb, 0, _7LETTERc, 0, _7LETTERd, 0},          // a_b_c_d user menu
};
static const byte _menuchar[MAXMENU + 1][4] = { // Menu keycodes
  {EXP, SQRT, POW, INV},        // exp_sqrt_pow_1/x
  {LN, GAUSS, FACT, DEGRAD},    // ln_gauss_gamma_deg/rad
  {0, SIN, COS, TAN},           // _sin_cos_tan
  {0, ASIN, ACOS, ATAN},        // _asin_acos_atan
  {0, SINH, COSH, TANH},        // _sinh_cosh_tanh
  {0, ASINH, ACOSH, ATANH},     // _asinh_acosh_atanh
  {PLAYa, PLAYb, PLAYc, PLAYd}, // a_b_c_d user menu
};


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

static byte buttoncast() { // Get button pattern and return keycode
  static const unsigned int _k[KEYS] = { // Indexing keyboard codes
    _K1, _K2,  _K3,  _K4,  _K5,  _K6,  _K7,  _K8,
    _K9, _K10, _K11, _K12, _K13, _K14, _K15, _K16
  };
  static const byte _kc[KEYS] = { // Indexing keycodes
    _KC1, _KC2,  _KC3,  _KC4,  _KC5,  _KC6,  _KC7,  _KC8,
    _KC9, _KC10, _KC11, _KC12, _KC13, _KC14, _KC15, _KC16
  };
  for (byte i = 0; i < KEYS; i++) if (getbuttons() & _k[i]) return (_kc[i]); // Casting
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

static void printbuf(byte *buf, byte dotpos) { // Write buffer and dot to display
  byte digbuf;
  if (dotpos > 0 && dotpos <= DIGITS) // Set dot
    buf[dotpos - 1] |= _7FULLSTOP;
  if (isrec) buf[7] = buf[7] | _7FULLSTOP; // Show REC light

  cmd(PRINTCMD); // Demand write command
  for (byte j = 0; j < SEGMENTS; j++) { // Write segment of all digits
    digbuf = 0;
    for (byte i = 0; i < DIGITS; i++) {
      digbuf = (digbuf << 1) | ((buf[i] & (0x01 << j)) ? 0x01 : 0x00);
    }
    for (byte i = 0; i < DIGITS; i++) { // Print segments for each digit
      digitalWrite(STROBE, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, 0xc0 | 2 * j); // Address - segment
      shiftOut(DATA, CLOCK, LSBFIRST, 0x00 | digbuf); // Data - digit
      digitalWrite(STROBE, HIGH);
    }
  }
}

static void printfloat(double f) { // Prints double or mantissa (show=true)
  static const byte digits[] = { // Character set to display numbers
    _7DIGIT0, _7DIGIT1, _7DIGIT2, _7DIGIT3, _7DIGIT4,
    _7DIGIT5, _7DIGIT6, _7DIGIT7, _7DIGIT8, _7DIGIT9
  };
  byte dispbuf[DIGITS] = {0, 0, 0, 0, 0, 0, 0, 0}; // Display buffer
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
    dispbuf[i] = digits[m % 10];
    m /= 10;
  }
  if (isshow) dispbuf[0] = _7APOSTROPHELEFT; // Sign for show
  else { // Rest of "normal print"
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
  printbuf(dispbuf, dot); // Write buffer and dot to display
}

static byte fcast(byte k) { // Returns f-key code for casting
  const byte _f_old[] = {_KC2,       _KC3,   _KC4,              // f-cast from
                         _KC5,       _KC6,   _KC7,   _KC8,
                         _KC9,       _KC10,  _KC11,  _KC12,
                         _KC13,      _KC14,  _KC15,  _KC16
                        };
  const byte _f_new[] = {RCL,        STO,    DIVIDE,            // to
                         MENU,       LOAD,   SAVE,   MULTIPLY,
                         ROTDOWN,    PEE,    REC,    SUBSTRACT,
                         BRIGHTNESS, SHOW,   SWAP,  ADD
                        };
  for (byte i = 0; i < NUMBEROFF; i++) {
    if (k == _f_old[i]) return (_f_new[i]);
  }
  return (NULL);
}

static void push_upper(void) { // Push upper part of stack
  memmove(&stack[2], &stack[1], 2 * sizeof(double));
}

static void push(void) { // Push stack
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
  for (byte i = _abs(e); i > 0; i--)  f *= 10;
  if (ne) f = 1 / f;
  return (f);
}

static double _exp_sin(double f, boolean isexp) { // Calculate exp with Taylor series
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

static double _atan_approx(double f) {
  return (f / (1 + 0.28 * f * f));
}

static double _atan(double f) {
  return (_abs(f) < 1 ? _atan_approx(f) : 0.5 * PI - _atan_approx(1 / f));
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
  cmd(0x88 | EEPROM.read(EEADDRBRIGHTNESS)); // Read brightness from EEPROM (saved with ff)
  for (byte i = 0; i < STACKSIZE; i++)       // Read stack from EEPROM (saved with ff)
    EEPROM.get(EEADDRSTACK + i * sizeof(double), stack[i]);

  //printbuf("@mXwPn@", 0); // Welcome message -ScArY-
  //printbuf("@vy88?@", 0); // Welcome message -HELLO-
  printfloat(stack[0]);     // No welcome message
}


void loop() {
  //while (1) { //*** Replaces setup-loop with a main-while (looses serial connection)
  byte key = NULL;
  static byte oldkey = NULL; // Previous key to check end of recording

  key = getkey(); // Read character

  if (isrec && key != NULL) { // ### Record keys and write to EEPPROM
    if (recptr < (recslot + 1)* MAXREC) {
      EEPROM.write(EEADDRREC + recptr, key); // Record key
      recptr++;
    }
  }
  else if (isplay) { // ### Plays recorded keys
    if (key == CLX) isplay = false; // C stops playing
    else if ( recptr < (recslot + 1)* MAXREC) {
      key = EEPROM.read(EEADDRREC + recptr); // Read key from EEPROM
      if (key == DIGIT2 && oldkey == SHIFT) { // Last record reached
        isplay = false;
        isfpressed = false;
        key = NULL;
      }
      oldkey = key;
      recptr++;
    }
  }

  if (ismenu || isselectconst) { // ### Selecting MENU or CONST
    byte dispbuf[DIGITS] = {0, 0, 0, 0, 0, 0, 0, 0};
    byte maxnr = MAXMENU;
    if (isselectconst) maxnr = EESLOTMAX;
    if (isprintmenu) {
      if (ismenu) memmove(dispbuf, _msgs[selectnr], DIGITS * sizeof(byte)); // Show menu
      else {
        dispbuf[0] = digit[_tens(selectnr)];
        dispbuf[1] = digit[_ones(selectnr)];
        for (byte i = 0; i < EECONSTCHAR; i++)
          dispbuf[i + DIGITS - EECONSTCHAR] = EEPROM.read(EEADDRCONST + selectnr * EESTEP + i);
      }
      printbuf(dispbuf, 0);
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
      printfloat(stack[0]);
      selectnr = 0;
      if (ismenu) ismenu = false;
      else isselectconst = false;
    }
    if (ismenu) {
      if (key == SHIFT || (key >= DIGIT7 && key <= DIGIT9)) { // Choose option
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
        printfloat(stack[0]);
        isselectconst = false;
        isnewnumber = true;
      }
      else if (key >= DIGIT0 && key <= DIGIT9) { // Enter constant number
        byte tmp = selectnr % 10 * 10 + key - '0';
        if (tmp <= maxnr) selectnr = tmp;
        else selectnr = key - '0';
        isprintmenu = true;
      }
      else key = NULL;
    }
  }
  else if (key == SHIFT) { // ### Toggle function key f
    if (isfpressed) { // Activate screensaver
      cmd(0x80); // Deactivate display - "1000 abbb" (a=0)
      isdisplaydeactivated = true;
      isfpressed = false;
      EEPROM.write(0, brightness);
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
  else if (key == EE && !isfpressed) { // ### Entering EE-input demanded
    if (isee && stack[0] > 0.0 && stack[0] != 1.0) { // Change sign of EE if EE is pressed the second time
      byte tmp = 0;
      if (stack[0] < 1.0 && log10(stack[0]) != (int)log10(stack[0])) tmp = 1;
      stack[0] = stack[0] / _pow10(2 * ((int)log10(stack[0]) - tmp));
      printfloat(stack[0]);
    }
    isee = true;
    ee = 0;
    key = NULL;
  }

  if (key != NULL) { // ### EXECUTE key if valid ###
    if (isfpressed) { // Cast pressed key to f-key if function key f is active
      key = fcast(key);
      isfpressed = false;
    }
    else if (key == CLX && isenteringnumber) key = CE; // Cast CLX to CE when number entering

    if ((key >= DIGIT0) && (key <= DIGIT9)) { // Numeric input
      if (isnewnumber) { // New number
        if (ispushed) ispushed = false;
        else push();
        stack[0] = isee ? 1.0 : 0.0; // Reset x (x=1 if EE-input follows)
        decimals = 0;
        isenteringnumber = true;
        isdot = false;
        isnewnumber = false;
      }
      if (isee) { // Entering EE (limit 29)
        if (ee % 10 < 3) ee = ee % 10 * 10 + key - '0';
        else ee = key - '0';
        stack[0] = stack[0] / _pow10(log10(stack[0])) * _pow10(ee);
      }
      else { // Entering mantissa
        if (isdot) stack[0] += (key - '0') / _pow10(++decimals); // Append decimal to number
        else stack[0] = stack[0] * 10 + key - '0'; // Append digit to number
      }
    }
    else if (key == ENTER) { // ENTER
      push();
      ispushed = true;
      isnewnumber = true;
      isee = false;
      isenteringnumber = false;
    }
    else if (key == CLX) { // CLx - Clear x
      stack[0] = 0.0;
      isee = false;
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
    else if (key == PLAYa || key == PLAYb || key == PLAYc || key == PLAYd) { // Toggle player ON/OFF
      if (isplay) isplay = false;
      else {
        if (key == PLAYa) recslot = 0;
        else if (key == PLAYb) recslot = 1;
        else if (key == PLAYc) recslot = 2;
        else recslot = 3;
        recptr = recslot * MAXREC;
        isplay = true;
        isnewnumber = true;
      }
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
      else if (key == BRIGHTNESS) { // BRIGHTNESS
        brightness = stack[0] > BRIGHTMAX ? BRIGHTMAX : (int)stack[0];
        cmd(0x88 | brightness);
        pull();
      }
      else if (key == STO) { // STO
        stack[4] = stack[0];
      }
      else if (key == RCL) { // RCL
        push();
        stack[0] = stack[4];
      }
      else if (key == SWAP) { // SWAP
        double tmp = stack[0];
        stack[0] = stack[1];
        stack[1] = tmp;
      }
      else if (key == ROTDOWN) { // ROT
        double tmp = stack[0];
        pull();
        stack[3] = tmp;
      }
      else if (key == SQRT) { // SQRT
        if (stack[0] > 0.0) stack[0] = _sqrt(stack[0]);
      }
      else if (key == EXP) {
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
      else if (key == PEE) { // PI
        if (!ispushed) push();
        stack[0] = PI;
      }
      else if (key == DEGRAD) { // Toggle ->DEG ->RAD
        if (rad == 1.0) rad = 180.0 / PI;
        else rad = 1.0;
      }
      else if (key == SAVE) { // Save signs (TZY) and number (mem) to slot X of EEPROM
        byte slotnr = _abs(stack[0]);
        if (slotnr < EESLOTMAX) {
          int addr = EEADDRCONST + slotnr * EESTEP;
          for (byte i = EECONSTCHAR; i > 0; i--) EEPROM.write(addr++, stack[i]);
          EEPROM.put(addr, stack[4]);
        }
      }
      else if (key == SIN || key == ASIN || key == COS || key == ACOS || key == TAN || key == ATAN) { // Trigonometric
        double si = _exp_sin(stack[0] / rad, false);
        double co = _sqrt(1 - si * si);
        double as = atan(stack[0] / _sqrt(1 - stack[0] * stack[0]));
        if (key == SIN) stack[0] = si;
        else if (key == ASIN) stack[0] = as * rad;
        else if (key == COS) stack[0] = co;
        else if (key == ACOS) stack[0] = (PI / 2 - as) * rad;
        else if (key == TAN) stack[0] = si / co;
        else stack[0] = atan(stack[0]) * rad;
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
      else if (key == GAUSS) { // GAUSS
        push_upper();
        stack[1] = _exp_sin(- log(1 + _exp_sin(-0.07 * stack[0] * stack[0] * stack[0] - 1.6 * stack[0], true)), true);
        stack[0] = _exp_sin(-0.5 * log(2 * PI) - stack[0] * stack[0] / 2, true);
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
      /*else if (key == ROTUP) { // ROT up      ABANDONED FUNCTIONS (partly "programable")
        double tmp = stack[3];
        push();
        stack[0] = tmp;
        }
        else if (key == ANNU) { // Annuity
        stack[0] = (1 - _exp_sin(-stack[0] * log(1 + stack[1]), true)) / stack[1];
        pull_upper();
        }
        else if(key== R2P) { // R->P
          double tmp = stack[1];
          stack[1] = atan(tmp / stack[0]) * rad;
          stack[0] = _sqrt(stack[0] * stack[0] + tmp * tmp);
        }
        else if(key==P2R) { // P->R
          double si = _exp_sin(stack[1] / rad, false);
          stack[1] = stack[0] * si;
          stack[0] = stack[0] * sqrt(1 - si * si);
        }
        /*case HMS2H: // H.MS->H
          lastx = x;
          x = (int)x + ((int)(100 * (x - (int)x))) / 60.0 + (100 * (100 * x - (int)(100 * x))) / 3600.0;
          break;
          case H2HMS: // H->H.MS
          lastx = x;
          x = (int)x + ((int)(60 * (x - (int)x))) / 100.0 + (60 * ((60 * (x - (int)x)) - (int)(60 * (x - (int)x)))) / 10000.0;
          break;
          /*case SUM: // SUM+
          sn++;
          sx += x;
          sy += y;
          sxx += x * x;
          sxy += x * y;
          push();
          lastx = x;
          x = sn;
          break;
          case SUMc: // SUM-
          sn--;
          sx -= x;
          sxx -= x * x;
          sy -= y;
          sxy -= x * y;
          push();
          lastx = x;
          x = sn;
          break;
          case MEAN: // MEAN, ST.DEV
          push();
          x = sqrt((sxx - sx * sx / sn) / (sn - 1));
          push();
          x = sx / sn;
          lastx = x;
          break;
          case LINREG: { // A+BX
          double tmp;
          push(&x, &y, &z, &u);
          lastx = x;
          x = tmp = (sxy / sn - sx / sn * sy / sn) / (sxx / sn - sx * sx / sn / sn);
          push(&x, &y, &z, &u);
          x = sy / sn - tmp * sx / sn;
          }
          break;
          case PREDICT: { // ->X,Y
          push();
          double tmp = (sxy / sn - sx / sn * sy / sn) / (sxx / sn - sx * sx / sn / sn);
          lastx = x;
          x = sy / sn - tmp * sx / sn + tmp * y; // ->y
          push();
          x = (z - sy / sn + tmp * sx / sn) / tmp; // ->x
          z = u;
          }
          break;
          case CLRSUM: // CLRSUM
          sn = sx = sxx = sy = sxy = 0.0;
          break;*/
      //} // End of switch

      ispushed = false; // Common reset of isee, isnewnumber, ...
      isnewnumber = true;
      isee = false;
      isenteringnumber = false;
    } //End of big IF ELSE

    //Serial.print(stack[0]); Serial.print(" "); Serial.print(stack[1]); Serial.print(" "); Serial.println(stack[2]);
    printfloat(stack[0]);
    isshow = false;
  }
}

//} //*** Replaces setup-loop with a main-while (looses serial connection)

