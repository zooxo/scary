# ScArY - Scientific RPN calculator on ATTINY
Version 2.0 ... (c) 2018 by deetee/zooxo

Special thanks to the mohpc-forum (particular Pauli) for saving bytes an providing ideas.
  
## What is ScArY?
ScArY is a scientific calculator based on an ATTINY85 microcontroller and a QYF-TM1638-board (8 digit LED display with 16 buttons controlled by 3 pins).

ScArY is capable of familiar functions of RPN calculators (ie stack operations) and many mathematical operations (ie trigonometic) as well as some special functions like gaussian distribution and gamma. In addition ScArY can save its state,  physical constants and sequences of keypresses permanently to the EEPROM.

Due to the memory restrictions of the ATTINY85 (8 kilobytes) some compromises were made to offer so many functions. So the numbers are shown in SCI notation only (see below). Another compromise is the lack of checking for errors - usually the display is unreadable if an error occurs.

## What's new in version 2?
* ScArY saves its actual status (stack, brightness setting) permanantly to EEPROM. This is done when the screensaver is activated (keys f-f). Note the procedure to initialize these values after flashing the software (EEPROM was deleted).
* It is possible to save up to 41 constants/numbers initialized with up to 3 characters to EEPROM. The saved constants can be browsed and reloaded very convenient. See the section of recommended physical constants.
* Some kind of "Type Recorder" was realized. It is possible to save 4 slots with up to 51 keypresses to the EEPROM and recall them with user defined menu entries.

## On which hardware does ScArY run?
Compile the attached file "scary_2_0-ino" with your arduino suite and upload the code to your ATTINY85 with some programmer hardware or an Arduino as ISP (like I did). Connect the ATTINY85 pins (5/6/7 resp. data/clock/strobe) with the corresponding pins on the QYF-TM1638-board, power them up (5V Vcc and GND) and you are running.

