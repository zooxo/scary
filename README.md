# ScArY - Scientific RPN calculator based on an ATTINY85
Version 3.0 ... (c) 2018 by deetee/zooxo

ScArY is free software. You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation.
## PREAMBLE
It is amazing how much calculator power a simple microcontroller like the ATTINY85 is able to perform. This 8 pin 8-bit core microcontroller provides only 8 kilobytes of flash memory to store program code, 512 bytes of RAM to handle variables and 512 bytes of EEPROM to save settings and user data permanently. So every byte is valuable and it took me many hours to optimize the code and to decide which function or feature to choose.

In general, functionality and functions outweighted comfort and error handling which can be seen, for instance, looking at the permanent scientific display format or a "non interpretable" display after dividing by zero. Thus the user has to follow the calculation process more strictly than on conventional RPN calculators.

Enjoy!    deetee
## INTRODUCTION
ScArY is a scientific calculator based on an ATTINY85 microcontroller and a QYF-TM1638-board (8 digit LED display with 16 buttons controlled with 3 pins).

ScArY is capable of basic arithmetical functions and familiar operations of RPN calculators (ie stack operations) as well as a wide range of scientific functions and probability or statistic operations.

In addition ScArY has some special features like saving its state, handling user defined constants and saving sequences of keypresses to EEPROM permanently ("Type Recorder").
## THE CALCULATOR
### 8-DIGITS SCIENTIFIC DISPLAY (permanent SCI notation):
```
    mantissa  exponent
    |         |
  - m.m m m - e e.
  |         |    |
  sign  EE-sign  Indicator for recording
```
### KEYBOARD LAYOUT:
```
  f[] [zZZ RESCUE]   7 [MENU]    8 [REC]        9 [/]
  EE [SUM] (UP)      4 [CONST]   5 [SAVE]       6 [*]
  CHS [ROT] (DOWN)   1 [RCL]     2 [STO]        3 [-]
  CLX [brightness]   0 [SHOW]    . [SWAP]   ENTER [+]
```
### MENU:
```
  E      F      G      H       ... User Menus ("Type Recorder")
  a      b      c      d
  EXP    SQRT   POW    INV     ... Basic Functions
  LN     ANNU   ->P    ->R     ... Logarithm, Annuity, Polar/Rectangular
  GAMMA  GAUSS  STAT   LR      ... Probability, Statistics, Linear Regression
  (t)    SIN    COS    TAN     ... Trigonometric Functions
  (t.)   ASIN   ACOS   ATAN
  (h)    SINH   COSH   TANH    ... Hyperbolic Functions
  (h.)   ASINH  ACOSH  ATANH
```
### ENTERING NUMBERS:
```
  1 Enter mantissa (with '.' if applicable)
    Press ENTER to push mantissa to stack
  2 To enter power of ten:
    Enter exponent and (if applicable) change sign of exponent with CHS
  3 Press EE to link the mantissa with the exponent
  4 If applicable: Toggle sign of number with CHS
```
## OPERATIONS and KEYS
### BASIC KEYS:
```
  0 1 2 3 4 5 6 7 8 9 . ... Digits and decimal point
  CHS EE                ... Change sign and enter exponent (actually Y*10^X)
  ENTER                 ... Enter number (push stack)
  C                     ... Clear X, clear entry or escape/stop
  f                     ... Function or shift to choose shifted keys
```
### F-KEYS:
```
  + - * /    ... Basic operations
  STO RCL    ... Store number to respectively recall number from memory
  SHOW       ... Show full mantissa of number (7 digits without decimal point)
  SWAP       ... Swap X and Y register of stack (X<->Y)
  ROT        ... Rotate stack (X=Y Y=Z Z=T T=X)
  SUM        ... Enter X-data for statistics or X,Y-data for linear regression
  MENU       ... Browse menu
  REC        ... Records 8x52 keypresses (to recall via user menu "abcdEFGH")
  CONST      ... Browse up to 10 user saved constants
  SAVE       ... Save up to 10 user saved constants
  zZZ RESCUE ... Toggle screensaver and save calculator state to EEPROM
  BRIGHTNESS ... Set brightness of display (0...7)
```
### MENU-FUNCTIONS:
```
  EXP LN SQRT POWER INV            ... Basic scientific operations
  ANNU ->P ->R                     ... Annuity, polar/rectangular ... x)
  GAMMA GAUSS                      ... Gamma/!, Probability(PDF/CDF)  ... x)
  STAT LR                          ... Statistics, linear regression
  SIN  COS  TAN  ASIN  ACOS  ATAN  ... Trigonometric
  SINH COSH TANH ASINH ACOSH ATANH ... Hyperbolic ... x)
  a b c d E F G H                  ... user menu (play recorded keypresses)
  
  x) ... Some functions (ANNU, ->P, ->R, GAMMA, GAUSS, HYP) may affect the
         whole stack as they are calculated with basic operations.
```
## SPECIALITIES
### PREPARING ScArY AFTER FLASHING:
As ScArY saves the state (stack and brightness values) when pressing the f-key twice (screensaver) it also loads the state after switching on. But flashing the ATTINY may clear the EEPROM. So the loaded state when switching on the first time after flashing gets undefined values (... and maybe a dark or "non interpretable" display).

