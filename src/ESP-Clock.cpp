//#include <WiFi.h>   //esp32
#include <SPIFFS.h>
//#include <string.h>
#include <WiFiSettings.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
//#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//#define CONFIG_PIN  27 // ESP32 pin GIOP27 Pressed by Power ON dissconnect from Router and starts the Config-AP!!!
#define CONFIG_PIN  27 // ESP32 pin GIOP27 Pressed by Power ON dissconnect from Router and starts the Config-AP!!!

#define SENSOR_PIN  18 // ESP32 pin GIOP21 connected to DS18B20 sensor's DQ pin

//#define SERIAL_DEBUG_MODE true
// Status LED


const uint32_t LED_PIN = 2;
#define LED_ON  LOW
#define LED_OFF HIGH

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);
float tempC; // temperature in Celsius
float tempF; // temperature in Fahrenheit

const int BUTTON_PIN = 17;

int lastState = HIGH; // the previous state from the input pin
int currentState;    // the current reading from the input pin
int onoff = 1; //leds by start on
const int RELAY_PIN = 22;  // the Arduino pin, which connects to the IN pin of relay
int NTP_UPDATE_SEKUNDEN = 3600; // 3600 = 1 Stunde
int data_update = 0;
int data_epoch = 0;
int next_update = 0;
int interval1_update = 0;
int interval1_epoch = 0;
int next_interval1_update = 0;
int interval2_update = 0;
int interval2_epoch = 0;
int next_interval2_update = 0;
int interval3_update = 0;
int interval3_epoch = 0;
int next_interval3_update = 0;
int interval4_update = 0;
int interval4_epoch = 0;
int next_interval4_update = 0;

//#define RGB_PIN        16
//#define NUMPIXELS 118
#define NUM_LEDS 118
#define DATA_PIN 16
CRGB leds[NUM_LEDS];
//#define FRAMES_PER_SECOND  1000


#define IR_RECEIVE_PIN 21
#define IR_FEEDBACK_LED_PIN 2


#include <IRremote.hpp>
#include <TinyIRReceiver.hpp>

//Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);
//#define DELAYVAL 50

//Zeitverschiebung UTC <-> MEZ (Winterzeit) = 3600 Sekunden (1 Stunde)
//Zeitverschiebung UTC <-> MEZ (Sommerzeit) = 7200 Sekunden (2 Stunden)
//const long utcOffsetInSeconds = 7200; //Sommerzeit
const long utcOffsetInSeconds = 3600; //Winterzeit
int MEZ = 0;
const int MySize = NUM_LEDS;
String MyArray[3][MySize];
int MyArray2[3];
String morevals;
//MyArray[0][30] = {{"leds[123].setRGB(123,123,123)"}}; 

char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
int blinker = 1;
String nightmode="no";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

int bright = 10; // gesamte Helligkeit
// 100% = 255
//  75% = 192
//  50% = 128
//  25% =  64
//  15% =  39 (Nightmode)

//int on = 255; // Helligkeit voll an
//int daymodeon = 255; // Helligkeit voll an
int on; // Helligkeit voll an
int daymodeon = 64; // Helligkeit voll an
int nightmodeon = 10; // Helligkeit im nachtmodus
int ledAddVal = 0;
int correct;
int correctd = 191;
int correctn = 20;

