/*
  Welcome to ScArLEt (Scientific Calculator on Arduino with RPN)
  Version 1.0 ... (c) 2018 by deetee/zooxo

  KEYBOARD LAYOUT:

     f[] [zZZ]          7 [MENU]    8 [CONST]       9 [/]
      EE [SUM+] (UP)    4 [PRG]     5 [RUN]         6 [*]
     CHS [ROT] (DOWN)   1 [STO]     2 [RCL]         3 [-]
       c [brightness]   0 [SWAP]    . [LASTx]   ENTER [+]


  COMMANDS and KEYS:
    Hardware/Settings:
      SHIFT-SHIFT    Screensaver till SHIFT will be pressed again
      z   BRIGHTNESS Set brightness of display (0 <= X <= 8)
    Basic keys:
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, .  Number input
      #   CHS        Change sign of X
      c/C C/CE       Clear X or clear last entry or escape menu
      E   EE         Enter or change sign of enter-exponent
      f   SHIFT      Shift or function key
          ENTER      Enter or push stack
    Memory:
      M   STO        Store Y to memory X
      m   RCL        Recall store X
    Stack operations:
      R   ROTup      Rotate stack up
      r   ROTdown    Rotate stack down
      x   SWAP       Swap X and Y
      X   LASTX      Recall last inserted X
    Menu
      A   MENU       Call menu
    Mathematical Functions:
      +   ADD        Add X and Y
      -   SUBSTRACT  Substract X from Y
      +   MULTIPLY   Multiply X and Y
      /   DIVIDE     Divide Y by X
      p   PI         Recall constant PI
      i   INVERT     Invert X (1/X)
      Q   SQRT       Calculate the square root of X
      ^   POW        Calculate Y^X
      L   EXP        Calculate the exponential value of X
      l   LN         Calculate the natural logarithm of X
      s/S SIN/ASIN   Calculate sine and arcus sine of X
      o/O COS/ACOS   Calculate cosine and arcus cosine of X
      t/T TAN/ATAN   Calculate tangent and arcus tangent of X
      v/V SINH/ASINH Calculate hyperbolic sine and area sine of X
      b/B COSH/ACOSH Calculate hyperbolic cosine and area cosine of X
      n/N TANH/ATANH Calculate hyperbolic tangent and area tangent of X
      a   ANNU       Calculate preset value of interest rate (Y) and duration (X)
      G   GAUSS      Calculate PDF (X) and CDF (Y) at value X
      g   FACTORIAL  Calculate factorial of X
      d   DEG/RAD    Toggle between degree or radian base (for trigonometrical functions)
      I   COMB       Combinations (sets) of n (Y) items taken r (X) at a time (nCr)
      J   PERM       Permutations (arrangements) of n (Y) items taken r (X) at a time (nPr)
      h   HMS2H      Convert time h.mmss to h
      H   H2HMS      Convert time h to h.mmss
      y   R2P        Convert rectangular xy coordinates (XY) to polar rp coordinates (XY)
      Y   P2R        Convert polar rp coordinates (XY) to rectangular xy coordinates (XY)
      %   SOLVE      Find zero-root of function programmed in program-slot 0 (with starting value X)
      |   INTEGRATE  Calculate integral (from Y to X) of function programmed in program-slot 0
    Statistics and Linear Regression:
      q   CLRSUM     Reset all statistical/regressional registers and variables
      u/U SUM+/SUM-  Add/reduce x(y)-values for statistical/regressional calculations
      j   MEAN       Calculate mean value (X) and standard deviation (Y)
      W   PREDICT    Predict x (X) and y (Y) of linear regression (y=ax+b with a=Y(1)-Y(0), b=Y(0))
    Physical Constants:
      $   CONST      Choose out of 62 physical constants
    IO-Functions:
      [   SAVE       Save program in program-slot Y to EEPROM-slot X
      ]   LOAD       Load EEPROM-slot Y to program-slot Y
      {   EXPORT
      }   IMPORT
    Programming:
      @   PRG        Edit program in program-slot X (SHIFT to delete and ENTER to insert step)
      !   RUN        Run program in program-slot X
      :   STOP       Stop execution of program
      &   LABEL      Program label (labeled in next step with any character)
      >   GOTO       Go to label (labeled in next step with any character)
      ?   IF         If X(GT|LT|GE|LE|EQ|NE)Y is false - skip next two program steps
      =   CASE       (CASEabcd11223344) Print selection text "a b c d" and execute 11, 22, 33 or 44
      "   PRINT
      '   PRINTX     Print X to display

  //#define '('
  //#define ')'
  //#define ','
  //#define ';'
  //#define '<'
  //#define 'D'
  //#define 'F'
  //#define 'K'
  //#define 'P'
  //#define 'Z'
  //#define '\\' do not use
  //#define '_'
  //#define '`'
  //#define 'e'
  //#define 'k'
  //#define 'w'
  //#define '~'




  Todo:
  Export Import (to prgslot)
  multisave first y prgslots to eeslot x
  case print 4 chars goto 4 levels
  gosub return
  change %
  matrix inv 2x2 3x3
  complex calculating


  Export program from program-slot X to (Linux-)PC:
  1 Start export on bytelab with: Export
  2 In the next 3 seconds start this command on your PC:
    (stty raw; cat > prg.txt) < /dev/serial_port
  3 If scarlet says "done" stop dumping to your PC with "ctl-c"
  4 Go on with bytelab with pressing any key
  5 The EEPROM-content is on your PC on file "prg.txt"

  Append a zero character to a file in linux with "dd if=/dev/zero bs=1 count=1 >> file".

    delay(3000);
    for (int i = 0; i <= EEPROMMAX; i++) Serial.write(EEPROM.read(i));
    waitforkeypress();

  void waitforkeypress() {
  byte kee = NULLCHAR;
  for (;;) {
    if (Serial.available() > 0) kee = (Serial.read());
    if (kee != NULLCHAR) break;
  }
  }



  Import content from (Linux-)PC to EEPROM:
  1 Start import on bytelab with: in
  2 Start sending file on the PC with:
    cat serial.dmp > /dev/serial_port
  3 Wait for OK message on bytelab

    while (Serial.available() <= 0) ;
    for (int i = 0; i <= EEPROMMAX; i++) EEPROM.write(i, Serial.read());
    message(MSGOK);


  ScArY is a scientific calculator based on an ATTINY85 microcontroller and a
  QYF-TM1638-board (8 digit LED display with 16 buttons controlled with 3 pins).

  ScArY is capable of familiar functions of RPN calculators (ie stack operations)
  and many mathematical operations (ie trigonometic) as well as some special functions
  like calculating annuities or gaussian distributions.

  Due to the memory restrictions of the ATTINY85 (8 kilobytes) some compromises were
  made to offer so many functions. So the numbers are shown in SCI notation only (see below).
  Another compromise is the lack of checking for errors - usually there is no readable display
  if an error occurs.


  KEYBOARD LAYOUT:

     f[] [zZZ]           7 [MENU]    8 [SWAP]        9 [/]
      EE [ROT-] (UP)     4 [PI]      5 [SQRT]        6 [*]
     CHS [ROT+] (DOWN)   1 [STO]     2 [RCL]         3 [-]
       c [brightness]    0 [SHUOW]   . [LASTx]   ENTER [+]


  MENU (f[7]):
       P (POW)    r (1/x)     E (EXP)     L  (LN)
                  S (SIN)     c (COS)     t  (TAN)
       =          S (ASIN)    c (ACOS)    t  (ATAN)
       H          S (SINH)    c (COSH)    t  (TANH)
       H=         S (ASINH)   c (ACOSH)   t  (ATANH)
       A (ANNU)   G (GAUSS)   F (FACT)    dr (DEG/RAD)


  8-DIGITS SCIENTIFIC DISPLAY (SCI notation):

       mantissa  exponent
       |         |
     - m.m m m - e e
     |         |
     sign      EE-sign


  ENTERING NUMBERS:
    1.) Enter mantissa (with '.' if applicabel)
    2.) If applicable: Enter EE to enter exponent (limited to 29)
    3.) If applicable: Toggle sign of exponent with EE
    4.) If applicable: Toggle sign of number with CHS


  COMMANDS and KEYS:
    Basic keys:
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ., EE, CHS, ENTER, C/CE, f
    f-keys:
      +, -, *, / (basic operations)
      STO, RCL, SHOW, SWAP, LASTx, ROT+, ROT-, SQRT, P
      MENU (browse menu)
      BRIGHTNESS (set brightness of display)
      zZZ (toggle screensaver)
    MENU-functions:
      POWER, 1/X, EXP, LN
      SIN, COS, TAN, ASIN, ACOS, ATAN
      SINH, COSH, TANH, ASINH, ACOSH, ATANH
      ANNU (present value for a given interest rate and duration)
      GAUSS (density and distribution)
      FACT, DEG, RAD


  TODOs:
      sleep mode
      add constants (41 items like HP35s)
      add further functions:
      - clock, SQR,xSQRTy, FACT, LOG, 10x, Py,x, Cy,x,
      - statistics, Linear regression,
      - ->P (convert to polar and ...), ->R (... rectangular coordinates)
      - ->H.MS (convert hours to hours, minutes, seconds ...), ->H (... and back)
      - ->RAD (convert degrees to radians), ->DEG (and back)

*/


