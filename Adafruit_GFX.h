#ifndef _ADAFRUIT_GFX_H
  #define _ADAFRUIT_GFX_H

#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif
#include "gfxfont.h"

#ifndef __AVR__
  #define GFX_ENABLE_24Bit //don't use the 24Bit interface on AVR devices, they won't have enough memory
#endif

typedef struct color24 {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} color24;

class Adafruit_GFX : public Print {

 public:

  Adafruit_GFX(int16_t w, int16_t h); // Constructor

  // This MUST be defined by the subclass:
  virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;    ///< Virtual drawPixel() function to draw to the screen/framebuffer/etc, must be overridden in subclass. @param x X coordinate.  @param y Y coordinate. @param color 16-bit pixel color.

  /*
   * TRANSACTION API / CORE DRAW API
   * These MAY be overridden by the subclass to provide device-specific
   * optimized code.  Otherwise 'generic' versions are used.
   */
  virtual void startWrite(void);
  virtual void endWrite(void);

  virtual void writePixel(int16_t x, int16_t y, uint16_t color);
  virtual void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  virtual void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  virtual void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  virtual void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

  // 24 Bit interface
  #ifdef GFX_ENABLE_24Bit
  /*
   * this writePixel() overload *must* be overwritten by a driver class that wants to
   * implement a true 24 Bit Interface and handle the conversion and displaying of
   * color in the display defined hardware bit depth
   */
   virtual void drawPixel(int16_t x, int16_t y, color24 color);

  /*
   * These MAY be overridden by the subclass to provide device-specific
   * optimized code.  Otherwise 'generic' versions are used.
   */
  virtual void writePixel(int16_t x, int16_t y, color24 color);
  virtual void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, color24 color);
  virtual void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, color24 color);
  virtual void writeFastVLine(int16_t x, int16_t y, int16_t h, color24 color);
  virtual void writeFastHLine(int16_t x, int16_t y, int16_t w, color24 color);
  #endif

  /*
   * CONTROL API
   * optimized code.  Otherwise 'generic' versions are used.
   */
  virtual void setRotation(uint8_t r);
  virtual void invertDisplay(boolean i);
  virtual void display();


  /*
   * BASIC DRAW API
   * These MAY be overridden by the subclass to provide device-specific
   * optimized code.  Otherwise 'generic' versions are used.
   *
   * It's good to implement those, even if using transaction API
   */
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    virtual void fillScreen(uint16_t color);
    virtual void clearDisplay();
    // Optional and probably not necessary to change
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    uint16_t color565(color24 color);

    // 24 Bit interface
    #ifdef GFX_ENABLE_24Bit
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, color24 color);
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, color24 color);
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, color24 color);
    virtual void fillScreen(color24 color);
    // Optional and probably not necessary to change
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, color24 color);
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, color24 color);
    #endif

  // These exist only with Adafruit_GFX (no subclass overrides)
  void
    drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),
    drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
      uint16_t color),
    fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),
    fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
      int16_t delta, uint16_t color),
    drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color),
    fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color),
    drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
      int16_t radius, uint16_t color),
    fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
      int16_t radius, uint16_t color),
    drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
      int16_t w, int16_t h, uint16_t color),
    drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
      int16_t w, int16_t h, uint16_t color, uint16_t bg),
    drawBitmap(int16_t x, int16_t y, uint8_t *bitmap,
      int16_t w, int16_t h, uint16_t color),
    drawBitmap(int16_t x, int16_t y, uint8_t *bitmap,
      int16_t w, int16_t h, uint16_t color, uint16_t bg),
    drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
      int16_t w, int16_t h, uint16_t color),
    drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
      int16_t w, int16_t h),
    drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap,
      int16_t w, int16_t h),
    drawGrayscaleBitmap(int16_t x, int16_t y,
      const uint8_t bitmap[], const uint8_t mask[],
      int16_t w, int16_t h),
    drawGrayscaleBitmap(int16_t x, int16_t y,
      uint8_t *bitmap, uint8_t *mask, int16_t w, int16_t h),
    drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[],
      int16_t w, int16_t h),
    drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap,
      int16_t w, int16_t h),
    drawRGBBitmap(int16_t x, int16_t y,
      const uint16_t bitmap[], const uint8_t mask[],
      int16_t w, int16_t h),
    drawRGBBitmap(int16_t x, int16_t y,
      uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h),
    drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
      uint16_t bg, uint8_t size),
    setCursor(int16_t x, int16_t y),
    setTextColor(uint16_t c),
    setTextColor(uint16_t c, uint16_t bg),
    setTextSize(uint8_t s),
    setTextWrap(boolean w),
    cp437(boolean x=true),
    setFont(const GFXfont *f = NULL),
    getTextBounds(const char *string, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h),
    getTextBounds(char *string, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h),
    getTextBounds(const __FlashStringHelper *s, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h),
    getTextBounds(const String &str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);

    // 24Bit interface
    #ifdef GFX_ENABLE_24Bit
  void
    drawCircle(int16_t x0, int16_t y0, int16_t r, color24 color),
    drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
      color24 color),
    fillCircle(int16_t x0, int16_t y0, int16_t r, color24 color),
    fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
      int16_t delta, color24 color),
    drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, color24 color),
    fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, color24 color),
    drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
      int16_t radius, color24 color),
    fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
      int16_t radius, color24 color),
    drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
      int16_t w, int16_t h, color24 color),
    drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
      int16_t w, int16_t h, color24 color, uint16_t bg),
    drawBitmap(int16_t x, int16_t y, uint8_t *bitmap,
      int16_t w, int16_t h, color24 color),
    drawBitmap(int16_t x, int16_t y, uint8_t *bitmap,
      int16_t w, int16_t h, color24 color, uint16_t bg),
    drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
      int16_t w, int16_t h, color24 color),
    drawChar(int16_t x, int16_t y, unsigned char c, color24 color,
      uint16_t bg, uint8_t size),
    setTextColor(color24 c),
    setTextColor(color24 c, color24 bg);
    #endif