So the following procedure may help to bring ScArY in a defined state:
```
  1 Press CLX (X=0)        ... even if the display remains dark
  2 Set brightness (f-CLX) ... a "non interpretable" display is readable
  3 Press CLX (X=0)        ... value of 0 should be readable
  4 Press ENTER 3 times    ... clears the stack (X=Y=Z=T=0)
  5 Press STO (f-2)        ... clears mem
  6 Press f twice (f-f)    ... saves state to EEPROM (activates screensaver)
  7 Press f                ... (re)activates the screen
```
### WORKING WITH CONSTANTS:
ScArY is capable to save up to 10 constants to permanently to the EEPROM memory. Additional to each constant up to three characters can be saved to recall and browse the constants very comfortable. See "Appendix - Physical Constants" for some physical constants.
```
  Example to write PI to slot O:
    1 3.141593 STO        ... store PI
    2 0 ENTER 115 ENTER 6 ... enter 3 characters (" PI"), see "Appendix - Identifiers of 7-Segment Displays"        
    3 ENTER 0             ... enter slot 0
    4 SAVE                ... save constant to EEPROM

  Example to load stored constant:
    1 CONST         ... enter the catalogue of constants
                        Use UP/DOWN-keys for browsing or enter a number directly (0...9)
    2 ENTER         ... load constant to stack
```
### TYPE RECORDER:
ScArY is able to record 8 user defined sequences of keypresses (up to 52 each) and "replay" them by selecting the appropriate user menu entry. These user defined key sequences or formulas are stored to the EEPROM memory permanently.
```
  Example to record temperature conversion (Fahrenheit -> Celsius):
    1 3 REC      ... record to slot 3 (user menu c)
    2 32 - 1.8 / ... convert to celsius
    3 REC        ... stop recording

  Convert Fahrenheit to Celsius:
    1 50 MENU->c ... play recorded user formula in slot c (=3)
    2 X=10       ... 50 Fahrenheit are 10 Celsius
```
### ANNUITY (PRESENT VALUE):
```
  Example to calculate the present value of a $1 5 year return with an interest rate of 8%:
    1 .08 ENTER 5 ANNU ... annuity factor for 5 years and 8%
    2 X=3.99           ... 5 years $1 each are equal to ~$4 invested with 8%
```
### GAUSS:
```
y                     ^                     |                   1 ------------------------                     |       +++++++ CDF (Cumulative Distribution Function)                     |   +                     | +                     (x)         .                     |+              CDF = integral(PDF) = 1/(1+exp(-0.07*x^3-1.6*x))                     +                      (-inf)                   **+**                **  +|   **                  +  |     *         PDF = 1/sqrt(2*PI)*exp(-x*x/2)             ** +    |      **      +*+*+*+        |         ***** PDF (Probability Density Function)      ---------------+------------------------> x
      Example to calculate PDF and CDF at x=0:        1 0 GAUSS        2 PDF=0.3989=1/sqrt(2*PI)        3 SWAP        4 CDF=0.5
```
### STATISTICS, LINEAR REGRESSION:
```
y        ^                /        |  Ypredict(x=1.5)=4      4 - <----------- /        |             /        |            / ^        |           /  |        |          /      3 -        [*] P2=(1|3)        |        /        |       /      ^        |      /       |        |     /      2 -   [*] P1=(0.5|2)        |   /        |_ /           ^        | /|           |        |/ |           |      1 -  |           |       /|  |           |      / |  |           |     /  |  | Xpredict(y=1.5)=0.25        |  v           |    ----+----+----|----+----|-> x        0       | 1         2                |                Xmean=0.75             |  |           ->|--|<- Standard Deviation S=0.354
      Example to calculate mean value and standard deviation:        1 0.5 SUM 1 SUM ... enter X-data        2 STAT        3 Xmean=0.75 (mean value)        4 SWAP        5 S=0.354 (standard deviation)
      Example to calculate a linear regression:        1 2 ENTER 0.5 SUM ... enter YX-data of first node        2 3 ENTER 1 SUM   ... enter YX-data of second node        3 1.5 LR          ... enter desired x/y-value        4 X=0.25          ... predicted x-value for y=1.5        5 SWAP        6 Y=4             ... predicted y-value for x=1.5
      Example to calculate the line of best fit:        1 2 ENTER 0.5 SUM ... enter YX-data of first node        2 3 ENTER 1 SUM   ... enter YX-data of second node        3 1 LR SWAP       ... enter x-value of 1        4 Y=3             ... predicted y-value for x=1        5 0 LR ROT        ... enter x-value of 0        6 Y=1             ... predicted y-value for x=0 (y-axis-intercept)        7 -               ... substract y(1) and y(0) (=slope)        8 X=2             ... slope of best-fit-line        9 y = 2 * x + 1   ... formula of best-fit-line
```
## APPENDIX
### HARDWARE:
```__________________            -.---------           | 8.8.8.8.8.8.8.8. |           | 1()   ()8 |-VCC  GND-|GND               |           | 2(3) (2)7 |----------|DIO   *   *   *   |           | 3(4) (1)6 |----------|CLK   *   *   *   |       GND-| 4()  (0)5 |----------|STB   *   *   *   |            -----------       VCC-|VCC   *   *   *   |              ATTINY85             ------------------       VCC=5V                          QYF-TM1638
```
### USAGE OF EEPROM (512 bytes):
```
| Brightness|   Stack   | |   CONSTANTS  | |  RECORDER |      |           | X Y Z T M | | C0 C1 ... C9 | | 8*REC(52) |      0           1          20 21            90 91        507      |     1     |     20    | |      70      | |    416    |
```
### ASCII TABLE:
```
DEC     |  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5          HEX |  0 1 2 3 4 5 6 7 8 9 a b c d e f      ------------------------------------------      032 20  |    ! " # $ % & ' ( ) * + , - . /      048 30  |  0 1 2 3 4 5 6 7 8 9 : ; < = > ?      064 40  |  @ A B C D E F G H I J K L M N O      080 50  |  P Q R S T U V W X Y Z [ \ ] ^ _      096 60  |  ` a b c d e f g h i j k l m n o      112 70  |  p q r s t u v w x y z { | } ~
```
### IDENTIFIERS OF 7-SEGMENT DISPLAY:
```
(i.e. code to display digit 3 =  79 = 4f)
      DEC       0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15          HEX   0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f                    _       _       _       _       _       _       _       _                         |   |           |   |           |   |           |   |      000 00                     |   |   |   |  _   _   _   _   _|  _|  _|  _|                    _       _       _       _       _       _       _       _                         |   |           |   |           |   |           |   |      016 10   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|                    _       _       _       _       _       _       _       _               |   |   | | | | |   |   | | | | |   |   | | | | |   |   | | | |      032 20                     |   |   |   |  _   _   _   _   _|  _|  _|  _|                    _       _       _       _       _       _       _       _               |   |   | | | | |   |   | | | | |   |   | | | | |   |   | | | |      048 30   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|                    _       _       _       _       _       _       _       _                _   _   _|  _|  _   _   _|  _|  _   _   _|  _|  _   _   _|  _|      064 40                     |   |   |   |  _   _   _   _   _|  _|  _|  _|                    _       _       _       _       _       _       _       _                _   _   _|  _|  _   _   _|  _|  _   _   _|  _|  _   _   _|  _|      080 50   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|                    _       _       _       _       _       _               _               |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_|      096 60                     |   |   |   |  _   _   _   _   _|  _|  _|  _|                    _       _       _       _       _       _       _       _               |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_| |_  |_  |_| |_|      112 70   |   |   |   |   | | | | | | | | |_  |_  |_  |_  |_| |_| |_| |_|