void zahlen(String night, String zahl1="8", String zahl2="8", String zahl3="8", String zahl4="8"){
if (night == "yes"){ on = nightmodeon; correct=correctn;}
if (night == "no"){ on = daymodeon; correct=correctd;}
if (zahl1 == "0"){
    leds[0].setRGB(0,0,on+correct); 
    leds[1].setRGB(0,0,on); 
    leds[2].setRGB(0,0,on); 
    leds[3].setRGB(0,0,on); 
    leds[4].setRGB(0,0,on); 
    leds[5].setRGB(0,0,0); 
    leds[6].setRGB(0,0,on); 
    leds[7].setRGB(0,0,on); 
    leds[8].setRGB(0,0,0); 
    leds[9].setRGB(0,0,on); 
    leds[10].setRGB(0,0,on); 
    leds[11].setRGB(0,0,on); 
    leds[12].setRGB(0,0,on); 
    leds[13].setRGB(0,0,on); 
} else if (zahl1 == "1"){
    leds[0].setRGB(0,0,0); 
    leds[1].setRGB(0,0,0); 
    leds[2].setRGB(0,0,0); 
    leds[3].setRGB(0,0,0); 
    leds[4].setRGB(0,0,0); 
    leds[5].setRGB(0,0,0); 
    leds[6].setRGB(0,0,0); 
    leds[7].setRGB(0,0,0); 
    leds[8].setRGB(0,0,0); 
    leds[9].setRGB(0,0,0); 
    leds[10].setRGB(0,0,on); 
    leds[11].setRGB(0,0,on); 
    leds[12].setRGB(0,0,on); 
    leds[13].setRGB(0,0,on); 
} else if (zahl1 == "2"){
    leds[0].setRGB(0,0,0); 
    leds[1].setRGB(0,0,0); 
    leds[2].setRGB(0,0,on); 
    leds[3].setRGB(0,0,on); 
    leds[4].setRGB(0,0,on); 
    leds[5].setRGB(0,0,on); 
    leds[6].setRGB(0,0,on); 
    leds[7].setRGB(0,0,on); 
    leds[8].setRGB(0,0,on); 
    leds[9].setRGB(0,0,on); 
    leds[10].setRGB(0,0,0); 
    leds[11].setRGB(0,0,0); 
    leds[12].setRGB(0,0,on); 
    leds[13].setRGB(0,0,on); 
} else if (zahl1 == "3"){
    leds[0].setRGB(0,0,0); 
    leds[1].setRGB(0,0,0); 
    leds[2].setRGB(0,0,0); 
    leds[3].setRGB(0,0,0); 
    leds[4].setRGB(0,0,on); 
    leds[5].setRGB(0,0,on); 
    leds[6].setRGB(0,0,on); 
    leds[7].setRGB(0,0,on); 
    leds[8].setRGB(0,0,on); 
    leds[9].setRGB(0,0,on); 
    leds[10].setRGB(0,0,on); 
    leds[11].setRGB(0,0,on); 
    leds[12].setRGB(0,0,on); 
    leds[13].setRGB(0,0,on); 
} else if (zahl1 == "4"){
    leds[0].setRGB(0,0,on+correct); 
    leds[1].setRGB(0,0,on); 
    leds[2].setRGB(0,0,on); 
    leds[3].setRGB(0,0,on); 
    leds[4].setRGB(0,0,0); 
    leds[5].setRGB(0,0,on); 
    leds[6].setRGB(0,0,0); 
    leds[7].setRGB(0,0,0); 
    leds[8].setRGB(0,0,on); 
    leds[9].setRGB(0,0,0); 
    leds[10].setRGB(0,0,on); 
    leds[11].setRGB(0,0,on); 
    leds[12].setRGB(0,0,on); 
    leds[13].setRGB(0,0,on); 
} else if (zahl1 == "5"){
    leds[0].setRGB(0,0,on+correct); 
    leds[1].setRGB(0,0,on); 
    leds[2].setRGB(0,0,0); 
    leds[3].setRGB(0,0,0); 
    leds[4].setRGB(0,0,on); 
    leds[5].setRGB(0,0,on); 
    leds[6].setRGB(0,0,on); 
    leds[7].setRGB(0,0,on); 
    leds[8].setRGB(0,0,on); 
    leds[9].setRGB(0,0,on); 
    leds[10].setRGB(0,0,on); 
    leds[11].setRGB(0,0,on); 
    leds[12].setRGB(0,0,0); 
    leds[13].setRGB(0,0,0); 
} else if (zahl1 == "6"){
    leds[0].setRGB(0,0,on+correct); 
    leds[1].setRGB(0,0,on); 
    leds[2].setRGB(0,0,on); 
    leds[3].setRGB(0,0,on); 
    leds[4].setRGB(0,0,on); 
    leds[5].setRGB(0,0,on); 
    leds[6].setRGB(0,0,on); 
    leds[7].setRGB(0,0,on); 
    leds[8].setRGB(0,0,on); 
    leds[9].setRGB(0,0,on); 
    leds[10].setRGB(0,0,on); 
    leds[11].setRGB(0,0,on); 
    leds[12].setRGB(0,0,0); 
    leds[13].setRGB(0,0,0); 
} else if (zahl1 == "7"){
    leds[0].setRGB(0,0,0); 
    leds[1].setRGB(0,0,0); 
    leds[2].setRGB(0,0,0); 
    leds[3].setRGB(0,0,0); 
    leds[4].setRGB(0,0,0); 
    leds[5].setRGB(0,0,0); 
    leds[6].setRGB(0,0,on); 
    leds[7].setRGB(0,0,on); 
    leds[8].setRGB(0,0,0); 
    leds[9].setRGB(0,0,0); 
    leds[10].setRGB(0,0,on); 
    leds[11].setRGB(0,0,on); 
    leds[12].setRGB(0,0,on); 
    leds[13].setRGB(0,0,on); 
} else if (zahl1 == "8"){
    leds[0].setRGB(0,0,on+correct); 
    leds[1].setRGB(0,0,on); 
    leds[2].setRGB(0,0,on); 
    leds[3].setRGB(0,0,on); 
    leds[4].setRGB(0,0,on); 
    leds[5].setRGB(0,0,on); 
    leds[6].setRGB(0,0,on); 
    leds[7].setRGB(0,0,on); 
    leds[8].setRGB(0,0,on); 
    leds[9].setRGB(0,0,on); 
    leds[10].setRGB(0,0,on); 
    leds[11].setRGB(0,0,on); 
    leds[12].setRGB(0,0,on); 
    leds[13].setRGB(0,0,on); 
} else if (zahl1 == "9"){
    leds[0].setRGB(0,0,on+correct); 
    leds[1].setRGB(0,0,on); 
    leds[2].setRGB(0,0,0); 
    leds[3].setRGB(0,0,0); 
    leds[4].setRGB(0,0,on); 
    leds[5].setRGB(0,0,on); 
    leds[6].setRGB(0,0,on); 
    leds[7].setRGB(0,0,on); 
    leds[8].setRGB(0,0,on); 
    leds[9].setRGB(0,0,on); 
    leds[10].setRGB(0,0,on); 
    leds[11].setRGB(0,0,on); 
    leds[12].setRGB(0,0,on); 
    leds[13].setRGB(0,0,on); 
}





if (zahl2 == "0"){
    leds[14].setRGB(0,0,on); 
    leds[15].setRGB(0,0,on); 
    leds[16].setRGB(0,0,on); 
    leds[17].setRGB(0,0,on); 
    leds[18].setRGB(0,0,on); 
    leds[19].setRGB(0,0,0); 
    leds[20].setRGB(0,0,on); 
    leds[21].setRGB(0,0,on); 
    leds[22].setRGB(0,0,0); 
    leds[23].setRGB(0,0,on); 
    leds[24].setRGB(0,0,on); 
    leds[25].setRGB(0,0,on); 
    leds[26].setRGB(0,0,on); 
    leds[27].setRGB(0,0,on); 
} else if (zahl2 == "1"){
    leds[14].setRGB(0,0,0); 
    leds[15].setRGB(0,0,0); 
    leds[16].setRGB(0,0,0); 
    leds[17].setRGB(0,0,0); 
    leds[18].setRGB(0,0,0); 
    leds[19].setRGB(0,0,0); 
    leds[20].setRGB(0,0,0); 
    leds[21].setRGB(0,0,0); 
    leds[22].setRGB(0,0,0); 
    leds[23].setRGB(0,0,0); 
    leds[24].setRGB(0,0,on); 
    leds[25].setRGB(0,0,on); 
    leds[26].setRGB(0,0,on); 
    leds[27].setRGB(0,0,on); 
} else if (zahl2 == "2"){
    leds[14].setRGB(0,0,0); 
    leds[15].setRGB(0,0,0); 
    leds[16].setRGB(0,0,on); 
    leds[17].setRGB(0,0,on); 
    leds[18].setRGB(0,0,on); 
    leds[19].setRGB(0,0,on); 
    leds[20].setRGB(0,0,on); 
    leds[21].setRGB(0,0,on); 
    leds[22].setRGB(0,0,on); 
    leds[23].setRGB(0,0,on); 
    leds[24].setRGB(0,0,0); 
    leds[25].setRGB(0,0,0); 
    leds[26].setRGB(0,0,on); 
    leds[27].setRGB(0,0,on); 
} else if (zahl2 == "3"){
    leds[14].setRGB(0,0,0); 
    leds[15].setRGB(0,0,0); 
    leds[16].setRGB(0,0,0); 
    leds[17].setRGB(0,0,0); 
    leds[18].setRGB(0,0,on); 
    leds[19].setRGB(0,0,on); 
    leds[20].setRGB(0,0,on); 
    leds[21].setRGB(0,0,on); 
    leds[22].setRGB(0,0,on); 
    leds[23].setRGB(0,0,on); 
    leds[24].setRGB(0,0,on); 
    leds[25].setRGB(0,0,on); 
    leds[26].setRGB(0,0,on); 
    leds[27].setRGB(0,0,on); 
} else if (zahl2 == "4"){
    leds[14].setRGB(0,0,on); 
    leds[15].setRGB(0,0,on); 
    leds[16].setRGB(0,0,0); 
    leds[17].setRGB(0,0,0); 
    leds[18].setRGB(0,0,0); 
    leds[19].setRGB(0,0,on); 
    leds[20].setRGB(0,0,0); 
    leds[21].setRGB(0,0,0); 
    leds[22].setRGB(0,0,on); 
    leds[23].setRGB(0,0,0); 
    leds[24].setRGB(0,0,on); 
    leds[25].setRGB(0,0,on); 
    leds[26].setRGB(0,0,on); 
    leds[27].setRGB(0,0,on); 
} else if (zahl2 == "5"){
    leds[14].setRGB(0,0,on); 
    leds[15].setRGB(0,0,on); 
    leds[16].setRGB(0,0,0); 
    leds[17].setRGB(0,0,0); 
    leds[18].setRGB(0,0,on); 
    leds[19].setRGB(0,0,on); 
    leds[20].setRGB(0,0,on); 
    leds[21].setRGB(0,0,on); 
    leds[22].setRGB(0,0,on); 
    leds[23].setRGB(0,0,on); 
    leds[24].setRGB(0,0,on); 
    leds[25].setRGB(0,0,on); 
    leds[26].setRGB(0,0,0); 
    leds[27].setRGB(0,0,0); 
} else if (zahl2 == "6"){
    leds[14].setRGB(0,0,on); 
    leds[15].setRGB(0,0,on); 
    leds[16].setRGB(0,0,on); 
    leds[17].setRGB(0,0,on); 
    leds[18].setRGB(0,0,on); 
    leds[19].setRGB(0,0,on); 
    leds[20].setRGB(0,0,on); 
    leds[21].setRGB(0,0,on); 
    leds[22].setRGB(0,0,on); 
    leds[23].setRGB(0,0,on); 
    leds[24].setRGB(0,0,on); 
    leds[25].setRGB(0,0,on); 
    leds[26].setRGB(0,0,0); 
    leds[27].setRGB(0,0,0); 
} else if (zahl2 == "7"){
    leds[14].setRGB(0,0,0); 
    leds[15].setRGB(0,0,0); 
    leds[16].setRGB(0,0,0); 
    leds[17].setRGB(0,0,0); 
    leds[18].setRGB(0,0,0); 
    leds[19].setRGB(0,0,0); 
    leds[20].setRGB(0,0,on); 
    leds[21].setRGB(0,0,on); 
    leds[22].setRGB(0,0,0); 
    leds[23].setRGB(0,0,0); 
    leds[24].setRGB(0,0,on); 
    leds[25].setRGB(0,0,on); 
    leds[26].setRGB(0,0,on); 
    leds[27].setRGB(0,0,on); 
} else if (zahl2 == "8"){
    leds[14].setRGB(0,0,on); 
    leds[15].setRGB(0,0,on); 
    leds[16].setRGB(0,0,on); 
    leds[17].setRGB(0,0,on); 
    leds[18].setRGB(0,0,on); 
    leds[19].setRGB(0,0,on); 
    leds[20].setRGB(0,0,on); 
    leds[21].setRGB(0,0,on); 
    leds[22].setRGB(0,0,on); 
    leds[23].setRGB(0,0,on); 
    leds[24].setRGB(0,0,on); 
    leds[25].setRGB(0,0,on); 
    leds[26].setRGB(0,0,on); 
    leds[27].setRGB(0,0,on); 
} else if (zahl2 == "9"){
    leds[14].setRGB(0,0,on); 
    leds[15].setRGB(0,0,on); 
    leds[16].setRGB(0,0,0); 
    leds[17].setRGB(0,0,0); 
    leds[18].setRGB(0,0,on); 
    leds[19].setRGB(0,0,on); 
    leds[20].setRGB(0,0,on); 
    leds[21].setRGB(0,0,on); 
    leds[22].setRGB(0,0,on); 
    leds[23].setRGB(0,0,on); 
    leds[24].setRGB(0,0,on); 
    leds[25].setRGB(0,0,on); 
    leds[26].setRGB(0,0,on); 
    leds[27].setRGB(0,0,on); 
}




if (zahl3 == "0"){
    leds[30].setRGB(0,on,0); 
    leds[31].setRGB(0,on,0); 
    leds[32].setRGB(0,on,0); 
    leds[33].setRGB(0,on,0); 
    leds[34].setRGB(0,on,0); 
    leds[35].setRGB(0,0,0); 
    leds[36].setRGB(0,on,0); 
    leds[37].setRGB(0,on,0); 
    leds[38].setRGB(0,0,0); 
    leds[39].setRGB(0,on,0); 
    leds[40].setRGB(0,on,0); 
    leds[41].setRGB(0,on,0); 
    leds[42].setRGB(0,on,0); 
    leds[43].setRGB(0,on,0); 
} else if (zahl3 == "1"){
    leds[30].setRGB(0,0,0); 
    leds[31].setRGB(0,0,0); 
    leds[32].setRGB(0,0,0); 
    leds[33].setRGB(0,0,0); 
    leds[34].setRGB(0,0,0); 
    leds[35].setRGB(0,0,0); 
    leds[36].setRGB(0,0,0); 
    leds[37].setRGB(0,0,0); 
    leds[38].setRGB(0,0,0); 
    leds[39].setRGB(0,0,0); 
    leds[40].setRGB(0,on,0); 
    leds[41].setRGB(0,on,0); 
    leds[42].setRGB(0,on,0); 
    leds[43].setRGB(0,on,0); 
} else if (zahl3 == "2"){
    leds[30].setRGB(0,on,0); 
    leds[31].setRGB(0,on,0); 
    leds[32].setRGB(0,0,0); 
    leds[33].setRGB(0,0,0); 
    leds[34].setRGB(0,on,0); 
    leds[35].setRGB(0,on,0); 
    leds[36].setRGB(0,on,0); 
    leds[37].setRGB(0,on,0); 
    leds[38].setRGB(0,on,0); 
    leds[39].setRGB(0,on,0); 
    leds[40].setRGB(0,on,0); 
    leds[41].setRGB(0,on,0); 
    leds[42].setRGB(0,0,0); 
    leds[43].setRGB(0,0,0); 
} else if (zahl3 == "3"){
    leds[30].setRGB(0,0,0); 
    leds[31].setRGB(0,0,0); 
    leds[32].setRGB(0,0,0); 
    leds[33].setRGB(0,0,0); 
    leds[34].setRGB(0,on,0); 
    leds[35].setRGB(0,on,0); 
    leds[36].setRGB(0,on,0); 
    leds[37].setRGB(0,on,0); 
    leds[38].setRGB(0,on,0); 
    leds[39].setRGB(0,on,0); 
    leds[40].setRGB(0,on,0); 
    leds[41].setRGB(0,on,0); 
    leds[42].setRGB(0,on,0); 
    leds[43].setRGB(0,on,0); 
} else if (zahl3 == "4"){
    leds[30].setRGB(0,0,0); 
    leds[31].setRGB(0,0,0); 
    leds[32].setRGB(0,on,0); 
    leds[33].setRGB(0,on,0); 
    leds[34].setRGB(0,0,0); 
    leds[35].setRGB(0,on,0); 
    leds[36].setRGB(0,0,0); 
    leds[37].setRGB(0,0,0); 
    leds[38].setRGB(0,on,0); 
    leds[39].setRGB(0,0,0); 
    leds[40].setRGB(0,on,0); 
    leds[41].setRGB(0,on,0); 
    leds[42].setRGB(0,on,0); 
    leds[43].setRGB(0,on,0); 
} else if (zahl3 == "5"){
    leds[30].setRGB(0,0,0); 
    leds[31].setRGB(0,0,0); 
    leds[32].setRGB(0,on,0); 
    leds[33].setRGB(0,on,0); 
    leds[34].setRGB(0,on,0); 
    leds[35].setRGB(0,on,0); 
    leds[36].setRGB(0,on,0); 
    leds[37].setRGB(0,on,0); 
    leds[38].setRGB(0,on,0); 
    leds[39].setRGB(0,on,0); 
    leds[40].setRGB(0,0,0); 
    leds[41].setRGB(0,0,0); 
    leds[42].setRGB(0,on,0); 
    leds[43].setRGB(0,on,0); 
} else if (zahl3 == "6"){
    leds[30].setRGB(0,on,0); 
    leds[31].setRGB(0,on,0); 
    leds[32].setRGB(0,on,0); 
    leds[33].setRGB(0,on,0); 
    leds[34].setRGB(0,on,0); 
    leds[35].setRGB(0,on,0); 
    leds[36].setRGB(0,on,0); 
    leds[37].setRGB(0,on,0); 
    leds[38].setRGB(0,on,0); 
    leds[39].setRGB(0,on,0); 
    leds[40].setRGB(0,0,0); 
    leds[41].setRGB(0,0,0); 
    leds[42].setRGB(0,on,0); 
    leds[43].setRGB(0,on,0); 
} else if (zahl3 == "7"){
    leds[30].setRGB(0,0,0); 
    leds[31].setRGB(0,0,0); 
    leds[32].setRGB(0,0,0); 
    leds[33].setRGB(0,0,0); 
    leds[34].setRGB(0,on,0); 
    leds[35].setRGB(0,0,0); 
    leds[36].setRGB(0,0,0); 
    leds[37].setRGB(0,0,0); 
    leds[38].setRGB(0,0,0); 
    leds[39].setRGB(0,on,0); 
    leds[40].setRGB(0,on,0); 
    leds[41].setRGB(0,on,0); 
    leds[42].setRGB(0,on,0); 
    leds[43].setRGB(0,on,0); 
} else if (zahl3 == "8"){
    leds[30].setRGB(0,on,0); 
    leds[31].setRGB(0,on,0); 
    leds[32].setRGB(0,on,0); 
    leds[33].setRGB(0,on,0); 
    leds[34].setRGB(0,on,0); 
    leds[35].setRGB(0,on,0); 
    leds[36].setRGB(0,on,0); 
    leds[37].setRGB(0,on,0); 
    leds[38].setRGB(0,on,0); 
    leds[39].setRGB(0,on,0); 
    leds[40].setRGB(0,on,0); 
    leds[41].setRGB(0,on,0); 
    leds[42].setRGB(0,on,0); 
    leds[43].setRGB(0,on,0); 
} else if (zahl3 == "9"){
    leds[30].setRGB(0,0,0); 
    leds[31].setRGB(0,0,0); 
    leds[32].setRGB(0,on,0); 
    leds[33].setRGB(0,on,0); 
    leds[34].setRGB(0,on,0); 
    leds[35].setRGB(0,on,0); 
    leds[36].setRGB(0,on,0); 
    leds[37].setRGB(0,on,0); 
    leds[38].setRGB(0,on,0); 
    leds[39].setRGB(0,on,0); 
    leds[40].setRGB(0,on,0); 
    leds[41].setRGB(0,on,0); 
    leds[42].setRGB(0,on,0); 
    leds[43].setRGB(0,on,0); 
}
if (zahl4 == "0"){
    leds[44].setRGB(0,on,0); 
    leds[45].setRGB(0,on,0); 
    leds[46].setRGB(0,on,0); 
    leds[47].setRGB(0,on,0); 
    leds[48].setRGB(0,on,0); 
    leds[49].setRGB(0,0,0); 
    leds[50].setRGB(0,on,0); 
    leds[51].setRGB(0,on,0); 
    leds[52].setRGB(0,0,0); 
    leds[53].setRGB(0,on,0); 
    leds[54].setRGB(0,on,0); 
    leds[55].setRGB(0,on,0); 
    leds[56].setRGB(0,on,0); 
    leds[57].setRGB(0,on,0); 
} else if (zahl4 == "1"){
    leds[44].setRGB(0,0,0); 
    leds[45].setRGB(0,0,0); 
    leds[46].setRGB(0,0,0); 
    leds[47].setRGB(0,0,0); 
    leds[48].setRGB(0,0,0); 
    leds[49].setRGB(0,0,0); 
    leds[50].setRGB(0,0,0); 
    leds[51].setRGB(0,0,0); 
    leds[52].setRGB(0,0,0); 
    leds[53].setRGB(0,0,0); 
    leds[54].setRGB(0,on,0); 
    leds[55].setRGB(0,on,0); 
    leds[56].setRGB(0,on,0); 
    leds[57].setRGB(0,on,0); 
} else if (zahl4 == "2"){
    leds[44].setRGB(0,on,0); 
    leds[45].setRGB(0,on,0); 
    leds[46].setRGB(0,0,0); 
    leds[47].setRGB(0,0,0); 
    leds[48].setRGB(0,on,0); 
    leds[49].setRGB(0,on,0); 
    leds[50].setRGB(0,on,0); 
    leds[51].setRGB(0,on,0); 
    leds[52].setRGB(0,on,0); 
    leds[53].setRGB(0,on,0); 
    leds[54].setRGB(0,on,0); 
    leds[55].setRGB(0,on,0); 
    leds[56].setRGB(0,0,0); 
    leds[57].setRGB(0,0,0); 
} else if (zahl4 == "3"){
    leds[44].setRGB(0,0,0); 
    leds[45].setRGB(0,0,0); 
    leds[46].setRGB(0,0,0); 
    leds[47].setRGB(0,0,0); 
    leds[48].setRGB(0,on,0); 
    leds[49].setRGB(0,on,0); 
    leds[50].setRGB(0,on,0); 
    leds[51].setRGB(0,on,0); 
    leds[52].setRGB(0,on,0); 
    leds[53].setRGB(0,on,0); 
    leds[54].setRGB(0,on,0); 
    leds[55].setRGB(0,on,0); 
    leds[56].setRGB(0,on,0); 
    leds[57].setRGB(0,on,0); 
} else if (zahl4 == "4"){
    leds[44].setRGB(0,0,0); 
    leds[45].setRGB(0,0,0); 
    leds[46].setRGB(0,on,0); 
    leds[47].setRGB(0,on,0); 
    leds[48].setRGB(0,0,0); 
    leds[49].setRGB(0,on,0); 
    leds[50].setRGB(0,0,0); 
    leds[51].setRGB(0,0,0); 
    leds[52].setRGB(0,on,0); 
    leds[53].setRGB(0,0,0); 
    leds[54].setRGB(0,on,0); 
    leds[55].setRGB(0,on,0); 
    leds[56].setRGB(0,on,0); 
    leds[57].setRGB(0,on,0); 
} else if (zahl4 == "5"){
    leds[44].setRGB(0,0,0); 
    leds[45].setRGB(0,0,0); 
    leds[46].setRGB(0,on,0); 
    leds[47].setRGB(0,on,0); 
    leds[48].setRGB(0,on,0); 
    leds[49].setRGB(0,on,0); 
    leds[50].setRGB(0,on,0); 
    leds[51].setRGB(0,on,0); 
    leds[52].setRGB(0,on,0); 
    leds[53].setRGB(0,on,0); 
    leds[54].setRGB(0,0,0); 
    leds[55].setRGB(0,0,0); 
    leds[56].setRGB(0,on,0); 
    leds[57].setRGB(0,on,0); 
} else if (zahl4 == "6"){
    leds[44].setRGB(0,on,0); 
    leds[45].setRGB(0,on,0); 
    leds[46].setRGB(0,on,0); 
    leds[47].setRGB(0,on,0); 
    leds[48].setRGB(0,on,0); 
    leds[49].setRGB(0,on,0); 
    leds[50].setRGB(0,on,0); 
    leds[51].setRGB(0,on,0); 
    leds[52].setRGB(0,on,0); 
    leds[53].setRGB(0,on,0); 
    leds[54].setRGB(0,0,0); 
    leds[55].setRGB(0,0,0); 
    leds[56].setRGB(0,on,0); 
    leds[57].setRGB(0,on,0); 
} else if (zahl4 == "7"){
    leds[44].setRGB(0,0,0); 
    leds[45].setRGB(0,0,0); 
    leds[46].setRGB(0,0,0); 
    leds[47].setRGB(0,0,0); 
    leds[48].setRGB(0,on,0); 
    leds[49].setRGB(0,0,0); 
    leds[50].setRGB(0,0,0); 
    leds[51].setRGB(0,0,0); 
    leds[52].setRGB(0,0,0); 
    leds[53].setRGB(0,on,0); 
    leds[54].setRGB(0,on,0); 
    leds[55].setRGB(0,on,0); 
    leds[56].setRGB(0,on,0); 
    leds[57].setRGB(0,on,0); 
} else if (zahl4 == "8"){
    leds[44].setRGB(0,on,0); 
    leds[45].setRGB(0,on,0); 
    leds[46].setRGB(0,on,0); 
    leds[47].setRGB(0,on,0); 
    leds[48].setRGB(0,on,0); 
    leds[49].setRGB(0,on,0); 
    leds[50].setRGB(0,on,0); 
    leds[51].setRGB(0,on,0); 
    leds[52].setRGB(0,on,0); 
    leds[53].setRGB(0,on,0); 
    leds[54].setRGB(0,on,0); 
    leds[55].setRGB(0,on,0); 
    leds[56].setRGB(0,on,0); 
    leds[57].setRGB(0,on,0); 
} else if (zahl4 == "9"){
    leds[44].setRGB(0,0,0); 
    leds[45].setRGB(0,0,0); 
    leds[46].setRGB(0,on,0); 
    leds[47].setRGB(0,on,0); 
    leds[48].setRGB(0,on,0); 
    leds[49].setRGB(0,on,0); 
    leds[50].setRGB(0,on,0); 
    leds[51].setRGB(0,on,0); 
    leds[52].setRGB(0,on,0); 
    leds[53].setRGB(0,on,0); 
    leds[54].setRGB(0,on,0); 
    leds[55].setRGB(0,on,0); 
    leds[56].setRGB(0,on,0); 
    leds[57].setRGB(0,on,0); 
}

}


