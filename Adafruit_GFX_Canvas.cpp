#include "Adafruit_GFX_Canvas.h"
#ifndef Adafruit_GFX
  #include "Adafruit_GFX.h"
#endif
#ifdef __AVR__
  #include <avr/pgmspace.h>
#elif defined(ESP8266) || defined(ESP32)
  #include <pgmspace.h>
#endif
//#define CALLTRACE 1

// -------------------------------------------------------------------------
// GFXcanvas1, GFXcanvas8 and GFXcanvas16 (currently a WIP, don't get too
// comfy with the implementation) provide 1-, 8- and 16-bit offscreen
// canvases, the address of which can be passed to drawBitmap() or
// pushColors() (the latter appears only in a couple of GFX-subclassed TFT
// libraries at this time).  This is here mostly to help with the recently-
// added proportionally-spaced fonts; adds a way to refresh a section of the
// screen without a massive flickering clear-and-redraw...but maybe you'll
// find other uses too.  VERY RAM-intensive, since the buffer is in MCU
// memory and not the display driver...GXFcanvas1 might be minimally useful
// on an Uno-class board, but this and the others are much more likely to
// require at least a Mega or various recent ARM-type boards (recommended,
// as the text+bitmap draw can be pokey).  GFXcanvas1 requires 1 bit per
// pixel (rounded up to nearest byte per scanline), GFXcanvas8 is 1 byte
// per pixel (no scanline pad), and GFXcanvas16 uses 2 bytes per pixel (no
// scanline pad).
// NOT EXTENSIVELY TESTED YET.  MAY CONTAIN WORST BUGS KNOWN TO HUMANKIND.
/**************************************************************************/

/*!
   @brief    Instantiate a GFX 1-bit canvas context for graphics
   @param    w   Display width, in pixels
   @param    h   Display height, in pixels
*/
/**************************************************************************/
GFXcanvas1::GFXcanvas1(uint16_t w, uint16_t h) : Adafruit_GFX(w, h) {
    uint16_t bytes = ((w + 7) / 8) * h;
    if((buffer = (uint8_t *)malloc(bytes))) {
        memset(buffer, 0, bytes);
    }
}

/**************************************************************************/
/*!
   @brief    Delete the canvas, free memory
*/
/**************************************************************************/
GFXcanvas1::~GFXcanvas1(void) {
    if(buffer) free(buffer);
}

/**************************************************************************/
/*!
   @brief    Get a pointer to the internal buffer memory
   @returns  A pointer to the allocated buffer
*/
/**************************************************************************/
uint8_t* GFXcanvas1::getBuffer(void) {
  return buffer;
}

/**************************************************************************/
/*!
   @brief    Draw a pixel to the canvas framebuffer
    @param   x   x coordinate
    @param   y   y coordinate
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas1::drawPixel(int16_t x, int16_t y, uint16_t color) {
#ifdef __AVR__
    // Bitmask tables of 0x80>>X and ~(0x80>>X), because X>>Y is slow on AVR
    static const uint8_t PROGMEM
      GFXsetBit[] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },
      GFXclrBit[] = { 0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE };
#endif
    //Serial.printf("drawPixel, canvas dimension: w: %03i, h: %03i\n",WIDTH,HEIGHT);
    //Serial.printf("drawPixel, before rotation : x: %03i, y: %03i, rot: %1i\n", x, y, this->rotation);
    if(buffer) {
      int16_t t;
      switch(rotation) {
          case 1:
              t = x;
              x = WIDTH  - 1 - y;
              y = t;
              break;
          case 2:
              x = WIDTH  - 1 - x;
              y = HEIGHT - 1 - y;
              break;
          case 3:
              t = x;
              x = y;
              y = HEIGHT - 1 - t;
              break;
      }
      if((x < 0) || (y < 0) || (x >= WIDTH) || (y >= HEIGHT)) return;
      //Serial.printf("drawPixel, after rotation  : x: %03i, y: %03i, rot: %1i, offsett: %i\n\n", x, y, this->rotation,(x / 8) + y * ((WIDTH + 7) / 8));
      
      uint8_t   *ptr  = &buffer[(x / 8) + y * ((WIDTH + 7) / 8)];
      
#ifdef __AVR__
        if(color) *ptr |= pgm_read_byte(&GFXsetBit[x & 7]);
        else      *ptr &= pgm_read_byte(&GFXclrBit[x & 7]);
#else
        if(color) *ptr |=   0x80 >> (x & 7);
        else      *ptr &= ~(0x80 >> (x & 7));
#endif
    }
}

bool GFXcanvas1::getPixel(int16_t x, int16_t y) {
#ifdef __AVR__
  // Bitmask tables of 0x80>>X and ~(0x80>>X), because X>>Y is slow on AVR
  static const uint8_t PROGMEM
    GFXsetBit[] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },
    GFXclrBit[] = { 0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE };
#endif
  bool c;
    if(buffer) {
/*
      int16_t t;
      switch(rotation) {
          case 1:
              t = x;
              x = WIDTH  - 1 - y;
              y = t;
              break;
          case 2:
              x = WIDTH  - 1 - x;
              y = HEIGHT - 1 - y;
              break;
          case 3:
              t = x;
              x = y;
              y = HEIGHT - 1 - t;

              break;
      }
*/
      if((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) return false;  
      uint8_t   *ptr  = &buffer[(x / 8) + y * ((WIDTH + 7) / 8)];
#ifdef __AVR__
        c = *ptr & pgm_read_byte(&GFXsetBit[x & 7]);
#else
        c = *ptr & 0x80>>(x & 7);
#endif
      //Serial.printf("getPixel x: %i, y: %i, byte: %02x, mask: %02x, c: %i\n",x,y,*ptr, 0x80>>(x % 7),c);
      if (c!=0){
        return 0x01;
      }
      else{
        return 0x0;
      }
    }
    else{
      return false;
    }
}

/*
 * read a full eight bits from a bitplane.
 * only used to quickly draw on screen
 */