```
### PHYSICAL CONSTANTS:
```
Constant      ID  Name      ---recommended:-------------------------------------------      3.141593      PI  Number PI      0.01745329    RpD Radians per Degrees      ---from WP34S-Manual:-------------------------------------      365.2425      A   Gregorian year      5.291772E-11  Ao  Bohr radius      384.4E6       Am  Semi-major axis of the Moon's orbit      1.495979E11   Ae  Semi-major axis of the Earth's orbit      2.997942E8    c   Speed of light      3.741772E-16  C1  First radiation constant      0.01438777    C2  Second radiation constant      1.602177E-19  e   Electron charge      96485.34      F   Faraday constant      2.502908      Fa  Feigenbaum's alpha      4.669202      Fd  Feigenbaum's delta      9.80665       g   Standard earth accelleration      6.674083E-11  G   Newtonian constant of gravitation      7.748092E-5   Go  Conductance quantum      0.9159656     Gc  Catalan's constant      -2.002232     Ge  Lande's electron g-factor      6.626069E-34  h   Planck constant      1.38065E-23   k   Boltzmann constant      4.835979E14   Kj  Josephson constant      1.616199      lP  Planck length      9.109383E-31  me  Electron mass      7.349E22      mM  Mass of the Moon      1.674927E-27  mn  Neutron mass      1.672622E-27  mp  Proton mass      2.17651E-8    mP  Planck mass      1.660539E-27  mu  Atomic mass unit      1.492417E-10  Muc Energy equivalent of atomic mass unit      1.883541E-28  mm  Muon mass      1.9891E30     mS  Mass of the Sun      5.9736E24     mE  Mass of the Earth      6.022141E23   NA  Avogadro's number      101325        po  Standard atmospheric pressure      1.875546E-18  qP  Planck charge      8.314472      R   Molar gas constant      2.81794E-15   re  Electron radius      25812.81      RK  Von Klitzing constant      1.73753E6     RM  Mean radius of the Moon      1.097373E7    Ryd Rydberg constant      6.96E8        rS  Mean radius of the Sun      6.37101E6     rE  Mean radius of the Earth      273.15        To  Standard temperature      5.39106E-44   tP  Planck time      1.416833E-32  TP- Planck temperature      0.02241397    Vm  Molar volume of an ideal gas      376.7303      Zo  Impedance of vacuum      7.297353E-3   _A  Fine structure constant      0.5772157     _GE Euler-Mascheroni constant      2.675222E8    _GP Proton gyromagnetic ratio      8.854188E-12  _Eo Electric constant or vacuum permitivity      2.42631E-12   _Le Compton wavelength of the electron      1.319591E-15  _Ln Compton wavelength of the neutorn      1.32141E-15   _Lp Compton wavelength of the proton      1.256673E-6   _mo Magnetic constant or vacuum permeability      9.274009E-24  _mB Bohr's magneton      -9.284764E-24 _me Electron magnetic moment      -9.662364E-27 _mn Neutron magnetic moment      1.410607E-26  _mp Proton magnetic moment      5.050783E-27  _mu Nuclear magneton      -4.490448E-26 _mm Muon magnetic moment      5.670373E-8   _SB Stefan-Boltzmann constant      1.618034      _P  Golden ratio      2.067834E-15  _Po Magnetic flux quantum
```