void roundcolor(String nightmode,uint8_t var_red_on, uint8_t var_green_on, uint8_t var_blue_on, int var_delay, int var_runden){
if (nightmode == "yes"){ on = nightmodeon; correct=correctn;}
if (nightmode == "no"){ on = daymodeon; correct=correctd;}
        for(int runden = 0; runden < var_runden; runden++) {
    int anz = 0;
        for(int dot = 0; dot < NUM_LEDS; dot++) {
uint8_t  var_red = 0;
uint8_t  var_green = 0;
uint8_t  var_blue = 0;
    morevals = "";
          anz++;
          if(dot == 0){ledAddVal = correct;}
          else{ledAddVal = 0;} 
if(var_red_on == 1){var_red=on+ledAddVal;}
if(var_green_on == 1){var_green=on+ledAddVal;}
if(var_blue_on == 1){var_blue=on+ledAddVal;}
                      leds[dot].setRGB(var_red,var_green,var_blue);
            FastLED.show();
      morevals += "leds["+String(dot)+"]";
//      if(anz < NUM_LEDS){
      morevals += ".setRGB(" + String(var_red) + "," + String(var_green) + "," + String(var_blue) + ")";
//      }
//      if(anz >= NUM_LEDS){
//      morevals += ".setRGB(" + String(daymodeon+ledAddVal) + "/0/0]";
//      }
     MyArray[0][dot] = morevals;
     MyArray2[0] = anz;
            // clear this led for the next time around the loop
            //leds[dot] = CRGB::Black;
            delay(var_delay);
        }
//     MyArray[0][1] = String(anz);
        for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB(0,0,0);
            FastLED.show();
            // clear this led for the next time around the loop
            //leds[dot] = CRGB::Black;
            delay(var_delay);
        }
            leds[0].setRGB(0,0,0);
//FastLED.clear();
  FastLED.show();           // Turn OFF all pixels ASAP
        }
  //pixels.setBrightness(bright); // Set BRIGHTNESS to about 1/5 (max = 255)
