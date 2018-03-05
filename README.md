# ScArY - Scientific RPN calculator on ATTINY
Version 1.0 ... (c) 2018 by deetee/zooxo

## What is ScArY?
ScArY is a scientific RPN calculator on an ATTINY85 and a  QYF-TM1638-board (8 digit LED display with 16 buttons controlled with 3 pins). ScArY is capable of familiar functions of RPN calculators (i.e. stack operations) and many mathematical operations (i.e. trigonometic functions) as well as some special functions like calculating annuities or gaussian distributions.
Due to the memory restrictions of the ATTINY85 (8 kilobytes) some compromises were  made to offer so many functions. So the numbers are shown in SCI notation only (see below).

Another compromise is the lack of checking for errors - usually there is no readable display  if an error occurs.

Due to the 8-bit-processor ARC calculates only 5 to 6 digits exactly. This should be enough for most calculations (except you are a bookkeeper who wants to add billion-amounts with cent-accuracy).

## On which hardware does ScArY run?
Compile the attached file "scary_1_0-ino" with your arduino suite and upload the code to your ATTINY85 with some programmer hardware or an Arduino as ISP (like I did). Connect the ATTINY85 pins (5/6/7 resp. data/clock/strobe) with the corresponding pins on the QYF-TM1638-board, power them up (5V Vcc and GND) and you are running.

## Which Commands does ScArY support (COMMANDS and KEYS)?    
### Basic keys:
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ., EE, CHS, ENTER, C/CE, f
### f-keys:
+, -, *, / (basic operations)      STO, RCL, SHOW, SWAP, LASTx, ROT+, ROT-, SQRT, P      MENU (browse menu)      BRIGHTNESS (set brightness of display)      zZZ (toggle screensaver)
### MENU-functions:
POWER, 1/X, EXP, LN      SIN, COS, TAN, ASIN, ACOS, ATAN      SINH, COSH, TANH, ASINH, ACOSH, ATANH      ANNU (present value for a given interest rate and duration)      GAUSS (density and distribution)      FACT, DEG, RAD

## A short Video of a Miniaturized Mobile ARC
## Some Pictures of a Miniaturized ScArY
## The Circuit Diagram


KEYBOARD LAYOUT:     f[] [zZZ]           7 [MENU]    8 [SWAP]        9 [/]      EE [ROT-] (UP)     4 [PI]      5 [SQRT]        6 [*]     CHS [ROT+] (DOWN)   1 [STO]     2 [RCL]         3 [-]       c [brightness]    0 [SHUOW]   . [LASTx]   ENTER [+]  MENU (f[7]):       P (POW)    r (1/x)     E (EXP)     L  (LN)                  S (SIN)     c (COS)     t  (TAN)       =          S (ASIN)    c (ACOS)    t  (ATAN)       H          S (SINH)    c (COSH)    t  (TANH)       H=         S (ASINH)   c (ACOSH)   t  (ATANH)       A (ANNU)   G (GAUSS)   F (FACT)    dr (DEG/RAD)  8-DIGITS SCIENTIFIC DISPLAY (SCI notation):       mantissa  exponent       |         |     - m.m m m - e e     |         |     sign      EE-sign  ENTERING NUMBERS:    1.) Enter mantissa (with '.' if applicabel)    2.) If applicable: Enter EE to enter exponent (limited to 29)    3.) If applicable: Toggle sign of exponent with EE    4.) If applicable: Toggle sign of number with CHS  
 
 

## A short Video of a Miniaturized Mobile ARChttp://youtu.be/F3uRQhoFq40
In this video you can see the following calculations:* Approximating PI with 22/7* Inserting -3.14159265E-2* Setting to 6 decimal places (FIX)* Calculating the mean value and standard deviation of 4, 5 and 6 (including SWAP)* Convert a rectangular vector (1,1) to polar and back (swap to change arguments)* Calculating the Gauss normal distribution and density function at 0 (swap to change results)* Starting a clock at 8:16 (and 50 seconds)
## Some Pictures of a Miniaturized Mobile ARC
![ARC pictures](https://cloud.githubusercontent.com/assets/16148023/18578469/618225e8-7bf0-11e6-8ab1-5494e8903779.jpg "pictures")
## The Circuit Diagram![ARC circuit diagram](https://cloud.githubusercontent.com/assets/16148023/18578474/65d0e99a-7bf0-11e6-9758-1d2680048e55.png "circuit")
## Key Assignment for the 12-Key-Keyboard![ARC assignment of keys](https://cloud.githubusercontent.com/assets/16148023/18578478/6a3a0458-7bf0-11e6-8bd6-32abda655e6e.png "keys")
