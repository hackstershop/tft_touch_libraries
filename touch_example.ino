
#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <Adafruit_TFTLCD.h>
#include <Wire.h>


#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin
#define DHTPIN 11
#define DHTTYPE DHT11   // DHT 11
// calibration mins and max for raw data when touching edges of screen
// YOU CAN USE THIS SKETCH TO DETERMINE THE RAW X AND Y OF THE EDGES TO GET YOUR HIGHS AND LOWS FOR X AND Y
#define TS_MINX 210
#define TS_MINY 210
#define TS_MAXX 915
#define TS_MAXY 910

//SPI Communication
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

//Color Definitons
#define BLACK     0x0000 

#define RED      0x001F
#define GREY      0xCE79
#define LIGHTGREY 0xDEDB
#define BLUE     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MINPRESSURE 1
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 330);

//2.4 = 240 x 320
//Height 319 to fit on screen

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


int X,Y;
boolean BUTTON = false;



void setup() {
  Serial.begin(9600);
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.setRotation(3);
  
  //Background color
  tft.fillScreen(BLUE);
  tft.drawPixel(5, 5, WHITE);
  tft.drawLine(50, 50, 100, 50, WHITE);  

  tft.drawRect(20, 100, 100, 50, WHITE);
  //tft.fillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);

  tft.drawCircle(200, 160, 50, WHITE);
  tft.fillCircle(200, 160, 50, WHITE);

  
  tft.setTextColor(WHITE, BLUE);
  tft.setTextSize(2);
  tft.setCursor(40, 120);
  tft.print("Touch");

  
}

void loop() {
  
 digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  //If sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  Y = map(p.x, TS_MAXX, TS_MINX, 0, tft.width());
  X = map(p.y, TS_MAXY, TS_MINY, 0, tft.height());
    
  if(p.z > 0 ){ // if pressure
    Serial.println(X);
    Serial.println(Y);
    Serial.println("------");
    //delay(100);
    if ( X > 20 && X < 100 && Y > 150 && Y < 250){
        BUTTON = !BUTTON;
        delay(200);
       
      }
     if ( BUTTON){
        tft.drawRect(20, 100, 100, 50, MAGENTA);
        tft.fillCircle(200, 160, 50, MAGENTA);
      }
      else{
        tft.drawRect(20, 100, 100, 50, WHITE);
        tft.fillCircle(200, 160, 50, WHITE);

        }


    
   

   } 

} 
