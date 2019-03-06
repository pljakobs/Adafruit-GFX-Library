#ifndef _ADAFRUIT_GFX_CANVAS_H
  #define _ADAFRUIT_GFX_CANVAS_H

#ifndef _ADAFRUIT_GFX_H
  #include "Adafruit_GFX.h"
#endif

#ifdef __AVR__
  #include <avr/pgmspace.h>
#elif defined(ESP8266) || defined(ESP32)
  #include <pgmspace.h>
#endif
#include <vector>

#define ERR_NOMEM       1
#define ERR_OUTOFRANGE  2
#define ERR_NOBUFFER    3

#define DIR_HORIZONTAL  0
#define DIR_VERTICAL    1

/// A GFX 1-bit canvas context for graphics
class GFXcanvas1 : public Adafruit_GFX {
 public:
  GFXcanvas1(uint16_t w, uint16_t h);
  ~GFXcanvas1(void);
  void     drawPixel(int16_t x, int16_t y, uint16_t color),
           fillScreen(uint16_t color),
           drawFastHLine(int16_t x, int16_t y, uint16_t w, uint16_t color),
           drawFastVLine(int16_t x, int16_t y, uint16_t h, uint16_t color);
  uint8_t *getBuffer(void);
  uint8_t getByte(int16_t x, int16_t y);
  bool    getPixel(int16_t x, int16_t y);
 private:
  uint8_t *buffer;
};


/// A GFX 8-bit canvas context for graphics
class GFXcanvas8 : public Adafruit_GFX {
 public:
  GFXcanvas8(uint16_t w, uint16_t h);
  ~GFXcanvas8(void);
  void     drawPixel(int16_t x, int16_t y, uint16_t color),
           fillScreen(uint16_t color),
           writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

  uint8_t *getBuffer(void);
  bool     getPixel(int16_t x, int16_t y);
 private:
  uint8_t *buffer;
};


///  A GFX 16-bit canvas context for graphics
class GFXcanvas16 : public Adafruit_GFX {
 public:
  GFXcanvas16(uint16_t w, uint16_t h);
  ~GFXcanvas16(void);
  void      drawPixel(int16_t x, int16_t y, uint16_t color),
            fillScreen(uint16_t color);
  uint16_t *getBuffer(void);
 private:
  uint16_t *buffer;
};

class GFXiCanvas : public Adafruit_GFX {
public:
  GFXiCanvas(int16_t width, int16_t height, uint8_t depth);
  ~GFXiCanvas(void);
  void
    // basic indexed drawing interface using uint8_t and
    // uint16_t color parameters for compatibility within
    // basic drawing routines
    drawPixel(int16_t x, int16_t y, uint16_t colorIndex),
    drawPixel(int16_t x, int16_t y, uint8_t colorIndex),

    drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
    drawFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color),

    //drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
    //drawFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color),

    setColor(uint8_t index, color24 color),
    draw(int16_t x, int16_t y, Adafruit_GFX *display, int16_t x0, int16_t y0, int16_t width, int16_t height),
    draw(int16_t x, int16_t y, Adafruit_GFX *display),
    quickDraw(int16_t x, int16_t y, Adafruit_GFX *display, int16_t x0, int16_t y0, int16_t width, int16_t height),     
    rQuickDraw(int16_t x, int16_t y, Adafruit_GFX *display, int16_t x0, int16_t y0, int16_t width, int16_t height),
    clearDisplay(void),
    setTransparent(uint8_t color,bool t),
    setTransparent(uint16_t color,bool t),
    setTransparent(bool t),
    setRotation(uint8_t rot),
    setTextHint(bool h),
    makeHTMLPalette(),
    dump(usb_serial_class *s);

  color24
    getPixel24(int16_t x, int16_t y),
    getColor(uint8_t index);
  uint16_t
    getPixel565(int16_t x, int16_t y);
  uint8_t
    getLastError(),
    getPixelColorIndex(int16_t x, int16_t y),
    getDepth();
  uint8_t *
    getBuffer(uint8_t bitmap);
private:
  void drawSegment(int16_t x0, int16_t y0, Adafruit_GFX *display, int16_t x, int16_t y, color24 c, int16_t l,bool dir);
  uint8_t
    _depth,
    _last_ERR,
    _transparent,
    _rotation;
  bool
    _useTransparency,
    _textHint;
  std::vector <color24> palette;
  std::vector <GFXcanvas1*> bitplane;
};

#endif // _ADAFRUIT_GFX_CANVASH