#if defined (S_DEBUG_MODE)
        Serial.println("MyArray[0]: ");
    for (int i2 = 0; i2 < 118; i2++){ 
        Serial.println(MyArray[0][i2]);
    }
       Serial.print("MyArray[0] anz: ");
        Serial.println(MyArray2[0]);
#endif

}

void my_fill_rainbow( struct CRGB * targetArray, int numToStart, int numToFill,
                  uint8_t initialhue,
                  uint8_t deltahue,float night=on,int MyArrayIdent=1)
{
   //FastLED.setBrightness(night);
   CHSV hsv;
    hsv.hue = initialhue;
    hsv.val = 255;
    hsv.sat = 240;
    int anz = 0;
    int posID = 0;
    float ledSubValR = 0;
    float ledSubValG = 0;
    float ledSubValB = 0;
    int ledSubValRI = 0;
    int ledSubValGI = 0;
    int ledSubValBI = 0;
   float ledSubVal100 = night/255;
   float ledAddValF = ledAddVal;
if (night == nightmodeon){ on = nightmodeon; correct=correctn;}
if (night == daymodeon){ on = daymodeon; correct=correctd;}
   float correctF = correct;
//   int ledSubVal100fest = 64/255;
     //numToStart +1;
    for( int i = numToStart; i < numToFill; ++i) {
    morevals = "";
        anz++;  
          if(i == 0){ledSubVal100 = (night+correctF)/255;} 
          else{ledSubVal100 = night/255;} 

      morevals += "leds["+String(i)+"].setRGB(";
  //    morevals += "LED["+String(i)+"]";
  //        Serial.print("[");
    //        Serial.print(i);
    //        Serial.print("]");
        hsv.hue += deltahue;
  CRGB rgb;
  hsv2rgb_rainbow( hsv, rgb);
         targetArray[i] = rgb;

  if (targetArray[i][0] > 0){
    float tArrR = targetArray[i][0];   
    ledSubValR = ledSubVal100*tArrR;
//    ledSubValR = ledSubValR+ledAddValF;
    ledSubValRI = round(ledSubValR);
    targetArray[i][0] = ledSubValRI; 
//        Serial.print("targetArray[");
//        Serial.print(i);
//        Serial.print("][0] - ");
//        Serial.print(ledSubValRI);
//        Serial.print("...");
//        Serial.print(targetArray[i][0]);
//        Serial.print(" / ");
      morevals += String(targetArray[i][0]) + ",";
  } // red
  if (targetArray[i][1] > 0){
    float tArrG = targetArray[i][1];   
    ledSubValG = ledSubVal100*tArrG;
//    ledSubValG = ledSubValG+ledAddValF;
    ledSubValGI = round(ledSubValG);
    targetArray[i][1] = ledSubValGI; 
//        Serial.print("targetArray[");
//        Serial.print(i);
//        Serial.print("][1] - ");
//        Serial.print(ledSubValGI);
//        Serial.print("...");
//        Serial.print(targetArray[i][1]);
//        Serial.print(" / ");
      morevals += String(targetArray[i][1]) + ",";
  } // green
  if (targetArray[i][2] > 0){
    float tArrB = targetArray[i][2];   
    ledSubValB = ledSubVal100*tArrB;
//    ledSubValB = ledSubValB+ledAddValF;
    ledSubValBI = round(ledSubValB);
    targetArray[i][2] = ledSubValBI; 
//        Serial.print("targetArray[");
//        Serial.print(i);
//        Serial.print("][2] - ");
//        Serial.print(ledSubValBI);
//        Serial.print("...");
//        Serial.print(targetArray[i][2]);
//        Serial.println(" ");
      morevals += String(targetArray[i][2]);
  } // blue

      morevals += ")";

     MyArray[MyArrayIdent][posID] = morevals;
    posID ++;
  }
     MyArray2[MyArrayIdent] = anz;
    //     Serial.print("(");
    //     Serial.print(anz);
    //     Serial.println(")");
    // MyArray[MyArrayIdent][0] = morevals;
    // MyArray[MyArrayIdent][1] = String(anz);
  //return(ret_var);
//  FastLED.setBrightness(bright);
}



// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void myrainbow(int wait,String night="no",uint8_t var_round_multipler=1) {
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
    float on1 = daymodeon;
    if (night == "yes"){ on1 = nightmodeon;}
if (night == "no"){ on1 = daymodeon;}

  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 600*var_round_multipler; firstPixelHue ++) {
//  for(long firstPixelHue = 0; firstPixelHue < 1; firstPixelHue ++) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
   // pixels.rainbow(firstPixelHue,1,255,on1,false);
     my_fill_rainbow( leds, 0, 58, gHue, 4,on1,1);
      my_fill_rainbow( leds, 58, 118, gHue, 4,on1,2);
//        Serial.print("anz:");
//        Serial.println(on1);
 // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
//        Serial.print("on1:");
//        Serial.println(on1);
//        Serial.print("firstPixelHue ");
//        Serial.print(firstPixelHue);

    FastLED.show();// Update strip with new contents
//  FastLED.delay(1000/80); 
  EVERY_N_MILLISECONDS( 1 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  
  }
FastLED.clear();
/*        Serial.print("Ident0 leds: ");
        Serial.println(MyArray[1][0]);
        Serial.print("Ident0 anz: ");
        Serial.println(MyArray[1][1]);
        Serial.print("Ident1 leds: ");
        Serial.println(MyArray[2][0]);
        Serial.print("Ident1 anz: ");
        Serial.println(MyArray[2][1]);*/
  //    delay(wait);  // Pause for a moment
//        Serial.println("MyArray: ");
//int arraySize = sizeof(MyArray) / sizeof(MyArray[0]);

//  for (int i = 0; i < 3; i++){
//int arraySize2 = sizeof(MyArray[i]) / sizeof(MyArray[i][0]);
//    for (int i2 = 0; i2 < 2; i2++){
//        Serial.print("MyArray[");
//        Serial.print(i);
//        Serial.print("][");
//        Serial.print(i2);
//        Serial.print("]: ");
//      Serial.println(MyArray[i][i2]);
//    }
//  }
#if defined (S_DEBUG_MODE)
        Serial.println("MyArray[0]: ");
    for (int i2 = 0; i2 < MyArray2[0]; i2++){ 
        Serial.println(MyArray[0][i2]);
    }
        Serial.print("MyArray[0] anz: ");
        Serial.println(MyArray2[0]);

        Serial.println("MyArray[1]: ");
    for (int i2 = 0; i2 < MyArray2[1]; i2++){ 
        Serial.println(MyArray[1][i2]);
    }
        Serial.print("MyArray[1] anz: ");
        Serial.println(MyArray2[1]);
 
        Serial.println("MyArray[2]: ");
    for (int i2 = 0; i2 < MyArray2[2]; i2++){ 
        Serial.println(MyArray[2][i2]);
    }
        Serial.print("MyArray[2] anz: ");
        Serial.println(MyArray2[2]);
#endif

} 