## Which Commands does ScArY support (COMMANDS and KEYS)?    
### Basic keys:
* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ., EE, CHS, ENTER, C/CE, f
### f-keys:
* +, -, *, / (basic operations)
* STO, RCL, SHOW, SWAP, ROT, SQRT, PI
* MENU (browse menu)
* BRIGHTNESS (set brightness of display)
* zZZ (toggle screensaver)
### MENU-functions:
* EXP, SQRT, POWER, 1/X,
* LN, GAUSS (PDF and CDF), GAMMA (Gamma/factorial), DEG/RAD (toggle)
* SIN, COS, TAN, ASIN, ACOS, ATAN
* SINH, COSH, TANH, ASINH, ACOSH, ATANH
* "a b c d" user menu (plays recorded keypresses from slot "1 2 3 4"

## How to Enter a Number?
  1. Enter mantissa (with '.' if applicable)
  2. If applicable: Enter EE to enter exponent (limited to 29)
  3. If applicable: Toggle sign of exponent with EE
  4. If applicable: Toggle sign of number with CHS

## A short Video of a Miniaturized ScArY
Version 1.0: https://youtu.be/q-9j547xWfg

Version 2.0: https://youtu.be/O8WEHZN1RMk

## Some Pictures of a Miniaturized ScArY
![pics](https://user-images.githubusercontent.com/16148023/36966765-be3b98d6-2055-11e8-950e-49108db44dd6.png)

## The Circuit Diagram
![circuit](https://user-images.githubusercontent.com/16148023/36966763-bdd99212-2055-11e8-9185-e1ec609a81a4.png)

## The Keyboard Layout
![keyboard2](https://user-images.githubusercontent.com/16148023/37587218-9ac6e782-2b56-11e8-8b4f-b3bd2d1db401.png)

     f[] [zZZ RESCUE]    7 [RCL]     8 [STO]         9 [/]
      EE [MENU] (UP)     4 [CONST]   5 [SAVE]        6 [*]
     CHS [ROT] (DOWN)    1 [PI]      2 [REC]         3 [-]
       c [brightness]    0 [SWAP]    . [SHOW]    ENTER [+]

       E (EXP)    S (SQRT)    P (POW)      r (1/x)
       L (LN)     G (GAUSS)   | (GAMMA)   dr (DEG/RAD) 
                  S (SIN)     c (COS)      t (TAN)
       ^          S (ASIN)    c (ACOS)     t (ATAN)
       h          S (SINH)    c (COSH)     t (TANH)
       h^         S (ASINH)   c (ACOSH)    t (ATANH)
       a (PLAY1)  b (PLAY2)   c (PLAY3)    d (PLAY4)

## FIRST LAUNCH AFTER FLASHUNG THE ATTINY85:
As ScArY saves the state (stack and brightness values) when pressing the f-key twice (screensaver) it also loads the state after switching on. But flashing the ATTINY may clear the EEPROM. So the loaded state when switching on the first time after flashing gets undefined values (... and maybe a dark or nonsense display).

So the following procedure may help to bring ScArY in a defined state:
  1 Press CLX (X=0) ... even if the display remains dark
  2 Set brightness (f-CLX) ... at least a nonsense display should be readable
  3 Press CLX (X=0) ... value of 0 should be readable
  4 Press ENTER 3 times to clear the stack (X=Y=Z=T=0)
  5 Press STO (f-1) to clear mem
  6 Press f twice (f-f) to save the state to the EEPROM (activates screensaver too)
  7 Press f to (re)activate the screen
  8 Done! (till you flash the ATTINY again)

## 8-DIGITS SCIENTIFIC DISPLAY (SCI notation):
```
       mantissa  exponent
       |         |
     - m.m m m - e e.
     |         |    |
     sign  EE-sign  Indicator for recording
```

## ENTERING NUMBERS:
  1 Enter mantissa (with '.' if applicable)
  2 If applicable: Enter EE to enter exponent (limited to 29)
  3 If applicable: Toggle sign of exponent with EE
  4 If applicable: Toggle sign of number with CHS


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


## USAGE OF EEPROM (512 bytes):
      Brightness  EEADDRSTACK   EEADDRCONST       EEADDRREC
      |           | x y z t m | | C0 C1 ... C41 | | 4*REC(51) |
      0           1          20 21            307 308       511
      |     1     |     20    | |      287      | |    204    |

      Constant Ci (EESTEP = 7 bytes): char1, char2, char3, double number (4 bytes)

## EXAMPLES FOR USER PROGRAMS ("Type Recorder"):

### Example to "program" the annuity factor to program slot 0 (user menu "a"):
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

### Example to "program" the conversion from rectangular to polar coordinates:
      - 2 REC (save to slot 2 = b)
      - ENTER ROT ROT SWAP ROT ENTER ROT SWAP
      - / ATAN ROT ROT * ROT ROT * + SQRT
      - REC
    To convert (1,1) to polar coordinates enter:
      - 1 ENTER 1
      - MENU b (... f-EE EE 6)
      - Results a lenght of SQRT(2) and with SWAP an angle of 45 degrees.
      - Calculation duration: 2.1 s

### Example to "program" the conversion from polar to rectangular coordinates:
      - 3 REC (save to slot 3 = c)
      - ENTER ROT ROT SWAP ROT ENTER ROT SWAP ROT
      - COS * ROT SIN * ROT ROT ROT
      - REC
    To convert (SQRT(2),45) to rectangular coordinates enter:
      - 45 ENTER 2 SQRT
      - MENU c (... f-EE EE 7)
      - Results a x-coordinate of 1 and with SWAP a y-coordinate of 1
      - Calculation duration: 2 s


## HOWTO WRITE PHYSICAL CONSTANTS TO EEPROM:
    1 Insert and store constant (f-8)
    2 Insert decimal values (Td, Zd, Yd) of characters (stack register TZY)
    3 Enter desired slot number (No) where to save the constant
    4 Enter SAVE (f-5)

## HOW TO READ STORED CONSTANT:
  Browse stored numbers with LOAD (f-4) and load to X with ENTER. For browsing use
  UP and DOWN keys or enter a number (2 digits) directly.

## PHYSICAL CONSTANTS, DECIMAL IDENTIFIER, NAME
(source: WP34s manual):
```
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
```
  
## IDENTIFIERS OF SEVEN SEGMENT DISPLAY
(ie code to display digit 3 =  79 = 4f):
```
    DEC       0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        HEX   0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f
                  _       _       _       _       _       _       _       _
                       |   |           |   |           |   |           |   |
    000 00                     |   |   |   |  _   _   _   _   _|  _|  _|  _|
                  _       _       _       _       _       _       _       _
                       |   |           |   |           |   |           |   |
    016 10   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|
                  _       _       _       _       _       _       _       _
             |   |   | | | | |   |   | | | | |   |   | | | | |   |   | | | |
    032 20                     |   |   |   |  _   _   _   _   _|  _|  _|  _|
                  _       _       _       _       _       _       _       _
             |   |   | | | | |   |   | | | | |   |   | | | | |   |   | | | |
    048 30   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|
                  _       _       _       _       _       _       _       _
              _   _   _|  _|  _   _   _|  _|  _   _   _|  _|  _   _   _|  _|
    064 40                     |   |   |   |  _   _   _   _   _|  _|  _|  _|
                  _       _       _       _       _       _       _       _
              _   _   _|  _|  _   _   _|  _|  _   _   _|  _|  _   _   _|  _|
    080 50   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|
                  _       _       _       _       _       _       _       _
             |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_|
    096 60                     |   |   |   |  _   _   _   _   _|  _|  _|  _|
                  _       _       _       _       _       _       _       _
             |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_|
    112 70   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|
```