uint8_t GFXcanvas1::getByte(int16_t x, int16_t y) {
  if(buffer) {
      if((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) return false;

      int16_t t;
      switch(rotation) {
          case 1:
              t = x;
              x = WIDTH  - 1 - y;
              y = t;
              break;
          case 2:
              x = WIDTH  - 1 - x;
              y = HEIGHT - 1 - y;
              break;
          case 3:
              t = x;
              x = y;
              y = HEIGHT - 1 - t;

              break;
      }
      return buffer[(x / 8) + y * ((WIDTH + 7) / 8)];
    }
  }

/**************************************************************************/
/*!
    @brief    Write a perfectly horizontal line, overwrite in subclasses if startWrite is defined!
    @param    x   Left-most x coordinate
    @param    y   Left-most y coordinate
    @param    w   Width in pixels
    @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas1::drawFastHLine(int16_t x, int16_t y, uint16_t w, uint16_t color){
  // todo: implement fast h-line drawing by writing whole bytes if possible
  drawLine(x,y,x+w,y, color);
}

/**************************************************************************/
/*!
    @brief    Write a perfectly vertical line, overwrite in subclasses if startWrite is defined!
    @param    x   Left-most x coordinate
    @param    y   Left-most y coordinate
    @param    h   height in pixels
    @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas1::drawFastVLine(int16_t x, int16_t y, uint16_t h, uint16_t color){
  // todo: implement fast V-line drawing by writing whole bytes if possible
  drawLine(x,y,x,y+h,color);
}

/**************************************************************************/
/*!
   @brief    Fill the framebuffer completely with one color
    @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas1::fillScreen(uint16_t color) {
    if(buffer) {
        uint16_t bytes = ((WIDTH + 7) / 8) * HEIGHT;
        memset(buffer, color ? 0xFF : 0x00, bytes);
    }
}

/**************************************************************************/
/*!
   @brief    Instatiate a GFX 8-bit canvas context for graphics
   @param    w   Display width, in pixels
   @param    h   Display height, in pixels
*/
/**************************************************************************/
GFXcanvas8::GFXcanvas8(uint16_t w, uint16_t h) : Adafruit_GFX(w, h) {
    uint32_t bytes = w * h;
    if((buffer = (uint8_t *)malloc(bytes))) {
        memset(buffer, 0, bytes);
    }
}

/**************************************************************************/
/*!
   @brief    Delete the canvas, free memory
*/
/**************************************************************************/
GFXcanvas8::~GFXcanvas8(void) {
    if(buffer) free(buffer);
}


/**************************************************************************/
/*!
   @brief    Get a pointer to the internal buffer memory
   @returns  A pointer to the allocated buffer
*/
/**************************************************************************/
uint8_t* GFXcanvas8::getBuffer(void) {
    return buffer;
}

/**************************************************************************/
/*!
   @brief    Draw a pixel to the canvas framebuffer
    @param   x   x coordinate
    @param   y   y coordinate
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas8::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if(buffer) {
        if((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) return;

        int16_t t;
        switch(rotation) {
            case 1:
                t = x;
                x = WIDTH  - 1 - y;
                y = t;
                break;
            case 2:
                x = WIDTH  - 1 - x;
                y = HEIGHT - 1 - y;
                break;
            case 3:
                t = x;
                x = y;
                y = HEIGHT - 1 - t;
                break;
        }

        buffer[x + y * WIDTH] = color;
    }
}

/**************************************************************************/
/*!
    @brief    Fill the framebuffer completely with one color
    @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas8::fillScreen(uint16_t color) {
    if(buffer) {
        memset(buffer, color, WIDTH * HEIGHT);
    }
}

void GFXcanvas8::writeFastHLine(int16_t x, int16_t y,
  int16_t w, uint16_t color) {

    if((x >= _width) || (y < 0) || (y >= _height)) return;
    int16_t x2 = x + w - 1;
    if(x2 < 0) return;

    // Clip left/right
    if(x < 0) {
        x = 0;
        w = x2 + 1;
    }
    if(x2 >= _width) w = _width - x;

    int16_t t;
    switch(rotation) {
        case 1:
            t = x;
            x = WIDTH  - 1 - y;
            y = t;
            break;
        case 2:
            x = WIDTH  - 1 - x;
            y = HEIGHT - 1 - y;
            break;
        case 3:
            t = x;
            x = y;
            y = HEIGHT - 1 - t;
            break;
    }

    memset(buffer + y * WIDTH + x, color, w);
}

/**************************************************************************/
/*!
   @brief    Instatiate a GFX 16-bit canvas context for graphics
   @param    w   Display width, in pixels
   @param    h   Display height, in pixels
*/
/**************************************************************************/
GFXcanvas16::GFXcanvas16(uint16_t w, uint16_t h) : Adafruit_GFX(w, h) {
    uint32_t bytes = w * h * 2;
    if((buffer = (uint16_t *)malloc(bytes))) {
        memset(buffer, 0, bytes);
    }
}

/**************************************************************************/
/*!
   @brief    Delete the canvas, free memory
*/
/**************************************************************************/
GFXcanvas16::~GFXcanvas16(void) {
    if(buffer) free(buffer);
}

/**************************************************************************/
/*!
   @brief    Get a pointer to the internal buffer memory
   @returns  A pointer to the allocated buffer
*/
/**************************************************************************/
uint16_t* GFXcanvas16::getBuffer(void) {
    return buffer;
}

/**************************************************************************/
/*!
   @brief    Draw a pixel to the canvas framebuffer
    @param   x   x coordinate
    @param   y   y coordinate
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas16::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if(buffer) {
        if((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) return;

        int16_t t;
        switch(rotation) {
            case 1:
                t = x;
                x = WIDTH  - 1 - y;
                y = t;
                break;
            case 2:
                x = WIDTH  - 1 - x;
                y = HEIGHT - 1 - y;
                break;
            case 3:
                t = x;
                x = y;
                y = HEIGHT - 1 - t;
                break;
        }

        buffer[x + y * WIDTH] = color;
    }
}

/**************************************************************************/
/*!
   @brief    Fill the framebuffer completely with one color
    @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void GFXcanvas16::fillScreen(uint16_t color) {
    if(buffer) {
        uint8_t hi = color >> 8, lo = color & 0xFF;
        if(hi == lo) {
            memset(buffer, lo, WIDTH * HEIGHT * 2);
        } else {
            uint32_t i, pixels = WIDTH * HEIGHT;
            for(i=0; i<pixels; i++) buffer[i] = color;
        }
    }
}

/**************************************************************************/
/*!
   @brief    Instatiate a GFX bitmapped canvas for drawing
   @param    w   canvas width, in pixels
   @param    h   canvas height, in pixels
   @param    d   number of bitplanes
*/
/**************************************************************************/
GFXiCanvas::GFXiCanvas(int16_t w, int16_t h, uint8_t d):Adafruit_GFX(w, h){
  _width=w;
  _height=h;
  _depth=d;
  _last_ERR=0;
  GFXcanvas1 *plane;
  /*!
    @remark
        depth is depth in bits, not number of colors!
        it has to be larger than 1 and smaller or equal 8,
        single bit bitplanes should use GFXcanvas1, 8bpp can
        alternatively use GFXCanvas8, although I'm not quite
        sure how that handles colors (assigns 16 Bit color to
          8Bit memory cell?)

    @remark
        Any iCanvas object will have a palette assigned to it that
        is used to map color numbers derived from the bitplanes to
        the actual 16 or 24 bit (565 or 888) color value
        the layout in memory will be like this for an iCanvas of depth 4


        ``````
        bitplane[0] *GFXCanvas1 <Bit 0: 1 0 1 1 0 0 0 1>
        bitplane[1] *GFXCanvas1 <Bit 1: 0 0 0 1 0 1 1 1>
        bitplane[2] *GFXCanvas1 <Bit 2: 0 1 0 0 0 0 0 1>
        bitplane[3] *GFXCanvas1 <Bit 3: 1 1 0 0 1 0 0 0>
                                      ---------------
                       resulting color: 5 C 1 3 8 2 2 7

        palette[0]=color24{r,g,b};
        palette[1]=color24{r,g,b};
        palette[2]=color24{r,g,b};
          .
          .
          .
        palette[F]=color24{r,g,b};
        ``````
  */
  Serial.printf("\n>>>>>>>>>>>>>>>>>>>>>\n\n intializing canvas\nwidth:  %i\nheight: %i\ndepth:  %i\n\n",_width, _height, _depth);
  if(_depth <=8 && _depth >=1){
    //Serial.printf("struct palette: sizeof(palette[0].r)=%i, sizeof(palette[0].g)=%i, sizeof(palette[0].b)=%i\n",sizeof(palette[0].r),sizeof(palette[0].g),sizeof(palette[0].b));
    //bitplane.reserve(_depth);
    for( uint8_t i=0;i<_depth;i++){
      plane=new GFXcanvas1(_width, _height);
      if(plane->getBuffer()==0){
        /* could not create bitplane i, out of memory
         * reduce canvas depth to i to be able to
         * continue and set error condition
         */
        _depth=i;
        _last_ERR=ERR_NOMEM;
      }else{
        bitplane.push_back(plane);
        Serial.printf("initialized bitplane[%i] at %p\n",i,bitplane.at(i)->getBuffer());
      }
    }
    /*
     * set default palettes (up to 32 colors, anything above that will always be free)
     */
    uint16_t numColors = 1<<_depth;
    palette.reserve(numColors);
    Serial.printf("initializing palette for %i colors\nvector has a size of %i(%i)\n",numColors,palette.capacity(),sizeof(palette[0]));
    for(uint16_t n=0;n<numColors;n++){
      palette.push_back({.r=0,.g=0,.b=0});
    }
    Serial.printf("cleared palette, depth %i\n", _depth);
    /*!
     * the constructor creates a base palette so the canvas is usable right away
     * overwrite using setColor() as needed.
     */

    switch (_depth) {
      case 1:
        palette.at(0)={ 0,  0,  0};
        palette.at(1)={255,255,255}; //ssd1306 OLEDs need uint16_t 1 to draw pixel
      break;
      case 2:
        palette.at( 0)={.r=  0, .g=  0, .b=  0};
        palette.at( 1)={.r=255, .g=255, .b=255};
        palette.at( 2)={.r=255, .g=  0, .b=  0};
        palette.at( 3)={.r=  0, .g=255, .b=  0};
      break;
      case 3:
        palette.at( 0)={.r=  0, .g=  0, .b=  0};
        palette.at( 1)={.r=255, .g=255, .b=255};
        palette.at( 2)={.r=255, .g=  0, .b=  0};
        palette.at( 3)={.r=  0, .g=255, .b=  0};
        palette.at( 4)={.r=  0, .g=  0, .b=255};
        palette.at( 5)={.r=255, .g=  0, .b=255};
        palette.at( 6)={.r=255, .g=255, .b=  0};
        palette.at( 7)={.r=  0, .g=255, .b=255};
      break;
      case 4:
        palette.at( 0)= {.r= 20, .g= 12, .b= 28};
        palette.at( 1)= {.r= 68, .g= 36, .b= 52};
        palette.at( 2)= {.r= 48, .g= 52, .b=109};
        palette.at( 3)= {.r= 78, .g= 74, .b= 78};
        palette.at( 4)= {.r=133, .g= 76, .b= 48};
        palette.at( 5)= {.r= 52, .g=101, .b= 36};
        palette.at( 6)= {.r=208, .g= 70, .b= 72};
        palette.at( 7)= {.r=117, .g=113, .b= 97};
        palette.at( 8)= {.r= 89, .g=125, .b=206};
        palette.at( 9)= {.r=210, .g=125, .b= 44};
        palette.at(10)= {.r=133, .g=149, .b=161};
        palette.at(11)= {.r=109, .g=170, .b= 44};
        palette.at(12)= {.r=210, .g=170, .b=153};
        palette.at(13)= {.r=109, .g=194, .b=202};
        palette.at(14)= {.r=218, .g=212, .b= 94};
        palette.at(15)= {.r=222, .g=238, .b=214};
      break;
      case 5:
      case 6:
      case 7:
      case 8:
        palette.at( 0)={.r= 20, .g= 12, .b= 28};
        palette.at( 1)={.r= 68, .g= 36, .b= 52};
        palette.at( 2)={.r= 48, .g= 52, .b=109};
        palette.at( 3)={.r= 78, .g= 74, .b= 78};
        palette.at( 4)={.r=133, .g= 76, .b= 48};
        palette.at( 5)={.r= 52, .g=101, .b= 36};
        palette.at( 6)={.r=208, .g= 70, .b= 72};
        palette.at( 7)={.r=117, .g=113, .b= 97};
        palette.at( 8)={.r= 89, .g=125, .b=206};
        palette.at( 9)={.r=210, .g=125, .b= 44};
        palette.at(10)={.r=133, .g=149, .b=161};
        palette.at(11)={.r=109, .g=170, .b= 44};
        palette.at(12)={.r=210, .g=170, .b=153};
        palette.at(13)={.r=109, .g=194, .b=202};
        palette.at(14)={.r=218, .g=212, .b= 94};
        palette.at(15)={.r=222, .g=238, .b=214};
        palette.at(16)={.r= 10, .g=  6, .b= 14};
        palette.at(17)={.r= 34, .g= 18, .b= 26};
        palette.at(18)={.r= 24, .g= 26, .b= 54};
        palette.at(19)={.r= 39, .g= 37, .b= 38};
        palette.at(20)={.r= 66, .g= 38, .b= 24};
        palette.at(21)={.r= 26, .g= 50, .b= 18};
        palette.at(22)={.r=104, .g= 35, .b= 36};
        palette.at(23)={.r= 58, .g= 56, .b= 48};
        palette.at(24)={.r= 44, .g= 62, .b=103};
        palette.at(25)={.r=105, .g= 62, .b= 22};
        palette.at(26)={.r= 66, .g= 74, .b= 80};
        palette.at(27)={.r= 54, .g= 85, .b= 22};
        palette.at(28)={.r=105, .g= 85, .b= 76};
        palette.at(29)={.r= 54, .g= 97, .b=101};
        palette.at(30)={.r=109, .g=106, .b= 47};
        palette.at(31)={.r=111, .g=119, .b=107};
      break;
    }
    //      Serial.printf("set color position %i to {r=%i, g=%i, b=%i}\n",n,palette.at(n).r, palette.at(n).g, palette.at(n).b);
    Serial.printf("GFXiCanvas constructor finished\ncreated %i bitplanes and %i palette positions\n\n>>>>>>>>>>>>>>>>>>>>>\n",bitplane.capacity(), palette.capacity());
  }else{
    _last_ERR=ERR_OUTOFRANGE;
  }
}

/**************************************************************************/
/*!
   @brief    free up memory used by iCanvas object
 */
/**************************************************************************/
GFXiCanvas::~GFXiCanvas(){
  //Serial.printf("\n>>>>>>>>>>>>>>>>>>>>>\n\ndeleting canvas\nwidth:  %i\nheight: %i\ndepth:  %i\n\n",_width, _height, _depth);
  for(uint8_t i=0;i<this->_depth;i++){
    delete this->bitplane.at(i);
  }
  bitplane.clear();
  palette.clear();
  //Serial.printf("\n exit destructor\n\n>>>>>>>>>>>>>>>>>>>>>\n");
}

/**************************************************************************/
/*!
   @brief    return the depth of an iCanvas context
   @returns  depth
*/
/**************************************************************************/
uint8_t GFXiCanvas::getDepth(){
  return this->_depth;
}

/**************************************************************************/
/*!
   @brief    draws a pixel on an iCanvas
   @param    x   pixel x position
   @param    x   pixel Y position
   @PARAM    colorIndex indexed color as defined in the palette. an
             index greater than 2^bitplanes is silently discareded
             and the corresponding pixel remains unchanged on the canvas
*/
/***************************************************************************/
void GFXiCanvas::drawPixel(int16_t x, int16_t y, uint8_t colorIndex){
  if(colorIndex<(1<<this->_depth)){
    _last_ERR=0;
    #ifdef CALLTRACE
    Serial.printf("called drawPixel in canvas with 8Bit color x: %i, y: %i c: %i\n",x,y,colorIndex);
    #endif
    //Serial.printf("drawing pixel at x:%i, y:%i\n",x,y);
    for(uint8_t i=0;i<this->_depth;i++) {
      //Serial.printf("bitplane:%i, val:%i\n",i,(colorIndex && 1<<i));
      this->bitplane.at(i)->drawPixel(x,y,(colorIndex & (1<<i)));
      }
  }else{
    _last_ERR=ERR_OUTOFRANGE;
  }
}

/**************************************************************************/
/*!
   @brief    draws a pixel on an iCanvas
   @param    x   pixel x position
   @param    x   pixel Y position
   @PARAM    colorIndex indexed color as defined in the palette. an
             index greater than 2^bitplanes is silently discareded
             and the corresponding pixel remains unchanged on the canvas
 *
 * this is for compatibility with other libraries that don't know about
 * indexed colors. Basically, it will just use the lower 8 bits of the
 * color value as the index. Depending on the actual number of bitplanes,
 * this is further reduced.
 */
 /***************************************************************************/
void GFXiCanvas::drawPixel(int16_t x, int16_t y, uint16_t colorIndex){
  #ifdef CALLTRACE
  Serial.printf("called drawPixel in canvas with 16Bit color %i\n",colorIndex);
  #endif
  uint8_t c=(uint8_t)(colorIndex&0xff);
  drawPixel(x,y,c);
}

/**************************************************************************/
/*!
   @brief    return the rgb tupel assigned to the given palette position
   @param    i  palette position
   @returns  color24 c
*/
/***************************************************************************/
color24 GFXiCanvas::getColor(uint8_t i){
  //if(i!=0) Serial.printf("index: %i ",i);
  if(i<(1<<this->_depth)){
    _last_ERR=0;
    //color24 c=this->palette.at(i);
    //if(i!=0) Serial.printf("color: r: %i, g: %i, b: %i\n",c.r,c.g,c.b);
    return this->palette.at(i);
  }else{
    return (color24){0,0,0};
    _last_ERR=ERR_OUTOFRANGE;
  }
}

/**************************************************************************/
/*!
   @brief    set color for palette position
   @param    i  palette position
   @param    c  color24 struct defining the r, g and b components
*/
/***************************************************************************/
void GFXiCanvas::setColor(uint8_t i, color24 c){
  if(i<(1<<this->_depth)){
    _last_ERR=0;
    this->palette.at(i)=c;
  }else{
    _last_ERR=ERR_OUTOFRANGE;
  }
}

/**************************************************************************/
/*!
   @brief    get color index for a pixel on canvas
   @param    x   pixel x position
   @param    x   pixel Y position
   @returns  c   color palette position for the given pixel
*/
/***************************************************************************/
uint8_t GFXiCanvas::getPixelColorIndex(int16_t x, int16_t y){
  uint8_t c=0;
  _last_ERR=0;
  //Serial.printf("getPixelColorIndex x:%i, y:%i [",x,y);
  if(x<0 || x>_width || y<0 || y<_height) _last_ERR=ERR_OUTOFRANGE;
  for(uint8_t i=0;i<this->_depth;i++) {
    //Serial.printf("bitplane %i - ",i);
    //uint8_t b=(this->bitplane.at(i)->getPixel(x,y) & 0x01)<<i;
    c=c|(this->bitplane.at(i)->getPixel(x,y) & 0x01)<<i;
    //Serial.printf("x: %i, y: %i, i: %i bit: %i col: %i\n",x,y,i,b,c);
  }
  //Serial.printf("x: %i, y: %i, c: %i\n",x,y,c);
  return c;
}

/**************************************************************************/
/*!
   @brief    get color24 tupel for a pixel on canvas by resolving
             the palette location
   @param    x   pixel x position
   @param    x   pixel Y position
   @returns  c   color24 tupel for the given pixel
*/
/***************************************************************************/
color24 GFXiCanvas::getPixel24(int16_t x, int16_t y) {
  return getColor(getPixelColorIndex(x,y));
}

/**************************************************************************/
/*!
   @brief    get color565 value for a pixel on canvas by resolving
             the palette location
   @param    x   pixel x position
   @param    x   pixel Y position
   @returns  c   uint16_t color565 value for the given pixel
*/
/***************************************************************************/
uint16_t GFXiCanvas::getPixel565(int16_t x, int16_t y) {
  color24 color;
  color = getPixel24(x,y);
  uint16_t c;
  //Serial.printf("getPixel656, x:%i, y:%i, r=%i, g=%i, b=%i\n",x,y,color.r,color.g,color.b);
  c=(color.r & 0xF8) << 8 | (color.g & 0xFC) << 3 | (color.b & 0xF8) >> 3;
  return c;
}

/**************************************************************************/
/*!
   @brief    set the palette value that should be used as transparent
   @param    colorIndex the palette position to be considered _transparent
   @param    t   whether or not to actually use it as _transparent
   @remark   if b=false, the given palette color will be painted as set
             otherwhise, it will not be painted, leaving the pixel on
             screen unchanged
*/
/***************************************************************************/
void GFXiCanvas::setTransparent(uint8_t colorIndex, bool t){
  if(colorIndex<(1<<this->_depth)){
    _last_ERR=0;
    _transparent=colorIndex;
  }else{
    _last_ERR=ERR_OUTOFRANGE;
  }
  _useTransparency=t;
}

/**************************************************************************/
/*!
   @brief   set the canvas rotation
   @param   r rotation parameter as defined in Adafruit-GFX
*/
/**************************************************************************/
void GFXiCanvas::setRotation(uint8_t rot){
  _rotation=rot;
  /*
  for(uint8_t i=0;i<this->_depth;i++){
    bitplane.at(i)->setRotation(_rotation);
  }
  */
}

/**************************************************************************/
/*!
   @brief    set the palette value that should be used as transparent
   @param    colorIndex the palette position to be considered _transparent
   @param    t   whether or not to actually use it as _transparent
   @remark   if b=false, the given palette color will be painted as set
             otherwhise, it will not be painted, leaving the pixel on
             screen unchanged
*/
/***************************************************************************/
void GFXiCanvas::setTransparent(uint16_t colorIndex, bool t){
  setTransparent((uint8_t)(colorIndex&0xff),t);
}

/**************************************************************************/
/*!
   @brief    set transparency status
   @param    b   whether or not to actually use it as _transparent
   @remark   if b=false, the given palette color will be painted as set
             otherwhise, it will not be painted, leaving the pixel on
             screen unchanged
*/
/***************************************************************************/
void GFXiCanvas::setTransparent(bool t){
  _useTransparency=t;
}

/**************************************************************************/
/*!
   @brief    make html Palette
   @param    none
   @remark   create a (partial) html standard palette.
             depending on the bit depth of the canvas, this
             will provide a selection of html colors. Six
             bitplanes will allow for all 140 colors defined by
             name in htmlcolors.h
 */
/**************************************************************************/
void GFXiCanvas::makeHTMLPalette(){
  setColor(html_BLACK,BLACK);
  setColor(html_WHITE,WHITE);
  if(this->_depth>1){
    setColor(html_INDIANRED,INDIANRED);
    setColor(html_LIGHTCORAL,LIGHTCORAL);
  }
  if(this->_depth>2){
    setColor(html_SALMON,SALMON);
    setColor(html_DARKSALMON,DARKSALMON);
    setColor(html_LIGHTSALMON,LIGHTSALMON);
    setColor(html_CRIMSON,CRIMSON);
  }
  if(this->_depth>2){
    setColor(html_RED,RED);
    setColor(html_FIREBRICK,FIREBRICK);
    setColor(html_DARKRED,DARKRED);
    setColor(html_PINK,PINK);
    setColor(html_LIGHTPINK,LIGHTPINK);
    setColor(html_HOTPINK,HOTPINK);
    setColor(html_DEEPPINK,DEEPPINK);
    setColor(html_MEDIUMVIOLETRED,MEDIUMVIOLETRED);
  }
  if(this->_depth>3){
    setColor(html_PALEVIOLETRED,PALEVIOLETRED);
    setColor(html_CORAL,CORAL);
    setColor(html_TOMATO,TOMATO);
    setColor(html_ORANGERED,ORANGERED);
    setColor(html_DARKORANGE,DARKORANGE);
    setColor(html_ORANGE,ORANGE);
    setColor(html_GOLD,GOLD);
    setColor(html_YELLOW,YELLOW);
    setColor(html_LIGHTYELLOW,LIGHTYELLOW);
    setColor(html_LEMONCHIFFON,LEMONCHIFFON);
    setColor(html_LIGHTGOLDENRODYELLOW,LIGHTGOLDENRODYELLOW);
    setColor(html_PAPAYAWHIP,PAPAYAWHIP);
    setColor(html_MOCCASIN,MOCCASIN);
    setColor(html_PEACHPUFF,PEACHPUFF);
    setColor(html_PALEGOLDENROD,PALEGOLDENROD);
    setColor(html_KHAKI,KHAKI);
  }
  if(this->_depth>4){
    setColor(html_DARKKHAKI,DARKKHAKI);
    setColor(html_LAVENDER,LAVENDER);
    setColor(html_THISTLE,THISTLE);
    setColor(html_PLUM,PLUM);
    setColor(html_VIOLET,VIOLET);
    setColor(html_ORCHID,ORCHID);
    setColor(html_FUCHSIA,FUCHSIA);
    setColor(html_MAGENTA,MAGENTA);
    setColor(html_MEDIUMORCHID,MEDIUMORCHID);
    setColor(html_MEDIUMPURPLE,MEDIUMPURPLE);
    setColor(html_REBECCAPURPLE,REBECCAPURPLE);
    setColor(html_BLUEVIOLET,BLUEVIOLET);
    setColor(html_DARKVIOLET,DARKVIOLET);
    setColor(html_DARKORCHID,DARKORCHID);
    setColor(html_DARKMAGENTA,DARKMAGENTA);
    setColor(html_PURPLE,PURPLE);
    setColor(html_INDIGO,INDIGO);
    setColor(html_SLATEBLUE,SLATEBLUE);
    setColor(html_DARKSLATEBLUE,DARKSLATEBLUE);
    setColor(html_MEDIUMSLATEBLUE,MEDIUMSLATEBLUE);
    setColor(html_GREENYELLOW,GREENYELLOW);
    setColor(html_CHARTREUSE,CHARTREUSE);
    setColor(html_LAWNGREEN,LAWNGREEN);
    setColor(html_LIME,LIME);
    setColor(html_LIMEGREEN,LIMEGREEN);
    setColor(html_PALEGREEN,PALEGREEN);
    setColor(html_LIGHTGREEN,LIGHTGREEN);
    setColor(html_MEDIUMSPRINGGREEN,MEDIUMSPRINGGREEN);
    setColor(html_SPRINGGREEN,SPRINGGREEN);
    setColor(html_MEDIUMSEAGREEN,MEDIUMSEAGREEN);
    setColor(html_SEAGREEN,SEAGREEN);
    setColor(html_FORESTGREEN,FORESTGREEN);
  }
  if(this->_depth>5){
    setColor(html_GREEN,GREEN);
    setColor(html_DARKGREEN,DARKGREEN);
    setColor(html_YELLOWGREEN,YELLOWGREEN);
    setColor(html_OLIVEDRAB,OLIVEDRAB);
    setColor(html_OLIVE,OLIVE);
    setColor(html_DARKOLIVEGREEN,DARKOLIVEGREEN);
    setColor(html_MEDIUMAQUAMARINE,MEDIUMAQUAMARINE);
    setColor(html_DARKSEAGREEN,DARKSEAGREEN);
    setColor(html_LIGHTSEAGREEN,LIGHTSEAGREEN);
    setColor(html_DARKCYAN,DARKCYAN);
    setColor(html_TEAL,TEAL);
    setColor(html_AQUA,AQUA);
    setColor(html_CYAN,CYAN);
    setColor(html_LIGHTCYAN,LIGHTCYAN);
    setColor(html_PALETURQUOISE,PALETURQUOISE);
    setColor(html_AQUAMARINE,AQUAMARINE);
    setColor(html_TURQUOISE,TURQUOISE);
    setColor(html_MEDIUMTURQUOISE,MEDIUMTURQUOISE);
    setColor(html_DARKTURQUOISE,DARKTURQUOISE);
    setColor(html_CADETBLUE,CADETBLUE);
    setColor(html_STEELBLUE,STEELBLUE);
    setColor(html_LIGHTSTEELBLUE,LIGHTSTEELBLUE);
    setColor(html_POWDERBLUE,POWDERBLUE);
    setColor(html_LIGHTBLUE,LIGHTBLUE);
    setColor(html_SKYBLUE,SKYBLUE);
    setColor(html_LIGHTSKYBLUE,LIGHTSKYBLUE);
    setColor(html_DEEPSKYBLUE,DEEPSKYBLUE);
    setColor(html_DODGERBLUE,DODGERBLUE);
    setColor(html_CORNFLOWERBLUE,CORNFLOWERBLUE);
    setColor(html_ROYALBLUE,ROYALBLUE);
    setColor(html_BLUE,BLUE);
    setColor(html_MEDIUMBLUE,MEDIUMBLUE);
    setColor(html_DARKBLUE,DARKBLUE);
    setColor(html_NAVY,NAVY);
    setColor(html_MIDNIGHTBLUE,MIDNIGHTBLUE);
    setColor(html_CORNSILK,CORNSILK);
    setColor(html_BLANCHEDALMOND,BLANCHEDALMOND);
    setColor(html_BISQUE,BISQUE);
    setColor(html_NAVAJOWHITE,NAVAJOWHITE);
    setColor(html_WHEAT,WHEAT);
    setColor(html_BURLYWOOD,BURLYWOOD);
    setColor(html_TAN,TAN);
    setColor(html_ROSYBROWN,ROSYBROWN);
    setColor(html_SANDYBROWN,SANDYBROWN);
    setColor(html_GOLDENROD,GOLDENROD);
    setColor(html_DARKGOLDENROD,DARKGOLDENROD);
    setColor(html_PERU,PERU);
    setColor(html_CHOCOLATE,CHOCOLATE);
    setColor(html_SADDLEBROWN,SADDLEBROWN);
    setColor(html_SIENNA,SIENNA);
    setColor(html_BROWN,BROWN);
    setColor(html_MAROON,MAROON);
    setColor(html_SNOW,SNOW);
    setColor(html_HONEYDEW,HONEYDEW);
    setColor(html_MINTCREAM,MINTCREAM);
    setColor(html_AZURE,AZURE);
    setColor(html_ALICEBLUE,ALICEBLUE);
    setColor(html_GHOSTWHITE,GHOSTWHITE);
    setColor(html_WHITESMOKE,WHITESMOKE);
    setColor(html_SEASHELL,SEASHELL);
    setColor(html_BEIGE,BEIGE);
    setColor(html_OLDLACE,OLDLACE);
    setColor(html_FLORALWHITE,FLORALWHITE);
    setColor(html_IVORY,IVORY);
  }
  if(this->_depth>6){
    setColor(html_ANTIQUEWHITE,ANTIQUEWHITE);
    setColor(html_LINEN,LINEN);
    setColor(html_LAVENDERBLUSH,LAVENDERBLUSH);
    setColor(html_MISTYROSE,MISTYROSE);
    setColor(html_GAINSBORO,GAINSBORO);
    setColor(html_LIGHTGRAY,LIGHTGRAY);
    setColor(html_SILVER,SILVER);
    setColor(html_DARKGRAY,DARKGRAY);
    setColor(html_GRAY,GRAY);
    setColor(html_DIMGRAY,DIMGRAY);
    setColor(html_LIGHTSLATEGRAY,LIGHTSLATEGRAY);
    setColor(html_SLATEGRAY,SLATEGRAY);
    setColor(html_DARKSLATEGRAY,DARKSLATEGRAY);
  }
}

/**************************************************************************/
/*!
  @brief    draw an iCanvas buffer on screen
  @param    x,y position on screen 
  @param    x0,y0 starting position in canvas for partial redraw
  @param    width,height size of partial redraw rect
  @param    *display display to draw on
  @remark   only calls quickDraw
*/
/**************************************************************************/
void GFXiCanvas::draw(int16_t x, int16_t y, Adafruit_GFX *display, int16_t x0, int16_t y0, int16_t width, int16_t height){
  // partial redraw for the rect starting at x0, y0 with width and height
  QuickDraw(x, y, display, x0, y0, width, height);
}

/**************************************************************************/
/*!
  @brief    draw an iCanvas buffer on screen
  @param    x,y position on screen 
  @param    *display display to draw on
  @remark   calls quickDraw with the full canvas size, effectively a full redraw
*/
/**************************************************************************/
void GFXiCanvas::draw(int16_t x, int16_t y, Adafruit_GFX *display){
  // full redraw
  //Serial.printf("starting quickDraw with x: %i, y: %i, w: %i, h: %i\n",x,y,this->_width, this->_height);
  QuickDraw(x, y, display, (uint16_t)0, (uint16_t)0, this->_width, this->_height);
}

/**************************************************************************/
/*!
  @brief    draw an iCanvas buffer on screen
  @param    x0,y0 position on screen 
  @param    x1,y1 starting position in canvas for partial redraw
  @param    width,height size of partial redraw rect
  @param    *display display to draw on
  @remark   draws the iCanvas buffer onto the given screen, requiring a 24 bit
            capabale Adafruit-GFX version
            This routine tries to be smart about what to actually draw 
            and collects runs of the same color to then draw a 
            fastVline/fastHline. For that, it will use _textHint. If textHint 
            is true, we'll have a preference for drawing horizontally, 
            otherwise we'll draw vertically. The assumption is, that text
            will have longer horizontal (blank) pixel lines.
*/
/**************************************************************************/

/**************************************************************************/
/* Drawing on screen:                                                     */
/* x_pos, y_pos should always refer to the top left corner                */
/* canvas shall be rotated position*90° (0, 90, 180, 270) while drawing   */
/* the quickDraw functions (longest runs) have to be rotated as well      */
/* translation and rotation therefore have to be decoupled                */
/**************************************************************************/
void GFXiCanvas::QuickDraw(int16_t x_pos, int16_t y_pos, Adafruit_GFX *display, int16_t x0, int16_t y0, int16_t w, int16_t h){
  uint8_t c;
  int16_t pos,t; 

  uint16_t xs=x_pos+x0;
  uint16_t ys=y_pos+y0;
  //Serial.printf("rQuickDraw: rotation: %i\n",this->_rotation);
  
  if(w>=h || _textHint){
    for (int16_t y=0;y<h;y++){
      for (int16_t x=0;x<w;){ 
        pos=0;
        c=this->getPixelColorIndex(x0+x,y0+y);
        if(!(_useTransparency && c==_transparent)){
          while(x+pos<=w && this->getPixelColorIndex(x0+x+pos++, y0+y)==c);
          pos--; //pos will always overshoot by 1
          drawSegment(x_pos, y_pos, display, x+x0, y+y0, getColor(c),pos,DIR_HORIZONTAL);
          x+=pos;
        }else{
          x++;
        }
      }
    }
  }else{
    for (int16_t x=0;x<w;x++){
      for (int16_t y=0;y<h;){
        pos=0;
        c=this->getPixelColorIndex(x0+x,y0+y);
        if(!(_useTransparency && c==_transparent)){
          while(y+pos<=h && this->getPixelColorIndex(x0+x, y0+y+pos++)==c);
          pos--;//pos will always overshoot by 1
          drawSegment(x_pos,y_pos, display, x+x0, y+y0, getColor(c),pos,DIR_VERTICAL);
          y+=pos;
        }else{
          y++;
        }
      }
    }
  }
  //Serial.printf("display->drawCircle(%i,%i,2,WHITE);\n",x_pos,y_pos);
  //display->drawCircle(x_pos,y_pos,3,(uint16_t)0xffff);
}

/**************************************************************************/
/*!
  @brief    drawSegment is used to draw a partial from a canvas to a 
            Adafruit-GFX display (which might in turn be another canvas)
            It's focussing on a single rect which may be a sub portion of 
            the canvas
  @param    x0, y0: on screen position
            *display pointer to the display object
            x, y: start of the the segment within the rect to draw
            c 24 bit color (color24)
            length length of the segment
            direction either DIR_HORIZONTAL or DIR_VERTICAL - drawing direction
   @remark  This will obey the rotation state of the current canvas and
            rotate the segment accordingly. Uses _rotation, _width and _height
            from the current object
*/
/**************************************************************************/
void GFXiCanvas::drawSegment(int16_t x0, int16_t y0, Adafruit_GFX *display, int16_t x, int16_t y, color24 c, int16_t length, bool direction){
  uint16_t t;
  //Serial.printf("drawComponent: x0: %03i, y0: %03i, x: %03i, y:%03i, length: %03i, w: %03i, h: %03i, rot: %i\n",x0,y0,x,y,length,this->_width,this->_height,this->_rotation);
  switch(this->_rotation) {
    case 1:
      t = x;
      x = this->_height  - 1 - y;
      y = t;
      direction=!direction; //horizontal becomes vertical and vice versa
      if(direction==DIR_HORIZONTAL) x-=length; //if a positive 180° vector is rotated 90° it becomes a negative 270° vector, thus we turn it around and move the starting x coordinate
      break;
    case 2:
      x = this->_width  - 1 - x;
      y = this->_height - 1 - y;
      direction==DIR_HORIZONTAL?x-=length:y-=length; //flip the direction 180°
      break;
    case 3:
      t = x;
      x = y;
      y = this->_width - 1 - t;
      direction=!direction; //horizontal becomes vertical and vice versa
      if(direction==DIR_VERTICAL) y-=length; //if a positive 90° vector is rotated 270° it becomes a negative 0° vector, thus we turn it around and move the starting y coordinate
      break;
  }
  if(length==1){
    display->drawPixel(x0+x,y0+y,c);
  }else{
    direction==DIR_VERTICAL?display->drawFastVLine(x0+x,y0+y,length,c):display->drawFastHLine(x0+x,y0+y,length,c);
  }
}

/**************************************************************************/
/*!
  @brief    return the pointer to the buffer for the given bitplane
  @param    plane Number of the bitplane to get the pointer to 
            (starting with 0)
  @returns  a pointer to a memory area. Be careful
*/
/**************************************************************************/
uint8_t *GFXiCanvas::getBuffer(uint8_t plane){
  if(plane>=0 && plane<this->_depth){
    return this->bitplane.at(plane)->getBuffer();
  }else{
    _last_ERR=ERR_OUTOFRANGE;
    return 0;
  }
}

/**************************************************************************/
/*!
  @brief  clear the canvas
*/
/**************************************************************************/
void GFXiCanvas::clearDisplay(){
  for(uint8_t i=0;i<this->_depth;i++){
    this->bitplane.at(i)->clearDisplay();
  }
}

/**************************************************************************/
/*!
  @brief  set the _textHint flag
  @param  h boolean for _textHint, true means treat this as text.
  @remark please see the description for quickDraw
*/
/**************************************************************************/
void GFXiCanvas::setTextHint(bool h){
  _textHint=h;
}

/**************************************************************************/
/*!
  @brief    return last error
  @returns  last error set internally
  @remark   This library tries to provide error codes for internal states
            Mainly, those are currently out of error and invalid index 
            conditions, but might be more in the future. Member functions
            in this class should clear _last_ERR upon entrance and then
            set it accordingly before exiting.
            The calling probram can then call getLastError() to get that
            value.
*/
/**************************************************************************/
uint8_t GFXiCanvas::getLastError(){
  return this->_last_ERR;
}

/**************************************************************************/
/*!
  @brief    dump the compounded canvas bitmap to serial
  @remark   This function creates a hex dump of the effective values for 
            the combined bitplanes and prints it to the usb_serial_class
            device. This device is the weakest point of this function,
            as it is not defined for every Arduino core (the initial 
            code was written for and tested on a Teensy)
*/
/**************************************************************************/
void GFXiCanvas::dump(usb_serial_class *s){
  if(&s){
    s->printf("dumping canvas\n==============\nwidth : %.4i\nheight: %.4i\ndepth : %.4i\nrotation: %i\n\n",this->_width, this->_height,this->_depth,this->_rotation);
    s->printf("Palette positions: %i\n", 1<<this->_depth);
    for(uint8_t i=0;i<1<<this->_depth;i++){
      s->printf("[%02i]: (%03i, %03i, %03i)\n",i,this->palette.at(i).r,this->palette.at(i).g,this->palette.at(i).b );
    }

    s->printf("\n      ");
    for (int16_t i=0;i<this->_width;i++){
      s->printf("%02i ",i);
    }
    s->printf("\n      ");
    for (int16_t i=0;i<this->_width;i++){
      s->printf("---");
    }

    s->printf("\n");
    for (int16_t y=0;y<this->_height;y++){
      s->printf("%04i:",y);
      for (int16_t x=0;x<this->_width;x++){

        s->printf(" %02x",this->getPixelColorIndex(x,y));
      }
      s->printf("\n");
    }
  }
}