#if ARDUINO >= 100
  virtual size_t write(uint8_t);
#else
  virtual void   write(uint8_t);
#endif

  int16_t height(void) const;
  int16_t width(void) const;

  uint8_t getRotation(void) const;

  // get current cursor position (get rotation safe maximum values, using: width() for x, height() for y)
  int16_t getCursorX(void) const;
  int16_t getCursorY(void) const;

 protected:
  void
    charBounds(char c, int16_t *x, int16_t *y,
      int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy);
  const int16_t
    WIDTH,          ///< This is the 'raw' display width - never changes
    HEIGHT;         ///< This is the 'raw' display height - never changes
  int16_t
    _width,         ///< Display width as modified by current rotation
    _height,        ///< Display height as modified by current rotation
    cursor_x,       ///< x location to start print()ing text
    cursor_y;       ///< y location to start print()ing text
  uint16_t
    textcolor,      ///< 16-bit background color for print()
    textbgcolor;    ///< 16-bit text color for print()
  uint8_t
    textsize,       ///< Desired magnification of text to print()
    rotation;       ///< Display rotation (0 thru 3)
  boolean
    wrap,           ///< If set, 'wrap' text at right edge of display
    _cp437;         ///< If set, use correct CP437 charset (default is off)
  GFXfont
    *gfxFont;       ///< Pointer to special font
};


/// A simple drawn button UI element
class Adafruit_GFX_Button {

 public:
  Adafruit_GFX_Button(void);
  // "Classic" initButton() uses center & size
  void initButton(Adafruit_GFX *gfx, int16_t x, int16_t y,
   uint16_t w, uint16_t h, uint16_t outline, uint16_t fill,
   uint16_t textcolor, char *label, uint8_t textsize);
  // New/alt initButton() uses upper-left corner & size
  void initButtonUL(Adafruit_GFX *gfx, int16_t x1, int16_t y1,
   uint16_t w, uint16_t h, uint16_t outline, uint16_t fill,
   uint16_t textcolor, char *label, uint8_t textsize);
  void drawButton(boolean inverted = false);
  boolean contains(int16_t x, int16_t y);

  void press(boolean p);
  boolean isPressed();
  boolean justPressed();
  boolean justReleased();

 private:
  Adafruit_GFX *_gfx;
  int16_t       _x1, _y1; // Coordinates of top-left corner
  uint16_t      _w, _h;
  uint8_t       _textsize;
  uint16_t      _outlinecolor, _fillcolor, _textcolor;
  char          _label[10];

  boolean currstate, laststate;
};
#endif
