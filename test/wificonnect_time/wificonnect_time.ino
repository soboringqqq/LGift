#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include "time.h"
#include "sntp.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define delay_time  1000000 // 1s

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



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

const char* ntpServer1 = "s1c.time.edu.cn";
const char* ntpServer2 = "s2f.time.edu.cn";
const long  gmtOffset_sec = 28800;
const int   daylightOffset_sec = 0;
int H = 0;
int H_pre = 0;
int M = 0;
int M_pre = 0; 
int S = 0;
int S_pre = 0;
int flag = 0;
int diffS = 0;
char buf[50];
//const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)


void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  H = int(timeinfo.tm_hour);
  M = int(timeinfo.tm_min); // extract value from char* to int
  S = int(timeinfo.tm_sec); // extract value from char* to int
  //timeinfo.tm_sec =+ 10;
  //Serial.println(H);
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  //Serial.println(&timeinfo, "%H:%M:%S");
  // H = int(&timeinfo, "%H");
  // Serial.println(H);
 // display.clearDisplay();
 // display.setTextSize(2);             // Normal 1:1 pixel scale
  //display.setTextColor(SSD1306_WHITE);        // Draw white text
 // display.setCursor(20,32);             // Start at middle
 // display.println(&timeinfo, "%H:%M:%S");
  //display.display();

  

}

// Callback function (get's called when time adjusts via NTP)
void timeavailable(struct timeval *t)
{
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}


void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
  delay(2000);
}


void setup() {
    // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

    // put your setup code here, to run once:
    Serial.begin(115200);

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

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
    }
  
    display.display();
    delay(2000); // Pause for 2 seconds

    // Clear the buffer
    display.clearDisplay();
    
    sntp_set_time_sync_notification_cb( timeavailable );
    //sntp_servermod e_dhcp(1);   // (optional)
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result



    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("AutoConnectAP","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }

    printLocalTime();

}

void loop() {
  
    // delay(5000);
    //printLocalTime(); 
    //Serial.println(M);
    //testdrawstyles();

   

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

    if(flag == 0)
    {
      printLocalTime();
      H_pre = H;
      M_pre = M;
      S_pre = S;
      flag = 1;
    }

    S_pre++;

    if(S_pre == 60)
      {
        M += 1;
        S_pre = 0;
      }

    if(M == 60)
      {
        H += 1;
        M = 0;
      }

    if(H == 24)
      {
        H = 0;
        M = 0;
        S = 0;
      }

    diffS = abs(M_pre - M);
    if(diffS > 30 )
    {
      flag = 0;
    }

    sprintf(buf, "%02d:%02d:%02d ", H, M, S_pre);
    
//    Serial.print(H);
//    Serial.print(":");
//    Serial.print(M);
//    Serial.print(":");
//    Serial.print(S_pre);

    Serial.print(buf);
    display.clearDisplay();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(20,32);             // Start at middle
//    display.print(H);
//    display.setCursor(60,32);             // Start at middle
//    display.print(M);
//    display.setCursor(90,32);             // Start at middle
    display.println(buf);
    display.display();

    //printLocalTime();

  }

}