void setup() 
{

  Serial.begin(115200);
//#include "wifi_sec.cpp"
//const char *ssid     = "wifissid";
//const char *password = "wifipass";
    WiFiSettings.hostname = "ESP-Clock";
    WiFiSettings.language = "de";
    SPIFFS.begin(true);  // Will format on the first run after failing to mount

    pinMode(LED_PIN, OUTPUT);
 pinMode(CONFIG_PIN, INPUT_PULLUP);
//  WiFi.begin(ssid, password);

    // Set custom callback functions
    WiFiSettings.onSuccess  = []() {
        digitalWrite(LED_PIN, LED_ON); // Turn LED on
    };
    WiFiSettings.onFailure  = []() {
        digitalWrite(LED_PIN, LED_OFF); // Turn LED off
    };
    WiFiSettings.onWaitLoop = []() {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED
        return 500; // Delay next function call by 500ms
    };
    //String host = WiFiSettings.string( "server_host", "default.example.org");
    //int    port = WiFiSettings.integer("server_port", 443);
  DS18B20.begin();    // initialize the DS18B20 sensor
FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
   // limit my draw to 1A at 5v of power draw
   FastLED.setMaxPowerInVoltsAndMilliamps(5,1000); 
//  FastLED.setBrightness(bright);

 // pixels.begin();
   pinMode(IR_FEEDBACK_LED_PIN, OUTPUT);

  pinMode(RELAY_PIN, OUTPUT);
pinMode(BUTTON_PIN, INPUT);
 // irrecv.enableIRIn();
//  irrecv.blink13(true);

    WiFiSettings.connect(true, 30);

byte pressed_config_pin = digitalRead(CONFIG_PIN);
if(pressed_config_pin == LOW){
Serial.println("Config-Button Pressed");

WiFiSettings.portal();

}


Serial.println("Winterzeit");
int ledState = LOW;   // ledState used to set the LED

//Serial.print("verbinde zu Router");
//  while (WiFi.status() != WL_CONNECTED) {
      // if the LED is off turn it on and vice-versa:
//  ledState = (ledState == LOW) ? HIGH : LOW;

  // set the LED with the ledState of the variable:
//  digitalWrite(IR_FEEDBACK_LED_PIN, ledState);
 //   delay(200);
   // Serial.print(".");

  //}
  Serial.println("verbunden!");
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver

  timeClient.begin();
 
  digitalWrite(RELAY_PIN, HIGH);
Serial.print("NTP-Server Update alle ");
Serial.print(NTP_UPDATE_SEKUNDEN);
Serial.println(" Sekunden");

 timeClient.update();


  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
   String formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  String dayStamp = formattedDate.substring(0, splitT);


 String data_day = dayStamp.substring(8,10);
 String data_month = dayStamp.substring(5,7);
 String data_year = dayStamp.substring(0,4);

  String formattedTime = timeClient.getFormattedTime();
   int weekDay = timeClient.getDay();

 String data_std1 = formattedTime.substring(0,1);
 String data_std2 = formattedTime.substring(1,2);
 String data_min1 = formattedTime.substring(3,4);
 String data_min2 = formattedTime.substring(4,5);
 String data_std = formattedTime.substring(0,2);
 String data_min = formattedTime.substring(3,5);
 String data_sec = formattedTime.substring(6,8);
int data_std_2 = data_std.toInt();
int data_min_2 = data_min.toInt();
int data_sec2 = data_sec.toInt();

int year = data_year.toInt(); 
int month = data_month.toInt();
//int month = 1;
int day = data_day.toInt();
int hour = data_std_2;
int MEZ = 0;

  if (month<3 || month>10){
   timeClient.setTimeOffset(3600); 
        Serial.print("Winterzeit ");
        Serial.print(data_std_2-1);
        Serial.print(":");
        Serial.print(data_min_2);
        Serial.print(" ");
        Serial.print(day);
        Serial.print(".");
        Serial.print(month);
        Serial.print(".");
        Serial.print(year);
     MEZ = 0;
             Serial.print(" MEZ=");

        Serial.println(MEZ);
  }
  
  if (month>3 && month<10){
   timeClient.setTimeOffset(7200); 
        Serial.print("Sommerzeit ");
        Serial.print(data_std_2+1);
        Serial.print(":");
        Serial.print(data_min_2);
        Serial.print(" ");
        Serial.print(day);
        Serial.print(".");
        Serial.print(month);
        Serial.print(".");
        Serial.print(year);
        MEZ = 1;
        Serial.print(" MEZ=");
        Serial.println(MEZ);
  }

//--------------------------------------------
int akt_std = data_std_2;
int akt_min = data_min_2;
int akt_sec = data_sec2;
String akt_std_zero = "";
if (akt_std < 10){akt_std_zero = "0";}
String akt_min_zero = "";
if (akt_min < 10){akt_min_zero = "0";}
String akt_sec_zero = "";
if (akt_sec < 10){akt_sec_zero = "0";}
String akt_mode = akt_std_zero + String(akt_std) + akt_min_zero + String(akt_min) + akt_sec_zero + String(akt_sec);
int switch_nightmode_std = 18;
int switch_nightmode_min = 30;
int switch_nightmode_sec = 0;
String sw_nm_std_zero = "";
if (switch_nightmode_std < 10){sw_nm_std_zero = "0";}
String sw_nm_min_zero = "";
if (switch_nightmode_min < 10){sw_nm_min_zero = "0";}
String sw_nm_sec_zero = "";
if (switch_nightmode_sec < 10){sw_nm_sec_zero = "0";}
String switch_nmode = sw_nm_std_zero + String(switch_nightmode_std) + sw_nm_min_zero + String(switch_nightmode_min) + sw_nm_sec_zero + String(switch_nightmode_sec);
int switch_daymode_std = 6;
int switch_daymode_min = 30;
int switch_daymode_sec = 0;
String sw_dm_std_zero = "";
if (switch_daymode_std < 10){sw_dm_std_zero = "0";}
String sw_dm_min_zero = "";
if (switch_daymode_min < 10){sw_dm_min_zero = "0";}
String sw_dm_sec_zero = "";
if (switch_daymode_sec < 10){sw_dm_sec_zero = "0";}
String switch_dmode = sw_dm_std_zero + String(switch_daymode_std) + sw_dm_min_zero + String(switch_daymode_min) + sw_dm_sec_zero + String(switch_daymode_sec);
int akt_time = akt_mode.toInt();
int sw_nm_time = switch_nmode.toInt();
int sw_dm_time = switch_dmode.toInt();

    if(data_std_2 == 6 && data_min_2 == 30 && data_sec2 == 0){
        nightmode="no";
        Serial.println("it is Morning  - switch to Daymode");
    }
    if(akt_time > sw_dm_time && akt_time < sw_nm_time && nightmode=="yes"){
        nightmode="no";
        Serial.println("it is after "+switch_dmode+" - switch to Daymode");
    }
    if(data_std_2 == 18 && data_min_2 == 30 && data_sec2 == 0 ){nightmode="yes";
        Serial.println("it is Afternoon - switch to Nightmode");
    }
    if(akt_time < sw_dm_time && nightmode=="no" or akt_time > sw_nm_time && nightmode=="no"){nightmode="yes";
        Serial.println("it is after "+switch_nmode+" - switch to Nightmode");
    }
 //--------------------------------------------------


 myrainbow(40,nightmode); 
 /* if (month == 3 && (hour + 24 * day) >= (1 + MEZ + 24 * (31 - (5 * year / 4 + 4) % 7)))
  {
   timeClient.setTimeOffset(7200); 
        Serial.println("Sommerzeit");
        Serial.print(data_std_2);
        Serial.print(":");
        Serial.print(data_min_2);
        Serial.print(" ");
        Serial.print(day);
        Serial.print(".");
        Serial.print(month);
         Serial.print(".");
        Serial.println(year);
        MEZ = 1;
        Serial.println(MEZ);
  }

  if (month == 10 && (hour + 24 * day) >= (1 + MEZ + 24 * (31 - (5 * year / 4 + 4) % 7)))
  {
   timeClient.setTimeOffset(3600); 
        Serial.println("Winterzeit");
        Serial.print(data_std_2);
        Serial.print(":");....
        Serial.print(data_min_2);
        Serial.print(" ");
        Serial.print(day);
        Serial.print(".");
        Serial.print(month);
         Serial.print(".");
        Serial.println(year);
        MEZ = 0;
        Serial.println(MEZ);
  }

*/

}


String edata(int start, int ende, String daten){
  String edata_return = "";
  edata_return = daten.substring(start, ende);
  return edata_return;
}


