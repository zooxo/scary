/*
  Welcome to ScArY (Scientific Calculator with RPN on an ATTINY)
  Version 1.0 ... (c) 2018 by deetee/zooxo

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


// DEFINES

#define _abs(x) ((x<0)?(-x):(x)) // abs()-substitute macro

// Pin assignment
//#define STROBE 9 // Strobe pin // Arduino/Genuino Micro
//#define CLOCK  8 // Clock pin
//#define DATA   7 // Data pin
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
#define TINYNUMBER     1e-7 // Number for rounding to 0
#define FIX               3 // Display 3 decimals
#define FIXMANT           3 // FIX in 10th-exponent
#define FIXSHOW           6 // FIX for SHOW
#define FIXMANTSHOW       6 // FIX in 10th-exponent
#define BRIGHTMAX         7 // Maximal value for brightness
#define MAXITERATE      100 // Maximal number of Taylor series loops to iterate
#define MENUKEYS          4 // Menu keys (ABCD)
#define MAXMENU           5 // Number of MENUs (including 0)
#define NUMBEROFF        15 // Number of casted f-keys

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
//#define '('
//#define ')'
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
//#define '<'
//#define '='
//#define '>'
//#define '?'
//#define '@'
#define MENU 'A'
#define ACOSH 'B'
#define CE 'C'
//#define 'D'
#define EE 'E'
//#define 'F'
#define GAUSS 'G'
//#define 'H'
//#define 'I'
//#define 'J'
//#define 'K'
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
#define LASTX 'X'
//#define 'Y'
//#define 'Z'
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
//#define 'h'
#define INV 'i'
//#define 'j'
//#define 'k'
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


// SUBPROGRAMS

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
  static byte oldkey = 0; // Needed for debouncing
  byte key1 = buttoncast(), key2 = 0;
  if (key1 != oldkey) key2 = buttoncast();
  if (key1 == key2) {
    oldkey = key1;
    return (key1);
  }
  return (NULL);
}

void printbuf(byte *buf, byte dotpos) { // Write buffer and dot to display
  byte digbuf;
  if (dotpos > 0 && dotpos <= DIGITS) // Set dot
    buf[dotpos - 1] = buf[dotpos - 1] | _7FULLSTOP;

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

void printfloat(double f, boolean show) { // Prints double or mantissa (show=true)
  const byte digits[] = { // Character set to display numbers
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

  if (show) { // Set local variables for "SHOW print" if SHOW was demanded
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

  if (show) dispbuf[0] = _7APOSTROPHELEFT; // Sign for show
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
      dispbuf[6] = digits[(e / 10) % 10];
      dispbuf[7] = digits[e % 10];
    }
  }
  printbuf(dispbuf, dot); // Write buffer and dot to display
}

byte fcast(byte k) { // Returns f-key code
  const byte _f_old[] = {' ', '3', '6', '9', '7', '.', '0', 'E', '#', '1', '2', '4', '5', 'c', '8'}; // f-cast from
  const byte _f_new[] = {'+', '-', '*', '/', 'A', 'X', 'y', 'R', 'r', 'M', 'm', 'p', 'Q', 'z', 'x'}; // to
  for (byte i = 0; i < NUMBEROFF; i++) {
    if (k == _f_old[i]) return (_f_new[i]);
  }
  return (NULL);
}

void push(double* a, double* b, double* c, double* d) { // Push stack
  *d = *c; *c = *b; *b = *a;
}

void pull(double* a, double* b, double* c, double* d, boolean isfull) { // Pull stack
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


// SETUP and LOOP

void setup() {
  //int main(void) { //***
  //init(); //***
  //{ //***
  pinMode(STROBE, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  cmd(0x88); // Activate and brightness "1000 abbb" (a=1)
  printbuf("@mXwPn@", 0); // Welcome message -ScArY-
  //printbuf("@vy88?@", 0); // Welcome message -HELLO-
  //printfloat(0.0,false); // No welcome message
}

void loop() {
  //while (1) { //***
  byte key = NULL;
  static double x = 0.0, y = 0.0, z = 0.0, u = 0.0, lastx = 0.0, mem = 0.0; // Stack, memory
  static double rad = 180.0 / PI; // Multiplier for radiants
  static boolean isnewnumber = false; // True if stack has to be lifted before entering a new number
  static boolean ispushed = false; // True if stack was already pushed by ENTER
  static boolean isfpressed = false; // Function key pressed
  static boolean isee = false; // True if EE was pressed and exponent will be entered
  static boolean isenteringnumber = true; // Used to differ clear and clear-entry
  static boolean isdot = false; // True if dot was pressed and decimals will be entered
  static byte decimals = 0; // Number of decimals entered - used for input after decimal dot
  static boolean isshow = false; // True, if SHOW was demanded
  static boolean ismenu = false; // True, if MENU was demanded
  static int8_t ee = 0; // EExponent
  static boolean isprintmenu = true; // True if MENU/CONST should be printed
  static byte selectnr = 0; // Number of selected menu/const item
  static byte brightness = 0;
  static boolean isdisplaydeactivated = false;

  const byte _msgs[][DIGITS] = {
    {_7LETTERP, 0, _7LETTERr, 0, _7LETTERE, 0, _7LETTERL, 0},          // pow_1/x_exp_ln
    {0, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0},                  // _sin_cos_tan
    {_7HIGHLINE, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0},         // _asin_acos_atan
    {_7LETTERh, 0, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0},          // _sinh_cosh_tanh
    {_7LETTERh, _7HIGHLINE, _7LETTERS, 0, _7LETTERc, 0, _7LETTERt, 0}, // _asinh_acosh_atanh
    {_7LETTERA, 0, _7LETTERG, 0, _7LETTERF, 0, _7LETTERd, _7LETTERr},  // annu_gauss_deg_rad
  };
  const byte _menuchar[][4] = { // Menu keycodes
    {'P', 'i', 'L', 'l'},     // pow_1/x_exp_ln
    {0, 's', 'o', 't'},       // _sin_cos_tan
    {0, 'S', 'O', 'T'},       // _asin_acos_atan
    {0, 'v', 'b', 'n'},       // _sinh_cosh_tanh
    {0, 'V', 'B', 'N'},       // _asinh_acosh_atanh
    {'a', 'G', 'g', 'd'},     // annu_gauss_!_deg/rad
  };

  key = getkey(); // Read character

  if (ismenu) { // Selecting MENU
    byte dispbuf[DIGITS];
    byte maxnr = MAXMENU;
    if (isprintmenu) {
      for (byte i = 0; i < DIGITS; i++) dispbuf[i] = _msgs[selectnr][i];
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
      printfloat(x, false);
      ismenu = false;
      selectnr = 0;
    }
    if (key == SHIFT || (key >= DIGIT7 && key <= DIGIT9)) { // Choose option
      if (key == SHIFT) key = DIGIT6;
      key = _menuchar[selectnr][key - DIGIT6];
      ismenu = false;
    }
    else key = NULL;
  }
  else if (key == SHIFT) { // Toggle function key f
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
  else if (key == DOT) { // Entering decimals demanded
    if (!isfpressed) {
      if (isnewnumber) { // Enable starting new number with .
 //       if (ispushed) ispushed = false;
 //       else push(&x, &y, &z, &u);
        x = 0.0;
        decimals = 0;
        isnewnumber = false;
      }
      isdot = true;
      key = NULL;
    }
  }
  else if (key == EE && !isfpressed) { // Entering EE-input demanded
    if (isee && x > 0.0 && x != 1.0) { // Change sign of EE if EE is pressed the second time
      byte tmp = 0;
      if (x < 1.0 && log10(x) != (int)log10(x)) tmp = 1;
      x = x / _pow10(2 * ((int)log10(x) - tmp));
      printfloat(x, false);
    }
    isee = true;
    ee = 0;
    key = NULL;
  }

  if (key != NULL) { // Treat key if valid
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
    else if (key == SHOW) isshow = true; // SHOW demanded
    else if (key == MENU) { // Activate MENU
      //selectnr = 0; // Uncomment if MENU should always start at first entry
      isprintmenu = true;
      ismenu = true;
    }

    else { // Other commands - finally setting the ispushed false and isnewnumber true

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
        case STO: // STO
          mem = x;
          break;
        case RCL: // RCL
          push(&x, &y, &z, &u);
          x = mem;
          break;
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
          x = _exp_sin(0.5 * log(x), true);
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
          if (rad == 1.0) rad = 180.0 / PI;
          else rad = 1.0;
          break;
        case ANNU: // Annuity
          x = (1 - _exp_sin(-x * log(1 + y), true)) / y;
          pull(&x, &y, &z, &u, false);
          break;
        case SIN: case ASIN: case COS: case ACOS: case TAN: case ATAN: { // Trigonometric
            double si = _exp_sin(x / rad, false);
            double co = _exp_sin(0.5 * log(1 - si * si), true);
            double as = atan(x / _exp_sin(0.5 * log(1 - x * x), true));
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
            else if (key == ASINH) x = log(x + _exp_sin(0.5 * log(tmp), true));
            else if (key == COSH) x = (ep + em) / 2;
            else if (key == ACOSH) x = log(x + _exp_sin(0.5 * log(tmp - 2), true));
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
        case FACT: // Factorial !
          double tmp = 1.0;
          for (byte i = 1; i <= x; i++) tmp *= i;
          x = tmp;
          break;
      } // End of switch

      ispushed = false; // Common reset of isee, isnewnumber, ...
      isnewnumber = true;
      isee = false;
      isenteringnumber = false;
    }

    //Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" "); Serial.println(z);
    printfloat(x, isshow);
    isshow = false;
  }
}
//} //***

