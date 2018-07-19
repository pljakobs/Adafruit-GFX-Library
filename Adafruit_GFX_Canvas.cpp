#include "Adafruit_GFX-Canvas.h"
#ifdef __AVR__
  #include <avr/pgmspace.h>
#elif defined(ESP8266) || defined(ESP32)
  #include <pgmspace.h>
#endif
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
   @brief    Instatiate a GFX 1-bit canvas context for graphics
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

        uint8_t   *ptr  = &buffer[(x / 8) + y * ((WIDTH + 7) / 8)];
#ifdef __AVR__
        c = *ptr & pgm_read_byte(&GFXsetBit[x & 7]);
#else
        c = *ptr & 0x80>>(x & 7);
#endif
      //Serial.printf("getPixel x: %i, y: %i, byte: %02x, mask: %02x, c: %i\n",x,y,*ptr, 0x80>>(x % 7),c);
      return c;
    }
    else{
      return false;
    }
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

GFXiCanvas::GFXiCanvas(int16_t _width, int16_t _height, uint8_t _depth):Adafruit_GFX(width, height){
  width=_width;
  height=_height;
  depth=_depth;
  /*
   * depth is depth in bits, not number of colors!
   * it has to be larger than 1 and smaller or equal 8,
   * single bit bitplanes should use GFXcanvas1, 8bpp can
   * alternatively use GFXCanvas8, although I'm not quite
   * sure how that handles colors (assigns 16 Bit color to
   * 8Bit memory cell?)
   *
   * Any iCanvas object will have a palette assigned to it that
   * is used to map color numbers derived from the bitplanes to
   * the actual 16 or 24 bit (565 or 888) color value
   *
   * the layout in memory will be like this for an iCanvas of depth 4
   *
   * bitplane[0] *GFXCanvas1 <Bit 0: 1 0 1 1 0 0 0 1>
   * bitplane[1] *GFXCanvas1 <Bit 1: 0 0 0 1 0 1 1 1>
   * bitplane[2] *GFXCanvas1 <Bit 2: 0 1 0 0 0 0 0 1>
   * bitplane[3] *GFXCanvas1 <Bit 3: 1 1 0 0 1 0 0 0>
   *                                 ---------------
   *                resulting color: 5 C 1 3 8 2 2 7
   *
   * palette[0]=color24{r,g,b};
   * palette[1]=color24{r,g,b};
   * palette[2]=color24{r,g,b};
   *      .
   *      .
   *      .
   * palette[F]=color24{r,g,b};
   */
   Serial.printf("\n>>>>>>>>>>>>>>>>>>>>>\n\n intializing canvas\nwidth:  %i\nheight: %i\ndepth:  %i\n\n",width, height, depth);
  if(depth <=8 && depth >=1){
    uint8_t numColors = 1<<depth;
    palette.reserve(numColors);
    //Serial.printf("struct palette: sizeof(palette[0].r)=%i, sizeof(palette[0].g)=%i, sizeof(palette[0].b)=%i\n",sizeof(palette[0].r),sizeof(palette[0].g),sizeof(palette[0].b));
    bitplane.reserve(depth);
    //GFXcanvas1 *bitplane = new *GFXcanvas1[depth];
    //palette ) new color24[numColors];
    //GFXcanvas1 *bitplane[depth];
    //color24 palette[numColors];
    for( uint8_t i=0;i<depth;i++){
      bitplane.push_back(new GFXcanvas1(width, height)); //Todo needs error handling if one bitplane cannot be allocated
      Serial.printf("initialized bitplane[%i] at %i\n",i,bitplane.at(i)->getBuffer());
    }
    Serial.printf("created bitplanes\n=================\n");
    /*
     * set default palettes (up to 32 colors, anything above that will always be free)
     */
    Serial.printf("initializing palette for %i colors\nvector has a size of %i(%i)\n",numColors,palette.capacity(),sizeof(palette[0]));
    for(uint8_t n=0;n<numColors;n++){
      palette.push_back({.r=0,.g=0,.b=0});
    }
    switch (depth) {
      case 1:
        palette.at(0)={.r=  0, .g=  0, .b=  0};
        palette.at(1)={.r=  0, .g=  0, .b= 16}; //ssd1306 LCDs need uint16_t 1 to draw pixsel
        break;
      case 2:
        palette.at(0)={.r=  0, .g=  0, .b=  0};
        palette.at(1)={.r=255, .g=255, .b=255};
        palette.at(2)={.r=255, .g=  0, .b=  0};
        palette.at(3)={.r=255, .g=255, .b=  0};
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
  }
  Serial.printf("GFXiCanvas consturctur finished\ncreated %i bitplanes and %i palette positions\n\n>>>>>>>>>>>>>>>>>>>>>\n",bitplane.capacity(), palette.capacity());
}

GFXiCanvas::~GFXiCanvas(){
  Serial.printf("\n>>>>>>>>>>>>>>>>>>>>>\n\ndeleting canvas\nwidth:  %i\nheight: %i\ndepth:  %i\n\n",width, height, depth);
  for(uint8_t i=0;i<this->depth;i++){
    delete this->bitplane.at(i);
  }
  bitplane.clear();
  palette.clear();
  Serial.printf("\n exit destructor\n\n>>>>>>>>>>>>>>>>>>>>>\n");
}

uint8_t GFXiCanvas::getDepth(){
  return this->depth;
}

void GFXiCanvas::drawPixel(int16_t x, int16_t y, uint8_t colorIndex){
  if(colorIndex<(1<<this->depth)){
    //Serial.printf("drawing pixel at x:%i, y:%i\n",x,y);
    for(uint8_t i=0;i<this->depth;i++) {
      //Serial.printf("bitplane:%i, val:%i\n",i,(colorIndex && 1<<i));
      this->bitplane.at(i)->drawPixel(x,y,(colorIndex && (1<<i)));
      }
  }
}

void GFXiCanvas::drawPixel(int16_t x, int16_t y, uint16_t colorIndex){
  uint8_t c=(uint8_t)(colorIndex&0xff);
  drawPixel(x,y,c);
}

color24 GFXiCanvas::getColor(uint8_t i){
  if(i<(1<<this->depth)){
    return this->palette.at(i);
  }else{
    return (color24){0,0,0};
  }
}

void GFXiCanvas::setColor(uint8_t i, color24 c){
  if(i<(1<<this->depth)){
    this->palette.at(i)=c;
  }
}

uint8_t GFXiCanvas::getPixelColorIndex(int16_t x, int16_t y){
  uint8_t c=0;
  //Serial.printf("getPixelColorIndex x:%i, y:%i [",x,y);
  for(uint8_t i=0;i<this->depth;i++) {
      //Serial.printf("%i",this->bitplane.at(i)->getPixel(x,y));
      c|=(this->bitplane.at(i)->getPixel(x,y)&&0x01)<<i;
  }
  //Serial.printf("] c:%i\n",c)
  ;
  return c;
}

color24 GFXiCanvas::getPixel24(int16_t x, int16_t y) {
  return getColor(getPixelColorIndex(x,y));
}

uint16_t GFXiCanvas::getPixel565(int16_t x, int16_t y) {
  color24 color;
  color = getPixel24(x,y);
  uint16_t c;
  //Serial.printf("getPixel656, x:%i, y:%i, r=%i, g=%i, b=%i\n",x,y,color.r,color.g,color.b);
  c=(color.r & 0xF8) << 8 | (color.g & 0xFC) << 3 | (color.b & 0xF8) >> 3;
  return c;
}

void GFXiCanvas::draw(int16_t x0, int16_t y0, Adafruit_GFX *display){
  for (int16_t y=0;y<this->height;y++){
    for (int16_t x=0;x<this->width;x++){
      display->drawPixel(x0+x, y0+y, this->getPixel565(x,y));
    }
  }
}

uint8_t *GFXiCanvas::getBuffer(uint8_t plane){
  if(plane>=0 && plane <this->depth){
    return this->bitplane.at(plane)->getBuffer();
  }
}

void GFXiCanvas::clearDisplay(){
  for(uint8_t i=0;i<this->depth;i++){
    this->bitplane.at(i)->clearDisplay();
  }
}
