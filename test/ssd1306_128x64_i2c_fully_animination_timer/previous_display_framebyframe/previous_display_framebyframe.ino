/**************************************************************************
  This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

  This example is for a 128x64 pixel display using I2C to communicate
  3 pins are required to interface (two I2C and one reset).

  Adafruit invests time and resources providing this open
  source code, please support Adafruit and open-source
  hardware by purchasing products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries,
  with contributions from the open source community.
  BSD license, check license.txt for more information
  All text above, and the splash screen below must be
  included in any redistribution.
 **************************************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bmp_frames.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32 mine 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define frames     58 // Number of frame in the animation example

#define LOGO_WIDTH    64
#define LOGO_HEIGHT   64
int frame = 0;
#define delay_time  50000 // 50 ms

hw_timer_t * timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile uint32_t isrCounter = 0;
volatile uint32_t lastIsrAt = 0;

void ARDUINO_ISR_ATTR onTimer() 
{
  // Increment the counter and set the time of ISR
  portENTER_CRITICAL_ISR(&timerMux);
  isrCounter++;
  lastIsrAt = millis();
  portEXIT_CRITICAL_ISR(&timerMux);
  // Give a semaphore that we can check in the loop
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
  // It is safe to use digitalRead/Write here if you want to toggle an output
}




void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Create semaphore to inform us when the timer has fired
  timerSemaphore = xSemaphoreCreateBinary();

  // Use 1st timer of 4 (counted from zero).
  // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
  // info).
  timer = timerBegin(0, 80, true);

  // Attach onTimer function to our timer.
  timerAttachInterrupt(timer, &onTimer, true);

  // Set alarm to call onTimer function every second (value in microseconds).
  // Repeat the alarm (third parameter)
  timerAlarmWrite(timer, delay_time, true); // 1000000 = 1 second

  // Start an alarm
  timerAlarmEnable(timer);

}



void loop()
{

//  display.clearDisplay();
 // stream();
//  frame = 0;

  if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE) 
  {
    uint32_t isrCount = 0, isrTime = 0;
    // Read the interrupt count and time
    portENTER_CRITICAL(&timerMux);
    isrCount = isrCounter;
    isrTime = lastIsrAt;
    portEXIT_CRITICAL(&timerMux);
    // Print it
    Serial.print("onTimer no. ");
    Serial.print(isrCount);
    Serial.print(" at ");
    Serial.print(isrTime);
    Serial.println(" ms");
    
    display.clearDisplay();
    framebyframe(frame); // every 50ms refresh a frame
    frame++;

    if (frame == frames)
    {
      frame = 0;
    }

  }

}



void framebyframe(int frame)
{
  switch (frame)
  {
    case 0:
      f0();
      break;
    case 1:
      f1();
      break;
    case 2:
      f2();
      break;
    case 3:
      f3();
      break;
    case 4:
      f4();
      break;
    case 5:
      f5();
      break;
    case 6:
      f6();
      break;
    case 7:
      f7();
      break;
    case 8:
      f8();
      break;
    case 9:
      f9();
      break;
    case 10:
      f10();
      break;
    case 11:
      f11();
      break;
    case 12:
      f12();
      break;
    case 13:
      f13();
      break;
    case 14:
      f14();
      break;
    case 15:
      f15();
      break;
    case 16:
      f16();
      break;
    case 17:
      f17();
      break;
    case 18:
      f18();
      break;
    case 19:
      f19();
      break;
    case 20:
      f20();
      break;
    case 21:
      f21();
      break;
    case 22:
      f22();
      break;
    case 23:
      f23();
      break;
    case 24:
      f24();
      break;
    case 25:
      f25();
      break;
    case 26:
      f26();
      break;
    case 27:
      f27();
      break;
    case 28:
      f28();
      break;
    case 29:
      f29();
      break;
    case 30:
      f30();
      break;
    case 31:
      f31();
      break;
    case 32:
      f32();
      break;
    case 33:
      f33();
      break;
    case 34:
      f34();
      break;
    case 35:
      f35();
      break;
    case 36:
      f36();
      break;
    case 37:
      f37();
      break;
    case 38:
      f38();
      break;
    case 39:
      f39();
      break;
    case 40:
      f40();
      break;
    case 41:
      f41();
      break;
    case 42:
      f42();
      break;
    case 43:
      f43();
      break;
    case 44:
      f44();
      break;
    case 45:
      f45();
      break;
    case 46:
      f46();
      break;
    case 47:
      f47();
      break;
    case 48:
      f48();
      break;
    case 49:
      f49();
      break;
    case 50:
      f50();
      break;
    case 51:
      f51();
      break;
    case 52:
      f52();
      break;
    case 53:
      f53();
      break;
    case 54:
      f54();
      break;
    case 55:
      f55();
      break;
    case 56:
      f56();
      break;
    case 57:
      f57();
      break;
    case 58:
      f58();
      break;


  }

}


void f0(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1); // display.drawBitmap(width position, height position, picture, picture width, picture height, none use)
  display.display();

}
void f1(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp1, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();

}
void f2(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp2, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();

}

void f3(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp3, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();

}

void f4(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp4, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f5(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp5, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f6(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp6, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f7(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp7, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f8(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp8, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f9(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp9, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f10(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp10, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f11(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp11, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f12(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp12, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f13(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp13, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f14(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp14, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f15(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp15, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f16(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp16, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f17(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp17, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f18(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp18, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f19(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp19, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f20(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp20, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f21(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp21, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f22(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp22, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f23(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp23, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f24(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp24, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f25(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp25, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f26(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp26, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f27(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp27, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f28(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp28, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f29(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp29, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f30(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp30, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f31(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp31, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f32(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp33, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f33(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp33, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f34(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp34, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f35(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp35, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f36(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp36, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f37(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp37, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f38(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp38, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f39(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp39, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f40(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp40, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f41(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp41, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f42(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp42, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f43(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp43, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f44(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp44, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f45(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp45, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f46(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp46, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f47(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp47, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f48(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp48, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f49(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp49, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f50(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp50, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f51(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp51, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f52(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp52, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f53(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp53, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f54(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp54, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}


void f55(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp55, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f56(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp56, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}


void f57(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp57, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}

void f58(void)
{
  display.drawBitmap((display.width() - LOGO_WIDTH) / 2, 0, logo_bmp58, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}