// DEFINES & INCLUDES

#include "scarlet.h"

#define WRITETOEEPROM 0 // Write CONST to EEPROM if 1
#include <EEPROM.h>

#define _abs(x) ((x<0)?(-x):(x)) // abs()-substitute macro

// Pin assignment
#define STROBE 11 // Strobe pin // Arduino/Genuino Micro
#define CLOCK  6 // Clock pin
#define DATA   3 // Data pin
//#define DATA   2 // 5 green    // ATTINY85
//#define CLOCK  1 // 6 yellow   // HW-pins: 8 7 6 5  SW-pins: 3 2 1 0
//#define STROBE 0 // 7 orange   //          1 2 3 4           4 5 6 7

// Commands for QYF-TM1638-board
#define PRINTCMD 0x40 // Command code for display printing
#define READCMD  0x42 // Command code for key reading

// Constants
#define DIGITS            8 // Number of digits
#define SEGMENTS          8 // Number of segments per digit
#define KEYS             16 // Number of keys
#define SMALLNUMBER    1e-8 // Smallest number before SCI
#define BIGNUMBER       1e8 // Biggest number before SCI
#define TINYNUMBER     1e-7 // Number for rounding to 0
#define MAXFIXPOSEE 4
#define MAXFIXNEGEE 3
#define FIX               3 // Display 3 decimals
#define FIXMANT           3 // FIX in 10th-exponent
#define MANTDIGITS        4 // Digits of mantissa in exponential expression
#define DOTEE             1 // Place of dot in exponential expression
#define FIXSHOW           6 // FIX for SHOW
#define FIXMANTSHOW       6 // FIX in 10th-exponent
#define BRIGHTMAX         7 // Maximal value for brightness
#define MAXITERATE      100 // Maximal number of Taylor series loops to iterate
#define MENUKEYS          4 // Menu keys (ABCD)
#define MAXMENU          11 // Number of MENUs (including 0)
#define MAXCONST         61 // Number of CONSTants (including 0)
#define NUMBEROFF        15 // Number of casted f-keys
#define DEFAULTFIX        4 // Default FIX
#define MSGTIME         750 // Message display time in ms
#define MAXSTO            9 // Maximal number of storages (including 0)

#define EEADDRCONST 2125 // Starting EEPROM address of CONST (42 consts possible)
#define EEADDRPRG      0 // Starting EEPROM address of programs (16x128=2048)


// SUBPROGRAMS

void reset() { // Reset shield (write NULL to 16 addresses)
  cmd(PRINTCMD); // Auto increment mode
  digitalWrite(STROBE, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, 0xc0); // Start address = 0
  for (byte i = 0; i < 16; i++) shiftOut(DATA, CLOCK, LSBFIRST, 0x00);
  digitalWrite(STROBE, HIGH);
}

void cmd(byte val) { // Send command to shield
  digitalWrite(STROBE, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, val);
  digitalWrite(STROBE, HIGH);
}