void loop(void) 
{
FastLED.clear();



  DS18B20.requestTemperatures();       // send the command to get temperatures
  tempC = round(DS18B20.getTempCByIndex(0));  // read temperature in °C
  //tempF = tempC * 9 / 5 + 32; // convert °C to °F
  //Serial.print("tempC");
  //Serial.println(tempC);
int temp=tempC;
data_epoch = timeClient.getEpochTime();
interval1_epoch = data_epoch;
interval2_epoch = data_epoch;
interval3_epoch = data_epoch;
interval4_epoch = data_epoch;

if (data_update == 0 or data_epoch >= data_update+NTP_UPDATE_SEKUNDEN){


timeClient.update();


  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
if (data_update == 0){
        Serial.print("Daten empfangen - Zeitstempel: ");
}
if (data_update != 0 && data_epoch >= data_update+NTP_UPDATE_SEKUNDEN){
        Serial.print("Daten update - Zeitstempel: ");
}
data_update = timeClient.getEpochTime();
//        Serial.print("data_update: ");
        Serial.println(data_update);
//        Serial.print("data_epoch: ");
//        Serial.println(data_epoch);
next_update = 0;
}
else{
if (interval1_update == 0 or interval1_epoch >= interval1_update+600){
int update_NTP = NTP_UPDATE_SEKUNDEN - next_update;
interval1_update = timeClient.getEpochTime();


        Serial.print("Nächstes Update in ");
        Serial.print(update_NTP);
        Serial.println(" Sekunden");
}
next_update ++;
next_interval1_update ++;
}

  // int data_std_2 = data_std.toInt();

  String formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  String dayStamp = formattedDate.substring(0, splitT);


 String data_day = edata(8,10,dayStamp);
 String data_month = edata(5,7,dayStamp);
 String data_year = edata(0,4,dayStamp);

  String formattedTime = timeClient.getFormattedTime();
   int weekDay = timeClient.getDay();

String data_std1 = edata(0,1,formattedTime);
 String data_std2 = edata(1,2,formattedTime);
 String data_min1 = edata(3,4,formattedTime);
 String data_min2 = edata(4,5,formattedTime);
 String data_sec = edata(6,8,formattedTime);

 String data_std = edata(0,2,formattedTime);
 String data_min = edata(3,5,formattedTime);
 int data_std_2 = data_std.toInt();
int data_min_2 = data_min.toInt();
int data_sec2 = data_sec.toInt();

int year = data_year.toInt(); 
int month = data_month.toInt();
//int month = 1;
int day = data_day.toInt();
int hour = data_std_2;
 //       Serial.println(MEZ);
/*  if (month<3 || month>10){
   timeClient.setTimeOffset(3600); 
        Serial.println("Winterzeit");
        Serial.print(data_std_2);
        Serial.print(":");
        Serial.print(data_min_2);
        Serial.print(" ");
        Serial.print(day);
        Serial.print(".");
        Serial.print(month);
        Serial.print(".");
        Serial.println(year);
        int MEZ = 0;
        Serial.println(MEZ);

  }
 if (month>3 && month<10){
   timeClient.setTimeOffset(7200); 
        Serial.println("Sommerzeit");
        Serial.print(data_std_2);
        Serial.print(":");
        Serial.print(data_min_2);
        Serial.print(" ");
        Serial.print(day);
        Serial.print(".");
        Serial.print(month);
        Serial.print(".");
        Serial.println(year);
          int MEZ = 1;
        Serial.println(MEZ);
}*/
  if(MEZ == 0){
  if (month == 3 && (hour + 24 * day) >= (1 + MEZ + 24 * (31 - (5 * year / 4 + 4) % 7)))
  {
   timeClient.setTimeOffset(7200); 
        Serial.print("Sommerzeit ");
        Serial.print(data_std_2+1);
        Serial.print(":");
        Serial.print(data_min_2);
        Serial.print(" ");
        Serial.print(day);
        Serial.print(".");
        Serial.print(month);
        Serial.print(".");
        Serial.print(year);
        MEZ = 1;
        Serial.print(" MEZ=");

          Serial.println(MEZ);
}
  }

  if(MEZ == 1){
  if (month == 10 && (hour + 24 * day) >= (1 + MEZ + 24 * (31 - (5 * year / 4 + 4) % 7)))
  {
   timeClient.setTimeOffset(3600); 
        Serial.print("Winterzeit ");
        Serial.print(data_std_2-1);
        Serial.print(":");
        Serial.print(data_min_2);
        Serial.print(" ");
        Serial.print(day);
        Serial.print(".");
        Serial.print(month);
        Serial.print(".");
        Serial.print(year);
        MEZ = 0;
        Serial.print(" MEZ=");

          Serial.println(MEZ);
}
  }



 
//  Serial.print(daysOfTheWeek[timeClient.getDay()]);
//  Serial.print(", ");
//  Serial.println(timeClient.getFormattedTime());


    int sec_start = 58;
    int sec_end = 118; 

    int add_std = 0;
    if (data_min_2 >12){ add_std = 1;}
    if (data_min_2 >24){ add_std = 2;}
    if (data_min_2 >36){ add_std = 3;}
    if (data_min_2 >48){ add_std = 4;}
int std24 = 0;
if (data_std_2 > 12){ std24 = 12;}

  int std_led_1 = data_std_2 - std24;
int std_led = 0;
if(std_led_1 == 1){std_led = 5;}
if(std_led_1 == 2){std_led = 10;}
if(std_led_1 == 3){std_led = 15;}
if(std_led_1 == 4){std_led = 20;}
if(std_led_1 == 5){std_led = 25;}
if(std_led_1 == 6){std_led = 30;}
if(std_led_1 == 7){std_led = 35;}
if(std_led_1 == 8){std_led = 40;}
if(std_led_1 == 9){std_led = 45;}
if(std_led_1 == 10){std_led = 50;}
if(std_led_1 == 11){std_led = 55;}

std_led = std_led + add_std;
    int std_60 = sec_start + std_led;
    int min_60 = sec_start + data_min_2;
    int sekunde = sec_start + data_sec2;
//  Serial.print("std_led_1: ");
//  Serial.println(std_led_1);
//  Serial.print("std_led: ");
//  Serial.println(std_led);
//  Serial.print("add_std: ");
//  Serial.println(add_std);
int akt_std = data_std_2;
int akt_min = data_min_2;
int akt_sec = data_sec2;
String akt_std_zero = "";
if (akt_std < 10){akt_std_zero = "0";}
String akt_min_zero = "";
if (akt_min < 10){akt_min_zero = "0";}
String akt_sec_zero = "";
if (akt_sec < 10){akt_sec_zero = "0";}
String akt_mode = akt_std_zero + String(akt_std) + akt_min_zero + String(akt_min) + akt_sec_zero + String(akt_sec);

int switch_nightmode_std = 18;
int switch_nightmode_min = 30;
int switch_nightmode_sec = 0;
String sw_nm_std_zero = "";
if (switch_nightmode_std < 10){sw_nm_std_zero = "0";}
String sw_nm_min_zero = "";
if (switch_nightmode_min < 10){sw_nm_min_zero = "0";}
String sw_nm_sec_zero = "";
if (switch_nightmode_sec < 10){sw_nm_sec_zero = "0";}
String switch_nmode = sw_nm_std_zero + String(switch_nightmode_std) + sw_nm_min_zero + String(switch_nightmode_min) + sw_nm_sec_zero + String(switch_nightmode_sec);
int switch_daymode_std = 6;
int switch_daymode_min = 30;
int switch_daymode_sec = 0;
String sw_dm_std_zero = "";
if (switch_daymode_std < 10){sw_dm_std_zero = "0";}
String sw_dm_min_zero = "";
if (switch_daymode_min < 10){sw_dm_min_zero = "0";}
String sw_dm_sec_zero = "";
if (switch_daymode_sec < 10){sw_dm_sec_zero = "0";}
String switch_dmode = sw_dm_std_zero + String(switch_daymode_std) + sw_dm_min_zero + String(switch_daymode_min) + sw_dm_sec_zero + String(switch_daymode_sec);
int akt_time = akt_mode.toInt();
int sw_nm_time = switch_nmode.toInt();
int sw_dm_time = switch_dmode.toInt();

    if(data_std_2 == 6 && data_min_2 == 30 && data_sec2 == 0){
        nightmode="no";
        Serial.println("it is Morning  - switch to Daymode");
    }
    if(akt_time > sw_dm_time && akt_time < sw_nm_time && nightmode=="yes"){
        nightmode="no";
        Serial.println("it is after "+switch_dmode+" - switch to Daymode");
    }
    if(data_std_2 == 18 && data_min_2 == 30 && data_sec2 == 0 ){nightmode="yes";
        Serial.println("it is Afternoon - switch to Nightmode");
    }
    if(akt_time < sw_dm_time && nightmode=="no" or akt_time > sw_nm_time && nightmode=="no"){nightmode="yes";
        Serial.println("it is after "+switch_nmode+" - switch to Nightmode");
    }
      // read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);

  if(lastState == LOW && currentState == HIGH){

    if (nightmode == "yes"){ 
        nightmode = "no";
    Serial.println("Button pressed - switch to Daymode");
        }
    else { 
        nightmode = "yes";
    Serial.println("Button pressed - switch to Nightmode");
        }

  }
  // save the last state
  lastState = currentState;

if (nightmode == "yes"){ on = nightmodeon;}
if (nightmode == "no"){ on = daymodeon;}
  if (IrReceiver.decode()) {
//       Serial.print("hex:");
      //Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
//        Serial.print("result:");
      //Serial.println(IrReceiver.decodedIRData.decodedRawData);

      int dataremote = IrReceiver.decodedIRData.decodedRawData;
#if defined (S_DEBUG_MODE)
              Serial.print("dataremote:");
      Serial.println(dataremote);
#endif
  if(dataremote == -1169817856){
// remote button on
    if(onoff == 0){
        onoff = 1;
    Serial.println("Remote used - Clock on!");
  digitalWrite(RELAY_PIN, HIGH);
    } else {
    Serial.println("Remote used - Clock is already on!");
    }
  }
  if(dataremote == -1203241216){
// remote button off
    if(onoff == 1){
        onoff = 0;
    Serial.println("Remote used - Clock off!");
  digitalWrite(RELAY_PIN, LOW);
    } else {
    Serial.println("Remote used - Clock is already off!");
    }

  }
  if(dataremote == -1153106176){
// remote button 1
    Serial.println("Remote used - show Date!");
 String data_day1 = edata(0,1,data_day);
 String data_day2 = edata(1,2,data_day);
 String data_month1 = edata(0,1,data_month);
 String data_month2 = edata(1,2,data_month);
  zahlen(nightmode,data_day1,data_day2,data_month1,data_month2);
    //leds[28].setRGB(on,0,0); 
    leds[29].setRGB(on,0,0); 

  FastLED.show();
  delay(3000);
  }
  if(dataremote == -1136394496){
// remote button 2
    Serial.println("Remote used - show Year!");

 String data_year1 = edata(0,1,data_year);
 String data_year2 = edata(1,2,data_year);
 String data_year3 = edata(2,3,data_year);
 String data_year4 = edata(3,4,data_year);
  zahlen(nightmode,data_year1,data_year2,data_year3,data_year4);
  FastLED.show();
  delay(3000);
  }
    if(dataremote == -133693696){
// remote button 3

    Serial.println("Remote used - show Temp!");
 String data_temp1 = "0";
 String data_temp2 = "0";
 String data_temp3 = "0";
 String data_temp4 = "0";

if (temp <= 9){
 data_temp2 = edata(0,1,String(temp));
   
} else {
data_temp1 = edata(0,1,String(temp));
data_temp2 = edata(1,2,String(temp));
 }

 //   Serial.print("tempC:");
    //Serial.println(String(tempC));
    //Serial.print("temp:");
    //Serial.println(temp);
    //Serial.print("data_temp1:");
    //Serial.println(data_temp1);
    //Serial.print("data_temp2:");
    //Serial.println(data_temp2);
    //Serial.print("data_temp3:");
    //Serial.println(data_temp3);
    //Serial.print("data_temp4:");
    //Serial.println(data_temp4);


  zahlen(nightmode,data_temp1,data_temp2,data_temp3,data_temp4);
    leds[30].setRGB(0,0,0); 
    leds[31].setRGB(0,0,0); 
    leds[32].setRGB(0,on,0); 
    leds[33].setRGB(0,on,0); 
    leds[34].setRGB(0,on,0); 
    leds[35].setRGB(0,on,0); 
    leds[36].setRGB(0,0,0); 
    leds[37].setRGB(0,0,0); 
    leds[38].setRGB(0,on,0); 
    leds[39].setRGB(0,on,0); 
    leds[40].setRGB(0,on,0); 
    leds[41].setRGB(0,on,0); 
    leds[42].setRGB(0,0,0); 
    leds[43].setRGB(0,0,0); 



    leds[44].setRGB(0,on,0); 
    leds[45].setRGB(0,on,0); 
    leds[46].setRGB(0,on,0); 
    leds[47].setRGB(0,on,0); 
    leds[48].setRGB(0,on,0); 
    leds[49].setRGB(0,0,0); 
    leds[50].setRGB(0,on,0); 
    leds[51].setRGB(0,on,0); 
    leds[52].setRGB(0,0,0); 
    leds[53].setRGB(0,on,0); 
    leds[54].setRGB(0,0,0); 
    leds[55].setRGB(0,0,0); 
    leds[56].setRGB(0,0,0); 
    leds[57].setRGB(0,0,0);
  FastLED.show();
  delay(3000);

  }
if(dataremote == -167117056){
// remote button 4
    Serial.println("Remote used - Numbertest!");
  zahlen(nightmode,"0","0","0","0");
  FastLED.show();
  delay(200);
  zahlen(nightmode,"1","1","1","1");
  FastLED.show();
  delay(200);
  zahlen(nightmode,"2","2","2","2");
  FastLED.show();
  delay(200);
  zahlen(nightmode,"3","3","3","3");
  FastLED.show();
  delay(200);
  zahlen(nightmode,"4","4","4","4");
  FastLED.show();
  delay(200);
  zahlen(nightmode,"5","5","5","5");
  FastLED.show();
  delay(200);
  zahlen(nightmode,"6","6","6","6");
  FastLED.show();
  delay(200);
  zahlen(nightmode,"7","7","7","7");
  FastLED.show();
  delay(200);
  zahlen(nightmode,"8","8","8","8");
  FastLED.show();
  delay(200);
  zahlen(nightmode,"9","9","9","9");
  FastLED.show();
  delay(200);

  }
  if(dataremote == -384368896){
// remote button 5
  myrainbow(40,nightmode,5);             // Flowing rainbow cycle along the whole strip
    Serial.println("Remote used - RainbowTime!");

  }
  if(dataremote == -233963776){
// remote button 6
  roundcolor(nightmode,1,0,0,1,1);
roundcolor(nightmode,1,1,0,1,1);
roundcolor(nightmode,0,1,0,1,1);
roundcolor(nightmode,0,1,1,1,1);
roundcolor(nightmode,0,0,1,1,1);
roundcolor(nightmode,1,0,1,1,1);
             // Flowing rainbow cycle along the whole strip
    Serial.println("Remote used - ColorTime!");

  }
  if(dataremote == -217252096){
// remote button 7
  roundcolor(nightmode,1,0,0,5,5);
    Serial.println("Remote used - roundColorTime!");

  }
  if(dataremote == -1587609856){
// remote button 8
    if (nightmode == "yes"){ 
        nightmode = "no";
    Serial.println("Remote used - switch to Daymode");
        }
    else { 
        nightmode = "yes";
    Serial.println("Remote used - switch to Nightmode");
        }

  }
      IrReceiver.resume(); // Enable receiving of the next value
 
  }

    zahlen(nightmode,data_std1,data_std2,data_min1,data_min2);
    if (blinker == 1){
    leds[28].setRGB(on,0,0); 
    leds[29].setRGB(on,0,0); 
    blinker = 0;
    } else {
    leds[28].setRGB(0,0,0); 
    leds[29].setRGB(0,0,0); 
    blinker = 1;
    }
    leds[58].setRGB(on,on,on); 
    leds[63].setRGB(on,on,on); 
    leds[68].setRGB(on,on,on); 
    leds[73].setRGB(on,on,on); 
    leds[78].setRGB(on,on,on); 
    leds[83].setRGB(on,on,on); 
    leds[88].setRGB(on,on,on); 
    leds[93].setRGB(on,on,on); 
    leds[98].setRGB(on,on,on); 
    leds[103].setRGB(on,on,on); 
    leds[108].setRGB(on,on,on); 
    leds[113].setRGB(on,on,on); 

    leds[std_60].setRGB(0,0,on); 
    leds[min_60].setRGB(0,on,0); 
  leds[sekunde].setRGB(on,0,0); 

 // Serial.print("std_60: ");
 // Serial.println(std_60);
 // Serial.print("min_60: ");
 // Serial.println(min_60);
 // Serial.print("sekunde: ");
 // Serial.println(sekunde);


if (interval2_update == 0 or interval2_epoch >= interval2_update+60){
interval2_update = timeClient.getEpochTime();
  Serial.print(data_std_2);
  Serial.print(":");
  Serial.print(data_min_2);
  Serial.print(":");
  Serial.print(data_sec2);
}
int helligkeit;
if (nightmode == "yes"){ helligkeit = nightmodeon;}
if (nightmode == "no"){ helligkeit = daymodeon;}
if (interval3_update == 0 or interval3_epoch >= interval3_update+1800){
interval3_update = timeClient.getEpochTime();
  Serial.print(" nightmode:");
  Serial.print(nightmode);
  Serial.print(" helligkeit:");
  Serial.println(helligkeit);
}
    //leds[25].setRGB(on,0,on); 

    FastLED.show();

delay(500);
//  for(int i=0; i<NUMPIXELS; i++) {

//    leds[i].setRGB(0, 150, 0);
//    leds[28].setRGB(255,255,255); 
//    leds[29].setRGB(255,255,255); 
//    FastLED.show();
//    delay(DELAYVAL);
//  rainbow(10);             // Flowing rainbow cycle along the whole strip

//  }

}