unsigned int getbuttons() { // Get button code (only one key at a time) - 16 bits
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

byte buttoncast() { // Get button pattern and return keycode
  const unsigned int _k[KEYS] = { // Indexing keyboard codes
    _K1, _K2,  _K3,  _K4,  _K5,  _K6,  _K7,  _K8,
    _K9, _K10, _K11, _K12, _K13, _K14, _K15, _K16
  };
  const byte _kc[KEYS] = { // Indexing keycodes
    _KC1, _KC2,  _KC3,  _KC4,  _KC5,  _KC6,  _KC7,  _KC8,
    _KC9, _KC10, _KC11, _KC12, _KC13, _KC14, _KC15, _KC16
  };
  for (byte i = 0; i < KEYS; i++) if (getbuttons() & _k[i]) return (_kc[i]); // Casting
}

byte getkey() { // Get one debounced key
  /*byte key = NULL;
    if (Serial.available()) {
    key = Serial.read();
    if (key == '6') return (_KC1);
    else if (key == '7') return (_KC2);
    else if (key == '8') return (_KC3);
    else if (key == '9') return (_KC4);
    else if (key == 'z') return (_KC5);
    else if (key == 'u') return (_KC6);
    else if (key == 'i') return (_KC7);
    else if (key == 'o') return (_KC8);
    else if (key == 'h') return (_KC9);
    else if (key == 'j') return (_KC10);
    else if (key == 'k') return (_KC11);
    else if (key == 'l') return (_KC12);
    else if (key == 'n') return (_KC13);
    else if (key == 'm') return (_KC14);
    else if (key == ',') return (_KC15);
    else if (key == '.') return (_KC16);
    }
    else return (NULL);*/
  /**/
  static byte oldkey = 0; // Needed for debouncing
  byte key1 = buttoncast(), key2 = 0;
  if (key1 != oldkey) key2 = buttoncast();
  if (key1 == key2) {
    oldkey = key1;
    return (key1);
  }
  return (NULL);
  /**/
}

void waitforkeypress() {
  while (getkey() == NULL);
  //for (;;) if (getkey() != NULL) break;
}

/*byte index(byte sign) {
  //if (sign > 127) sign -= 127;
  for (byte j = 0; j < 96; j++)
    if (letter[j] == sign) return (j);
  return (NULL);
  }*/

void printbuf(byte *buf) { // Write buffer and dot to display
  byte dbuf[DIGITS] = {_7DIGIT1, _7DIGIT2, _7DIGIT3, _7DIGIT4, _7DIGIT5, _7DIGIT6, _7DIGIT7, _7DIGIT8,};
  char string[20];
  /*string[0] = '\0';
    for (byte i = 0; i < DIGITS; i++) {
    if (buf[i] <= 127) {
      strcat(string, " ");
      string[strlen(string) - 1] = index(buf[i]) + ' ';
    }
    else {
      strcat(string, " ");
      string[strlen(string) - 1] = index(buf[i] & 0x7f) + ' ';
      strcat(string, " ");
      string[strlen(string) - 1] = '.';
    }
    }
    Serial.println(string);*/
  /**/
  byte digbuf;
  //if (dotpos > 0 && dotpos <= DIGITS) // Set dot
  //  buf[dotpos - 1] = buf[dotpos - 1] | _7FULLSTOP;

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
  /**/
}

void printfloat(double f) { // Prints float variable
  const byte digits[] = { // Character set to display numbers
    _7DIGIT0, _7DIGIT1, _7DIGIT2, _7DIGIT3, _7DIGIT4,
    _7DIGIT5, _7DIGIT6, _7DIGIT7, _7DIGIT8, _7DIGIT9
  };
  byte dispbuf[DIGITS] = {0, 0, 0, 0, 0, 0, 0, 0}; // Display buffer
  long m; // Mantissa
  int8_t e; // Exponent
  if (f < 0.0) {
    f = - f;
    dispbuf[0] = _7MINUS;
  }
  e = log10(f); // Exponent
  m = (f / _pow10(e - FIX)) + .5; // Mantissa
  if (m > 0 && m < _pow10(FIXMANT)) { // Change (n-1)-digit-mantissa to n digits
    e -= 1;
    m = (f / _pow10(e - FIX)) + .5; // "New" mantissa
  }
  for (byte i = MANTDIGITS; i > 0; i--) { // Print mantissa
    dispbuf[i] = digits[m % 10];
    m /= 10;
  }
  if (e < 0) { // Negative exponent
    dispbuf[5] = _7MINUS;
    e = -e;
  }
  if (e < 10) { // Print exponent
    dispbuf[6] = _7DIGIT0;
    dispbuf[7] = digits[e];
  }
  else {
    dispbuf[6] = digits[(e / 10) % 10];
    dispbuf[7] = digits[e % 10];
  }
  dispbuf[DOTEE] |= _7FULLSTOP;
  printbuf(dispbuf); // Write buffer and dot to display
}

void printnumber(double f) {
  const byte digits[] = { // Character set to display numbers
    _7DIGIT0, _7DIGIT1, _7DIGIT2, _7DIGIT3, _7DIGIT4,
    _7DIGIT5, _7DIGIT6, _7DIGIT7, _7DIGIT8, _7DIGIT9
  };
  long m; // Mantissa
  int8_t e; // Exponent
  byte dispbuf[DIGITS] = {0, 0, 0, 0, 0, 0, 0, 0}; // Display buffer
  if (f == 0.0) {                                   // E x a c t l y   z e r o
    dispbuf[0] = _7DIGIT0 | _7FULLSTOP;
    for (byte i = 1; i < DIGITS; i++) dispbuf[i] = _7DIGIT0;
    //for (byte i = 0; i < fix && i < DIGITS; i++) dispbuf[i + 1] = _7DIGIT0;
    printbuf(dispbuf); // Write buffer and dot to display
  }
  else if (f >= 0) {                                // P o s i t i v e   N u m b e r
    if (f >= BIGNUMBER || f <= SMALLNUMBER * _pow10(DEFAULTFIX)) { // BIG or TINY
      printfloat(f);
    }
    else { // NORMAL
      if (f >= 1) {
        e = log10(f); // Exponent
        m = f * _pow10(min(DIGITS - e - 1, DIGITS)) + .5; // Mantissa
        for (byte i = min(DIGITS, e + 1 + DIGITS) ; i > 0; i--) { // Print mantissa
          dispbuf[i - 1] = digits[m % 10];
          m /= 10;
        }
        dispbuf[e] |= _7FULLSTOP;
      }
      else {
        m = f * _pow10(DIGITS - 1) + .5; // Mantissa
        for (byte i = DIGITS; i > 0; i--) { // Print mantissa
          dispbuf[i - 1] = digits[m % 10];
          m /= 10;
        }
        dispbuf[0] |= _7FULLSTOP;
      }
      printbuf(dispbuf); // Write buffer and dot to display
    }
  }
  else {                                           // N e g a t i v e   N u m b e r
    if (f <= -BIGNUMBER / 10 || f >= -SMALLNUMBER * _pow10(DEFAULTFIX + 1)) { // BIG or TINY
      printfloat(f);
    }
    else { // NORMAL
      if (f < -1) {
        dispbuf[e] = _7MINUS;
        e = log10(-f); // Exponent
        m = -f * _pow10(min(DIGITS - e - 2, DIGITS)) + .5; // Mantissa
        for (byte i = min(DIGITS - 1, e + 1 + DIGITS) ; i > 0; i--) { // Print mantissa
          dispbuf[i] = digits[m % 10];
          m /= 10;
        }
        dispbuf[e + 1] |= _7FULLSTOP;
        printbuf(dispbuf); // Write buffer and dot to display
      }
      else {
        m = -f * _pow10(DIGITS - 2) + .5; // Mantissa
        for (byte i = DIGITS; i > 0; i--) { // Print mantissa
          dispbuf[i - 1] = digits[m % 10];
          m /= 10;
        }
        dispbuf[0] = _7MINUS;
        dispbuf[1] |= _7FULLSTOP;
        printbuf(dispbuf); // Write buffer and dot to display
      }
    }
  }
}

byte fcast(byte k) { // Returns f-key code
  const byte _f_old[] = {_KC2,       _KC3,  _KC4,              // f-cast from
                         _KC5,       _KC6,  _KC7,   _KC8,
                         _KC9,       _KC10, _KC11,  _KC12,
                         _KC13,      _KC14, _KC15,  _KC16
                        };
  const byte _f_new[] = {MENU,       CONST, DIVIDE,            // to
                         SUM,      PRG,   RUN,    MULTIPLY,
                         ROTDOWN,    STO,   RCL,    SUBSTRACT,
                         BRIGHTNESS, SWAP,  LASTX,  ADD
                        };
  for (byte i = 0; i < NUMBEROFF; i++) if (k == _f_old[i]) return (_f_new[i]);
  return (NULL);
}

void message(byte nr) { // Displays message
  printbuf(_message[nr]);
  delay(MSGTIME);
}


void push(double * a, double * b, double * c, double * d) { // Push stack
  *d = *c; *c = *b; *b = *a;
}

void pull(double * a, double * b, double * c, double * d, boolean isfull) { // Pull stack
  if (isfull) *a = *b;
  *b = *c; *c = *d;
}

double _pow10(int8_t e) { // Returns 10^e
  boolean ne = (e < 0);
  double f = 1.0;
  for (byte i = _abs(e); i > 0; i--)  f *= 10;
  if (ne) f = 1 / f;
  return (f);
}

double _exp_sin(double f, boolean isexp) { // Calculate exp with Taylor series
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

double hmstoh(double hms) { // hms->h
  //  return((int)hms+((int)(100*(hms-(int)hms)))/60.0+(100*(100*hms-(int)(100*hms)))/3600.0);
  unsigned long T = (hms + 0.000005) * 100000;
  int hh = (int)(T / 100000), mm = (int)(T / 1000) - hh * 100, ss = T / 10 - hh * 10000 - mm * 100, t = T - hh * 100000 - mm * 1000 - ss * 10;
  return (hh + mm / 60.0 + ss / 3600.0 + t / 36000.0);
}

double htohms(double h) { // h->hms
  h += 0.000005;
  return ((int)h + ((int)(60 * (h - (int)h))) / 100.0 + (60 * ((60 * (h - (int)h)) - (int)(60 * (h - (int)h)))) / 10000.0);
}


//#if WRITETOEEPROM


void writeeeprom() { // Write content to EEPROM (messages, const)
  int addr = EEADDRCONST;
  for (byte k = 0; k <= MAXCONST; k++) {
    for (byte i = 0; i < CDIGITS; i++) EEPROM.write(addr++, _consttxt[k][i]); // Write name
    EEPROM.put(addr, (double)_const[k]); // Write number
    addr += sizeof(const double);
  }
}

//#endif


// SETUP and LOOP

void setup() {
  pinMode(STROBE, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  cmd(0x88); // Activate and brightness "1000 abbb" (a=1)
  //reset();
  //printbuf("@vy88?@", 0); // Welcome message -HELLO-
  printbuf("mXwP8yx"); // Welcome message ScArLEt
  //printfloat(0.0,false); // No welcome message
#if WRITETOEEPROM
  writeeeprom(); // Write messages, menus and constants to EEPROM - only one time needed!
#endif
}

void loop() {
  byte key = NULL;
  static double x = 0.0, y = 0.0, z = 0.0, u = 0.0, lastx = 0.0; // Stack
  static double mem[MAXSTO]; // Memory
  static double rad = 180.0 / PI; // Multiplier for radiants
  static boolean isnewnumber = false; // True if stack has to be lifted before entering a new number
  static boolean ispushed = false; // True if stack was already pushed by ENTER
  static boolean isfpressed = false; // Function key pressed
  static boolean isee = false; // True if EE was pressed and exponent will be entered
  static boolean isenteringnumber = true; // Used to differ clear and clear-entry
  static boolean isdot = false; // True if dot was pressed and decimals will be entered
  static byte decimals = 0; // Number of decimals entered - used for input after decimal dot
  static boolean ismenu = false; // True, if MENU was demanded
  static int8_t ee = 0; // EExponent
  static boolean isprintmenu = true; // True if MENU/CONST should be printed
  static byte selectnr = 0; // Number of selected menu/const item
  static byte brightness = 0; // Value for brightness (0...8)
  static boolean isdisplaydeactivated = false; // True if screensaver is on
  static boolean isselectconst = false; // True if CONST browsing is demanded

#define MAXPRGSLOTS    4 // Maximal number of programs in memory
#define MAXEEPRGSLOTS 20 // Maximal number of programs in EEPROM
#define MAXPRGSIZE   100 // Maximal size of program
#define PRGHEADERSIZE  1 // Number of first characters for name of program
#define PRGCMDPOS      4 // Display position of command
  static boolean isrun = false; // Execute program
  static byte pointer = PRGHEADERSIZE;
  static byte prgnr = 0;
  static char prg[MAXPRGSLOTS][MAXPRGSIZE] = {"F *2-", "C&S=abcd>A>B>C>D>S&A1+:&B2+:&C3+:&D4+:", "S1+:1+", "I?LT1234"};
  static boolean isprg = false; // Edit program
  static boolean isprintprg = false; // True, if PRG-step should be printed
  static byte maxstepnr = 0;
  static boolean isentercmd = false; // True, if command should be entered
  static boolean isprintcmd = false; // True, if command should be printed
  static byte selectcmd = 0; // Number of command to be selected

  static byte calcstep = 0; // Calculating steps of solver/integrator
  static double xsolve1 = 0.0, ysolve1 = 0.0, xsolve2 = 0.0, ysolve2 = 0.0; // Solve/Int variables
#define DELTA 1E-4 // Delta for solver
  static boolean issolve = false; // Solver activated
#define STRIPES 10 // Number of stripes for integrating
  static double width = 0.0, integral = 0.0; // Integration stripe width and area
  static boolean isintegrate = false; // Integration activated

  static double sx = 0.0, sxx = 0.0, sy = 0.0, sxy = 0.0; // Statistical/LR variables
  static byte sn = 0;

  const byte _msgs[][DIGITS] = {
    {_7LETTERE, 0, _7LETTERS, 0, _7LETTERP, 0, _7LETTERr, 0},         // exp_sqrt_pow_inv
    {_7LETTERL, 0, _7LETTERF, 0, 0, 0, _7LETTERP, _7LETTERI},         // ln_!_0_pi
    {_7LETTERC, 0, _7LETTERP, 0, 0, 0, 0, 0},                         // C_P__
    {_7MINUS, _7LETTERh, _7LETTERh, _7MINUS, _7MINUS, _7LETTERP, _7MINUS, _7LETTERr}, // h2hms_hms2h_r2p_p2r
    {_7LETTERA, 0, _7LETTERG, 0, _7LETTERF, 0, _7LETTERd, _7LETTERr}, // annu_gauss_fix_deg/rad
    {0, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0},                 // _sin_cos_tan
    {_7TILDE, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0},           // _asin_acos_atan
    {_7LETTERh, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0},         // _sinh_cosh_tanh
    {_7LETTERh, _7TILDE, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0},   // _asinh_acosh_atanh
    {_7MINUS, 0, _7TILDE, 0, _7LETTERC, 0, _7LETTERP, _7LETTERr},     // SUM-_^x_CLR
    {_7LETTERS, 0, _7LETTERI, 0, 0, 0, 0, 0},                         // solve_integrate__
    {_7LETTERS, 0, _7LETTERL, 0, _7LETTERE, 0, _7LETTERI, 0},         // save_load_export_import
  };
  const byte _menuchar[][4] = { // Menu keycodes
    {EXP, SQRT, POW, INV},        // exp_sqrt_pow_inv
    {LN, FACT, 0, PEE},           // ln_!_0_pi
    {COMB, PERM, 0, 0},           // C_P__
    {HMS2H, H2HMS, R2P, P2R},     // h2hms_hms2h_r2p_p2r
    {ANNU, GAUSS, FIX, DEGRAD},   // annu_gauss_fix_deg/rad
    {0, SIN, COS, TAN},           // _sin_cos_tan
    {0, ASIN, ACOS, ATAN},        // _asin_acos_atan
    {0, SINH, COSH, TANH},        // _sinh_cosh_tanh
    {0, ASINH, ACOSH, ATANH},     // _asinh_acosh_atanh
    {SUMc, MEAN, CLRSUM, PREDICT},// SUM-_^x_CLR
    {SOLVE, INTEGRATE, 0, 0},     // solve_integrate__
    {SAVE, LOAD, EXPORT, IMPORT}, // save_load_export_import
  };

  key = getkey(); // Read character

  if (issolve) { // *** SOLVER ***
    if (!isrun) { // prg[0] finished
      if (calcstep == 0) {
        ysolve1 = x;
        x = xsolve2 = xsolve1 + DELTA;
        calcstep++;
        pointer = PRGHEADERSIZE;
        isrun = true;
      }
      else if (calcstep == 1) {
        ysolve2 = x;
        xsolve2 = xsolve1;
        x = xsolve1 = xsolve1 - ysolve1 * DELTA / (ysolve2 - ysolve1);
        calcstep = 0;
        if (abs(xsolve1 - xsolve2) < DELTA) { // Solver end
          message(MSGOK);
          printnumber(x);
          issolve = false;
          key = NULL;
        }
        else { // Next run
          isrun = true;
          pointer = PRGHEADERSIZE;
        }
      }
    }
  }
  else if (isintegrate) { // *** INTEGRATION ***
    if (!isrun) { // prg[0] finished
      if (calcstep == 0) {
        ysolve1 = x;
        x = xsolve1 = xsolve1 + width;
        calcstep++;
        pointer = PRGHEADERSIZE;
        isrun = true;
      }
      else if (calcstep == 1) {
        ysolve2 = x;
        x = xsolve1 = xsolve1 + width;
        calcstep++;
        pointer = PRGHEADERSIZE;
        isrun = true;
      }
      else if (calcstep == 2) {
        integral += (ysolve1 + 4 * ysolve2 + x) * width / 3;
        calcstep = 0;
        if (xsolve1 >= xsolve2) { // Solver end
          x = integral;
          message(MSGOK);
          printnumber(x);
          isintegrate = false;
          key = NULL;
        }
        else { // Next run
          x = xsolve1;
          isrun = true;
          pointer = PRGHEADERSIZE;
        }
      }
    }
  }

  if (isrun) { // *** EXECUTE PROGRAM ***
    Serial.print("ptr="); Serial.println(pointer);
    if (key == CLX) {
      message(MSGSTOP);
      isrun = false;
      issolve = false;
    }
    else if (prg[prgnr][pointer] == LABEL) { // Treat LABEL
      pointer += 2;
    }
    else if (prg[prgnr][pointer] == GOTO) { // Treat GOTO
      for (byte i = 0; i < strlen(prg[prgnr]) - 1 && i <= MAXPRGSIZE; i++) {
        if (prg[prgnr][i] == LABEL && prg[prgnr][i + 1] == prg[prgnr][pointer + 1]) { // Label found
          pointer = i + 2;
          break;
        }
      }
    }
    else if (prg[prgnr][pointer] == IF) { // Treat IF
      byte first = prg[prgnr][pointer + 1], second = prg[prgnr][pointer + 2];
      pointer += 5;
      if (first == 'G' && second == 'T') {      // GT
        if (x > y) pointer -= 2;
      }
      else if (first == 'L' && second == 'T') { // LT
        if (x < y) pointer -= 2;
      }
      else if (first == 'G' && second == 'E') { // GE
        if (x >= y) pointer -= 2;
      }
      else if (first == 'L' && second == 'E') { // LE
        if (x <= y) pointer -= 2;
      }
      else if (first == 'E' && second == 'Q') { // EQ
        if (x == y) pointer -= 2;
      }
      else if (first == 'N' && second == 'E') { // NE
        if (x != y) pointer -= 2;
      }
    }
    else if (prg[prgnr][pointer] == CASE) { // Treat CASE selection
      byte dispbuf[DIGITS] = {0, 0, 0, 0, 0, 0, 0, 0}; // Display buffer
      for (byte i = 0; i < 4; i++)
        dispbuf[i * 2] = letter[prg[prgnr][pointer + i + 1] - ' '];
      printbuf(dispbuf); // Write buffer to display
      for (;;) {
        key = NULL;
        key = getkey(); // Read character
        if (key == CLX) {
          key = STOP;
          break;
        }
        else if (key == SHIFT) {
          pointer += 5;
          key = NULL;
          break;
        }
        else if (key == DIGIT7) {
          pointer += 7;
          key = NULL;
          break;
        }
        else if (key == DIGIT8) {
          pointer += 9;
          key = NULL;
          break;
        }
        else if (key == DIGIT9) {
          pointer += 11;
          key = NULL;
          break;
        }
      }
    }
    else { // Execute key or end program
      key = prg[prgnr][pointer++];
      if (prg[prgnr][pointer] == NULL || pointer >= MAXPRGSIZE) {
        isrun = false;
      }
    }
  }
  else if (isentercmd) { // *** SELECT COMMAND ***
    if (isprintcmd) {
      byte dispbuf[DIGITS] = {0, 0, 0, 0, 0, 0, 0, 0}; // Display buffer
      dispbuf[1] = letter[((int)(selectcmd / 10)) % 10 + '0' - ' '];
      dispbuf[2] = letter[selectcmd % 10 + '0' - ' '];
      dispbuf[3] = letter[selectcmd];
      for (byte i = 0; i < strlen(command[selectcmd]); i++)
        dispbuf[i + 4] = letter[command[selectcmd][i] - ' '];
      printbuf(dispbuf); // Write buffer to display
      isprintcmd = false;
    }
    if (key == EE) { // Previous menu entry
      if (selectcmd > 0) selectcmd--;
      else selectcmd = NROFCMDS;
      isprintcmd = true;
    }
    else if (key == CHS) { // Next menu entry
      if (selectcmd < NROFCMDS) selectcmd++;
      else selectcmd = 0;
      isprintcmd = true;
    }
    else if (key == CLX) { // Exit menu
      //printnumber(x);
      isprintprg = true;
      isentercmd = false;
    }
    else if (key == ENTER) { // Enter - insert command
      strcat(prg[prgnr], " ");
      for (byte i = strlen(prg[prgnr]) - 1; i > selectnr + 1 ; i--)
        prg[prgnr][i] = prg[prgnr][i - 1];
      prg[prgnr][selectnr + 1] = selectcmd + ' ';
      selectnr++;
      maxstepnr++;
      isprintprg = true;
      isentercmd = false;
    }
    if (key >= DIGIT0 && key <= DIGIT9) { // Enter command code manually
      if ((selectcmd % 10 * 10 + key - '0') <= NROFCMDS)
        selectcmd = selectcmd % 10 * 10 + key - '0';
      else selectcmd = key - '0';
      isprintcmd = true;
    }
    key = NULL;
  }
  else if (isprg) { // *** EDIT PROGRAM ***
    if (isprintprg) {
      byte dispbuf[DIGITS] = {0, 0, 0, 0, 0, 0, 0, 0}; // Display buffer
      Serial.print("selnr="); Serial.println(selectnr);
      dispbuf[0] = letter[prgnr + '0' - ' '];
      dispbuf[1] = letter[((int)(selectnr / 10)) % 10 + '0' - ' '];
      dispbuf[2] = letter[selectnr % 10 + '0' - ' '];
      dispbuf[3] = letter[prg[prgnr][selectnr] - ' '];
      if (selectnr >= PRGHEADERSIZE)
        for (byte i = 0; i < strlen(command[prg[prgnr][selectnr] - ' ']); i++)
          dispbuf[i + PRGCMDPOS] = letter[command[prg[prgnr][selectnr] - ' '][i] - ' '];
      printbuf(dispbuf); // Write buffer to display
      isprintprg = false;
    }
    if (key == EE) { // Previous menu entry
      if (selectnr > 0) selectnr--;
      else selectnr = maxstepnr;
      isprintprg = true;
    }
    else if (key == CHS) { // Next menu entry
      if (selectnr < maxstepnr) selectnr++;
      else selectnr = 0;
      isprintprg = true;
    }
    else if (key == CLX) { // Exit menu
      printnumber(x);
      isprg = false;
    }
    else if (key == ENTER) { // Enter - insert command after this step
      message(MSGINS);
      isprintcmd = true;
      isentercmd = true;
    }
    if (key >= DIGIT0 && key <= DIGIT9) { // Enter program step manually
      if ((selectnr % 10 * 10 + key - '0') <= maxstepnr)
        selectnr = selectnr % 10 * 10 + key - '0';
      else selectnr = key - '0';
      isprintprg = true;
    }
    else if (key == SHIFT) { // Delete this step
      if (maxstepnr > 0) { // Not possible to delte 1-step-program
        for (byte i = selectnr; i < maxstepnr; i++) prg[prgnr][i] = prg[prgnr][i + 1];
        prg[prgnr][maxstepnr] = NULL;
        maxstepnr--;
        selectnr--;
        if (selectnr >= maxstepnr) selectnr = maxstepnr;
        isprintprg = true;
      }
    }
    key = NULL;
  }

  if (isselectconst) { // *** SELECTING CONST ***
    byte dispbuf[DIGITS] = {0, 0, 0, 0, 0, 0, 0, 0};
    if (isprintmenu) {
      dispbuf[0] = letter[((int)(selectnr / 10)) % 10 + '0' - ' '];
      dispbuf[1] = letter[selectnr % 10 + '0' - ' '];
      for (byte i = 0; i < CDIGITS; i++)
        dispbuf[i + 5] = EEPROM.read(EEADDRCONST + selectnr * (CDIGITS + sizeof(const double)) + i);
      printbuf(dispbuf);
      isprintmenu = false;
    }
    if (key == EE) { // Previous menu entry
      if (selectnr > 0) selectnr--;
      else selectnr = MAXCONST;
      isprintmenu = true;
    }
    else if (key == CHS) { // Next menu entry
      if (selectnr < MAXCONST) selectnr++;
      else selectnr = 0;
      isprintmenu = true;
    }
    else if (key == CLX) { // Exit menu
      printnumber(x);
      //ismenu = false;
      isselectconst = false;
    }
    else if (key == ENTER) { // Enter - choose const
      push(&x, &y, &z, &u);
      //x = _const[selectnr];
      EEPROM.get(EEADDRCONST + selectnr * (CDIGITS + sizeof(const double)) + CDIGITS, x);
      printnumber(x);
      isselectconst = false;
      isnewnumber = true;
    }
    else if (key >= DIGIT0 && key <= DIGIT9) { // Enter constant number manually
      if ((selectnr % 10 * 10 + key - '0') <= MAXCONST)
        selectnr = selectnr % 10 * 10 + key - '0';
      else selectnr = key - '0';
      isprintmenu = true;
    }
    key = NULL;
  }
  else if (ismenu) { // *** SELECTING MENU ***
    byte dispbuf[DIGITS];
    if (isprintmenu) {
      for (byte i = 0; i < DIGITS; i++) dispbuf[i] = _msgs[selectnr][i];
      printbuf(dispbuf);
      isprintmenu = false;
    }
    if (key == EE) { // Previous menu entry
      if (selectnr > 0) selectnr--;
      else selectnr = MAXMENU;
      isprintmenu = true;
    }
    else if (key == CHS) { // Next menu entry
      if (selectnr < MAXMENU) selectnr++;
      else selectnr = 0;
      isprintmenu = true;
    }
    else if (key == CLX) { // Exit menu
      printnumber(x);
      ismenu = false;
      isselectconst = false;
    }
    else if (key == ENTER) { // Enter - choose const
      push(&x, &y, &z, &u);
      EEPROM.get(EEADDRCONST + selectnr * (DIGITS + sizeof(const double)) + DIGITS, x);
      printnumber(x);
      isselectconst = false;
      isnewnumber = true;
    }
    if (key == SHIFT || (key >= DIGIT7 && key <= DIGIT9)) { // Choose option
      if (key == SHIFT) key = DIGIT6;
      key = _menuchar[selectnr][key - DIGIT6];
      ismenu = false;
    }
    else key = NULL;
  }
  else if (key == SHIFT) { // *** TOGGLE SHIFT KEY ***
    //isfpressed =  isfpressed ?  false : true; // Toggle f-key
    if (isfpressed) {
      cmd(0x80); // Deactivate display - "1000 abbb" (a=0)
      isdisplaydeactivated = true;
      isfpressed = false;
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
  else if (key == DOT) { // *** ENTER DECIMALS DEMANDED ***
    if (!isfpressed) {
      if (isnewnumber) { // Enable starting new number with .
        if (ispushed) ispushed = false;
        else push(&x, &y, &z, &u);
        x = 0.0;
        decimals = 0;
        isnewnumber = false;
      }
      isdot = true;
      key = NULL;
    }
  }
  else if (key == EE && !isfpressed) { // *** ENTER EE INPUT DEMANDED ***
    if (isee && x > 0.0 && x != 1.0) { // Change sign of EE if EE is pressed the second time
      byte tmp = 0;
      if (x < 1.0 && log10(x) != (int)log10(x)) tmp = 1;
      x = x / _pow10(2 * ((int)log10(x) - tmp));
      printnumber(x);
    }
    isee = true;
    ee = 0;
    key = NULL;
  }

  if (key != NULL) { // *** TREAT KEY (if valid) ***
    if (isfpressed) { // Convert pressed key to f-key if function key f is active
      key = fcast(key);
      isfpressed = false;
    }
    else if (key == CLX && isenteringnumber) key = CE; // Cast c to C

    if ((key >= DIGIT0) && (key <= DIGIT9)) { // Numeric input
      if (isnewnumber) { // New number
        if (ispushed) ispushed = false;
        else push(&x, &y, &z, &u);
        x = isee ? 1.0 : 0.0; // Reset x (x=1 if EE-input follows)
        decimals = 0;
        isenteringnumber = true;
        isdot = false;
        isnewnumber = false;
      }
      if (isee) { // Entering EE (limit 29)
        if (ee % 10 < 3) ee = ee % 10 * 10 + key - '0';
        else ee = key - '0';
        x = x / _pow10(log10(x)) * _pow10(ee);
      }
      else { // Entering mantissa
        if (isdot) x += (key - '0') / _pow10(++decimals); // Append decimal to number
        else x = x * 10 + key - '0'; // Append digit to number
      }
    }
    else if (key == ENTER) { // ENTER
      push(&x, &y, &z, &u);
      ispushed = true;
      isnewnumber = true;
      isee = false;
      isenteringnumber = false;
    }
    else if (key == CLX) { // CLx - Clear x
      x = 0.0;
      isee = false;
    }
    else if (key == CE) { // CE - clear entry
      if (isdot) {
        if (x > TINYNUMBER && decimals > 0)
          x -= ((long)(x * _pow10(decimals)) % 10) / _pow10(decimals--);
        else isdot = false;
      }
      else x = (long)(x / 10.0);
    }
    else if (key == CHS) { // CHS
      x = -x;
      isnewnumber = true;
    }
    else if (key == MENU) { // Activate MENU
      selectnr = 0; // Comment if MENU should always start at first entry
      isprintmenu = true;
      ismenu = true;
    }
    else if (key == CONST) { // Activate CONST
      message(MSGCONST);
      selectnr = 0;
      isprintmenu = true;
      isselectconst = true;
    }
    else if (key == RUN) { // Execute program (RUN)
      message(MSGRUN);
      prgnr = (int)x;
      if (prgnr >= MAXPRGSLOTS) prgnr = 0;
      pull(&x, &y, &z, &u, true);
      isnewnumber = true;
      pointer = PRGHEADERSIZE;
      isrun = true;
    }
    else if (key == PRG) { // Edit program (PRG)
      message(MSGPRG);
      prgnr = (int)x;
      if (prgnr >= MAXPRGSLOTS) prgnr = 0;
      selectnr = 0;
      maxstepnr = strlen(prg[prgnr]) - 1;
      pull(&x, &y, &z, &u, true);
      isprintprg = true;
      isprg = true;
    }
    else if (key == SOLVE) { // Activate solver (SLV)
      xsolve1 = x;
      prgnr = 0;
      calcstep = 0;
      pointer = PRGHEADERSIZE;
      message(MSGRUN);
      issolve = true;
      isnewnumber = true;
      isrun = true;
    }
    else if (key == INTEGRATE) { // Activate integrator (INT)
      integral = 0.0;
      xsolve1 = y;
      xsolve2 = x;
      width = (x - y) / 2 / STRIPES;
      xsolve1 = x = y;
      prgnr = 0;
      calcstep = 0;
      pointer = PRGHEADERSIZE;
      message(MSGRUN);
      isintegrate = true;
      isnewnumber = true;
      isrun = true;
    }

    else { // OTHER COMMANDS - finally setting the ispushed false and isnewnumber true

      switch (key) {
        case ADD: // ADD
          lastx = x;
          x = x + y;
          pull(&x, &y, &z, &u, false);
          break;
        case SUBSTRACT: // SUBSTRACT
          lastx = x;
          x = y - x;
          pull(&x, &y, &z, &u, false);
          break;
        case MULTIPLY: // MULTIPLY
          lastx = x;
          x = x * y;
          pull(&x, &y, &z, &u, false);
          break;
        case DIVIDE: // DIVIDE
          lastx = x;
          x = y / x;
          pull(&x, &y, &z, &u, false);
          break;
        case BRIGHTNESS: { // Set brightness
            brightness = x > BRIGHTMAX ? BRIGHTMAX : (int)x;
            cmd(0x88 | brightness);
            //cmd(0x88 | (x > BRIGHTMAX ? BRIGHTMAX : (int)x));
            pull(&x, &y, &z, &u, true);
            break;
          }
        case STO: { // STO
            byte memnr = (int)abs(x);
            if (memnr <= MAXSTO) {
              mem[memnr] = y;
              pull(&x, &y, &z, &u, true);
            }
            break;
          }
        case RCL: { // RCL
            byte memnr = (int)abs(x);
            if (memnr <= MAXSTO) {
              x = mem[memnr];
            }
            break;
          }
        case SWAP: { // SWAP
            double tmp = x;
            x = y;
            y = tmp;
            break;
          }
        case LASTX: // LASTx
          push(&x, &y, &z, &u);
          x = lastx;
          break;
        case ROTDOWN: { // ROT down
            double tmp = x;
            pull(&x, &y, &z, &u, true);
            u = tmp;
            break;
          }
        case ROTUP: { // ROT up
            double tmp = u;
            push(&x, &y, &z, &u);
            x = tmp;
            break;
          }
        case SQRT: // SQRT
          x = sqrt(x);
          break;
        case EXP: // EXP              // Functions via menu
          x = _exp_sin(x, true);
          break;
        case LN: // LN
          x = log(x);
          break;
        case POW: // XpowerY
          x = _exp_sin(x * log(y), true);
          pull(&x, &y, &z, &u, false);
          break;
        case INV: // 1/x
          x = _exp_sin(-log(x), true);
          break;
        case PEE: // PI
          if (!ispushed) push(&x, &y, &z, &u);
          x = PI;
          break;
        case DEGRAD: // Toggle ->DEG ->RAD
          if (rad == 1.0) {
            rad = 180.0 / PI;
            message(MSGDEG);
          }
          else {
            rad = 1.0;
            message(MSGRAD);
          }
          break;
        case ANNU: // Annuity
          x = (1 - _exp_sin(-x * log(1 + y), true)) / y;
          pull(&x, &y, &z, &u, false);
          break;
        case SIN: case ASIN: case COS: case ACOS: case TAN: case ATAN: { // Trigonometric
            double si = _exp_sin(x / rad, false);
            double co = sqrt(1 - si * si);
            double as = atan(x / sqrt(1 - x * x));
            if (key == SIN) x = si;
            else if (key == ASIN) x = as * rad;
            else if (key == COS) x = co;
            else if (key == ACOS) x = (PI / 2 - as) * rad;
            else if (key == TAN) x = si / co;
            else if (key == ATAN) x = atan(x) * rad;
            break;
          }
        case SINH: case ASINH: case COSH: case ACOSH: case TANH: case ATANH: { // Hyperbolic
            double ep = _exp_sin(x, true);
            double em = _exp_sin(-x, true);
            double tmp = x * x + 1;
            if (key == SINH) x = (ep - em) / 2;
            else if (key == ASINH) x = log(x + sqrt(tmp));
            else if (key == COSH) x = (ep + em) / 2;
            else if (key == ACOSH) x = log(x + sqrt(tmp - 2));
            else if (key == TANH) x = (ep - em) / (ep + em);
            else if (key == ATANH) x = 0.5 * log((1 + x) / (1 - x));
            break;
          }
        case GAUSS: // GAUSS 322
          u = z;
          z = y;
          y = _exp_sin(- log(1 + _exp_sin(-0.07 * x * x * x - 1.6 * x, true)), true);
          x = _exp_sin(-0.5 * log(2 * PI) - x * x / 2, true);
          break;
        case FACT: { // Factorial !
            double tmp = 1.0;
            for (byte i = 1; i <= x; i++) tmp *= i;
            x = tmp;
            break;
          }
        case SUM: // SUM+
          sn++;
          sx += x;
          sy += y;
          sxx += x * x;
          sxy += x * y;
          push(&x, &y, &z, &u);
          lastx = x;
          x = sn;
          break;
        case SUMc: // SUM-
          sn--;
          sx -= x;
          sxx -= x * x;
          sy -= y;
          sxy -= x * y;
          push(&x, &y, &z, &u);
          lastx = x;
          x = sn;
          break;
        case MEAN: // MEAN, ST.DEV
          Serial.println("in MEAN");
          push(&x, &y, &z, &u);
          x = sqrt((sxx - sx * sx / sn) / (sn - 1));
          push(&x, &y, &z, &u);
          x = sx / sn;
          lastx = x;
          break;
        /*case LINREG: { // A+BX
            double tmp;
            push(&x, &y, &z, &u);
            lastx = x;
            x = tmp = (sxy / sn - sx / sn * sy / sn) / (sxx / sn - sx * sx / sn / sn);
            push(&x, &y, &z, &u);
            x = sy / sn - tmp * sx / sn;
          }
          break;*/
        case PREDICT: { // ->X,Y
            double tmp;
            push(&x, &y, &z, &u);
            tmp = (sxy / sn - sx / sn * sy / sn) / (sxx / sn - sx * sx / sn / sn);
            lastx = x;
            x = sy / sn - tmp * sx / sn + tmp * y; // ->y
            push(&x, &y, &z, &u);
            x = (z - sy / sn + tmp * sx / sn) / tmp; // ->x
            z = u;
          }
          break;
        case CLRSUM: // CLRSUM
          sn = sx = sxx = sy = sxy = 0.0;
          break;
        case COMB: { // COMB
            lastx = x;
            double tmp = x;
            x = 1.0;
            for (byte i = y - tmp + 1; i <= y; i++) x *= i;
            for (byte i = 1; i <= tmp; i++) x /= i;
            y = z;
            z = u;
          }
          break;
        case PERM: { // PERM
            lastx = x;
            double tmp = x;
            x = 1.0;
            for (byte i = y - tmp + 1; i <= y; i++) x *= i;
            y = z;
            z = u;
          }
          break;
        case HMS2H: // H.MS->H
          lastx = x;
          x = hmstoh(x);
          break;
        case H2HMS: // H->H.MS
          lastx = x;
          x = htohms(x);
          break;
        case R2P: { // R->P
            double tmp = y;
            y = atan(tmp / x) * rad;
            lastx = x;
            x = sqrt(x * x + tmp * tmp);
          }
          break;
        case P2R: { // P->R
            double si = _exp_sin(y / rad, false);
            y = x * si;
            lastx = x;
            x = x * sqrt(1 - si * si);
            break;
          }
          break;
        case SAVE: // Save MEM-Slot to EE-Slot
          for (byte i = 0; i < strlen(prg[(int)y]); i++) {
            EEPROM.write(EEADDRPRG + (int)x * MAXPRGSIZE + i, prg[(int)y][i]);
          }
          EEPROM.write(EEADDRPRG + (int)x * MAXPRGSIZE + strlen(prg[(int)y]), NULL);
          pull(&x, &y, &z, &u, true);
          pull(&x, &y, &z, &u, true);
          message(MSGOK);
          break;
        case LOAD: { // Load EE-Slot to MEM-Slot
            byte i = 0;
            prg[(int)x][0] = '\0';
            while (EEPROM.read(EEADDRPRG + (int)y * MAXPRGSIZE + i) != NULL) {
              strcat(prg[(int)x] , " ");
              prg[(int)x][strlen(prg[(int)x]) - 1] = EEPROM.read(EEADDRPRG + (int)y * MAXPRGSIZE + i);
              i++;
            }
            pull(&x, &y, &z, &u, true);
            pull(&x, &y, &z, &u, true);
            message(MSGOK);
          }
          break;
        case EXPORT: { // Export Program-Slot to serial
            message(MSGRUN);
            delay(3000);
            byte slot = (int)abs(x);
            if (slot <= MAXPRGSLOTS) {
              for (byte i = 0; i < strlen(prg[slot]); i++)
                Serial.write(prg[slot][i]);
              message(MSGOK);
              delay(3000);
            }
            key = NULL;
          }
          break;
        case IMPORT: { // Import serial to MEM-Slot
            byte slot = (int)abs(x);
            if (slot <= MAXPRGSLOTS) {
              prg[slot][0] = NULL;
              while (Serial.available() <= NULL) ;
              for (int i = 0; i <= MAXPRGSIZE; i++) {
                byte data = Serial.read();
                strcat(prg[slot], " ");
                prg[slot][strlen(prg[slot])] = data - ' ';
                //              byte data = Serial.read();
                //            prg[slot][i] = data;
                //EEPROM.write(EEADDRPRG + slot * MAXPRGSIZE + i, data);
                if (data == 'Z') break;
              }
              message(MSGOK);
            }
          }
          break;
        case PRINTX: // Print x (needed in programs)
          printnumber(x);
          delay(500);
          break;
        case STOP: // Stop program execution
          isrun = false;
          message(MSGSTOP);
          break;
      } // End of switch

      ispushed = false; // Common reset of isee, isnewnumber, ...
      isnewnumber = true;
      isee = false;
      isenteringnumber = false;
    }

    // Print stack for testing
    Serial.print(x, 6); Serial.print(" "); Serial.print(y, 6); Serial.print(" "); Serial.println(z, 6);
    if (!isrun && !issolve && !isintegrate) printnumber(x);
  }
}

