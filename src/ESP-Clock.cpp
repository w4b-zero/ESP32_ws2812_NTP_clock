#include <WiFi.h>   //esp32
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SENSOR_PIN  18 // ESP32 pin GIOP21 connected to DS18B20 sensor's DQ pin

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

#define LED_PIN        16
#define NUMPIXELS 118
#define IR_INPUT_PIN 21
#define IR_FEEDBACK_LED_PIN 2


#include <IRremote.hpp>
#include <TinyIRReceiver.hpp>

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 50

//Zeitverschiebung UTC <-> MEZ (Winterzeit) = 3600 Sekunden (1 Stunde)
//Zeitverschiebung UTC <-> MEZ (Sommerzeit) = 7200 Sekunden (2 Stunden)
//const long utcOffsetInSeconds = 7200; //Sommerzeit
const long utcOffsetInSeconds = 3600; //Winterzeit
int MEZ = 0;

char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
int blinker = 1;
String nightmode="no";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

int bright = 10; // gesamte Helligkeit
int on = 255; // Helligkeit voll an
int daymodeon = 255; // Helligkeit voll an
int nightmodeon = 40; // Helligkeit im nachtmodus


void zahlen(String night="no", String zahl1="8", String zahl2="8", String zahl3="8", String zahl4="8"){
if (night == "yes"){ on = nightmodeon;}
if (night == "no"){ on = daymodeon;}

if (zahl1 == "0"){
    pixels.setPixelColor(0, pixels.Color(0,0,on)); 
    pixels.setPixelColor(1, pixels.Color(0,0,on)); 
    pixels.setPixelColor(2, pixels.Color(0,0,on)); 
    pixels.setPixelColor(3, pixels.Color(0,0,on)); 
    pixels.setPixelColor(4, pixels.Color(0,0,on)); 
    pixels.setPixelColor(5, pixels.Color(0,0,0)); 
    pixels.setPixelColor(6, pixels.Color(0,0,on)); 
    pixels.setPixelColor(7, pixels.Color(0,0,on)); 
    pixels.setPixelColor(8, pixels.Color(0,0,0)); 
    pixels.setPixelColor(9, pixels.Color(0,0,on)); 
    pixels.setPixelColor(10, pixels.Color(0,0,on)); 
    pixels.setPixelColor(11, pixels.Color(0,0,on)); 
    pixels.setPixelColor(12, pixels.Color(0,0,on)); 
    pixels.setPixelColor(13, pixels.Color(0,0,on)); 
} else if (zahl1 == "1"){
    pixels.setPixelColor(0, pixels.Color(0,0,0)); 
    pixels.setPixelColor(1, pixels.Color(0,0,0)); 
    pixels.setPixelColor(2, pixels.Color(0,0,0)); 
    pixels.setPixelColor(3, pixels.Color(0,0,0)); 
    pixels.setPixelColor(4, pixels.Color(0,0,0)); 
    pixels.setPixelColor(5, pixels.Color(0,0,0)); 
    pixels.setPixelColor(6, pixels.Color(0,0,0)); 
    pixels.setPixelColor(7, pixels.Color(0,0,0)); 
    pixels.setPixelColor(8, pixels.Color(0,0,0)); 
    pixels.setPixelColor(9, pixels.Color(0,0,0)); 
    pixels.setPixelColor(10, pixels.Color(0,0,on)); 
    pixels.setPixelColor(11, pixels.Color(0,0,on)); 
    pixels.setPixelColor(12, pixels.Color(0,0,on)); 
    pixels.setPixelColor(13, pixels.Color(0,0,on)); 
} else if (zahl1 == "2"){
    pixels.setPixelColor(0, pixels.Color(0,0,0)); 
    pixels.setPixelColor(1, pixels.Color(0,0,0)); 
    pixels.setPixelColor(2, pixels.Color(0,0,on)); 
    pixels.setPixelColor(3, pixels.Color(0,0,on)); 
    pixels.setPixelColor(4, pixels.Color(0,0,on)); 
    pixels.setPixelColor(5, pixels.Color(0,0,on)); 
    pixels.setPixelColor(6, pixels.Color(0,0,on)); 
    pixels.setPixelColor(7, pixels.Color(0,0,on)); 
    pixels.setPixelColor(8, pixels.Color(0,0,on)); 
    pixels.setPixelColor(9, pixels.Color(0,0,on)); 
    pixels.setPixelColor(10, pixels.Color(0,0,0)); 
    pixels.setPixelColor(11, pixels.Color(0,0,0)); 
    pixels.setPixelColor(12, pixels.Color(0,0,on)); 
    pixels.setPixelColor(13, pixels.Color(0,0,on)); 
} else if (zahl1 == "3"){
    pixels.setPixelColor(0, pixels.Color(0,0,0)); 
    pixels.setPixelColor(1, pixels.Color(0,0,0)); 
    pixels.setPixelColor(2, pixels.Color(0,0,0)); 
    pixels.setPixelColor(3, pixels.Color(0,0,0)); 
    pixels.setPixelColor(4, pixels.Color(0,0,on)); 
    pixels.setPixelColor(5, pixels.Color(0,0,on)); 
    pixels.setPixelColor(6, pixels.Color(0,0,on)); 
    pixels.setPixelColor(7, pixels.Color(0,0,on)); 
    pixels.setPixelColor(8, pixels.Color(0,0,on)); 
    pixels.setPixelColor(9, pixels.Color(0,0,on)); 
    pixels.setPixelColor(10, pixels.Color(0,0,on)); 
    pixels.setPixelColor(11, pixels.Color(0,0,on)); 
    pixels.setPixelColor(12, pixels.Color(0,0,on)); 
    pixels.setPixelColor(13, pixels.Color(0,0,on)); 
} else if (zahl1 == "4"){
    pixels.setPixelColor(0, pixels.Color(0,0,on)); 
    pixels.setPixelColor(1, pixels.Color(0,0,on)); 
    pixels.setPixelColor(2, pixels.Color(0,0,on)); 
    pixels.setPixelColor(3, pixels.Color(0,0,on)); 
    pixels.setPixelColor(4, pixels.Color(0,0,0)); 
    pixels.setPixelColor(5, pixels.Color(0,0,on)); 
    pixels.setPixelColor(6, pixels.Color(0,0,0)); 
    pixels.setPixelColor(7, pixels.Color(0,0,0)); 
    pixels.setPixelColor(8, pixels.Color(0,0,on)); 
    pixels.setPixelColor(9, pixels.Color(0,0,0)); 
    pixels.setPixelColor(10, pixels.Color(0,0,on)); 
    pixels.setPixelColor(11, pixels.Color(0,0,on)); 
    pixels.setPixelColor(12, pixels.Color(0,0,on)); 
    pixels.setPixelColor(13, pixels.Color(0,0,on)); 
} else if (zahl1 == "5"){
    pixels.setPixelColor(0, pixels.Color(0,0,on)); 
    pixels.setPixelColor(1, pixels.Color(0,0,on)); 
    pixels.setPixelColor(2, pixels.Color(0,0,0)); 
    pixels.setPixelColor(3, pixels.Color(0,0,0)); 
    pixels.setPixelColor(4, pixels.Color(0,0,on)); 
    pixels.setPixelColor(5, pixels.Color(0,0,on)); 
    pixels.setPixelColor(6, pixels.Color(0,0,on)); 
    pixels.setPixelColor(7, pixels.Color(0,0,on)); 
    pixels.setPixelColor(8, pixels.Color(0,0,on)); 
    pixels.setPixelColor(9, pixels.Color(0,0,on)); 
    pixels.setPixelColor(10, pixels.Color(0,0,on)); 
    pixels.setPixelColor(11, pixels.Color(0,0,on)); 
    pixels.setPixelColor(12, pixels.Color(0,0,0)); 
    pixels.setPixelColor(13, pixels.Color(0,0,0)); 
} else if (zahl1 == "6"){
    pixels.setPixelColor(0, pixels.Color(0,0,on)); 
    pixels.setPixelColor(1, pixels.Color(0,0,on)); 
    pixels.setPixelColor(2, pixels.Color(0,0,on)); 
    pixels.setPixelColor(3, pixels.Color(0,0,on)); 
    pixels.setPixelColor(4, pixels.Color(0,0,on)); 
    pixels.setPixelColor(5, pixels.Color(0,0,on)); 
    pixels.setPixelColor(6, pixels.Color(0,0,on)); 
    pixels.setPixelColor(7, pixels.Color(0,0,on)); 
    pixels.setPixelColor(8, pixels.Color(0,0,on)); 
    pixels.setPixelColor(9, pixels.Color(0,0,on)); 
    pixels.setPixelColor(10, pixels.Color(0,0,on)); 
    pixels.setPixelColor(11, pixels.Color(0,0,on)); 
    pixels.setPixelColor(12, pixels.Color(0,0,0)); 
    pixels.setPixelColor(13, pixels.Color(0,0,0)); 
} else if (zahl1 == "7"){
    pixels.setPixelColor(0, pixels.Color(0,0,0)); 
    pixels.setPixelColor(1, pixels.Color(0,0,0)); 
    pixels.setPixelColor(2, pixels.Color(0,0,0)); 
    pixels.setPixelColor(3, pixels.Color(0,0,0)); 
    pixels.setPixelColor(4, pixels.Color(0,0,0)); 
    pixels.setPixelColor(5, pixels.Color(0,0,0)); 
    pixels.setPixelColor(6, pixels.Color(0,0,on)); 
    pixels.setPixelColor(7, pixels.Color(0,0,on)); 
    pixels.setPixelColor(8, pixels.Color(0,0,0)); 
    pixels.setPixelColor(9, pixels.Color(0,0,0)); 
    pixels.setPixelColor(10, pixels.Color(0,0,on)); 
    pixels.setPixelColor(11, pixels.Color(0,0,on)); 
    pixels.setPixelColor(12, pixels.Color(0,0,on)); 
    pixels.setPixelColor(13, pixels.Color(0,0,on)); 
} else if (zahl1 == "8"){
    pixels.setPixelColor(0, pixels.Color(0,0,on)); 
    pixels.setPixelColor(1, pixels.Color(0,0,on)); 
    pixels.setPixelColor(2, pixels.Color(0,0,on)); 
    pixels.setPixelColor(3, pixels.Color(0,0,on)); 
    pixels.setPixelColor(4, pixels.Color(0,0,on)); 
    pixels.setPixelColor(5, pixels.Color(0,0,on)); 
    pixels.setPixelColor(6, pixels.Color(0,0,on)); 
    pixels.setPixelColor(7, pixels.Color(0,0,on)); 
    pixels.setPixelColor(8, pixels.Color(0,0,on)); 
    pixels.setPixelColor(9, pixels.Color(0,0,on)); 
    pixels.setPixelColor(10, pixels.Color(0,0,on)); 
    pixels.setPixelColor(11, pixels.Color(0,0,on)); 
    pixels.setPixelColor(12, pixels.Color(0,0,on)); 
    pixels.setPixelColor(13, pixels.Color(0,0,on)); 
} else if (zahl1 == "9"){
    pixels.setPixelColor(0, pixels.Color(0,0,on)); 
    pixels.setPixelColor(1, pixels.Color(0,0,on)); 
    pixels.setPixelColor(2, pixels.Color(0,0,0)); 
    pixels.setPixelColor(3, pixels.Color(0,0,0)); 
    pixels.setPixelColor(4, pixels.Color(0,0,on)); 
    pixels.setPixelColor(5, pixels.Color(0,0,on)); 
    pixels.setPixelColor(6, pixels.Color(0,0,on)); 
    pixels.setPixelColor(7, pixels.Color(0,0,on)); 
    pixels.setPixelColor(8, pixels.Color(0,0,on)); 
    pixels.setPixelColor(9, pixels.Color(0,0,on)); 
    pixels.setPixelColor(10, pixels.Color(0,0,on)); 
    pixels.setPixelColor(11, pixels.Color(0,0,on)); 
    pixels.setPixelColor(12, pixels.Color(0,0,on)); 
    pixels.setPixelColor(13, pixels.Color(0,0,on)); 
}





if (zahl2 == "0"){
    pixels.setPixelColor(14, pixels.Color(0,0,on)); 
    pixels.setPixelColor(15, pixels.Color(0,0,on)); 
    pixels.setPixelColor(16, pixels.Color(0,0,on)); 
    pixels.setPixelColor(17, pixels.Color(0,0,on)); 
    pixels.setPixelColor(18, pixels.Color(0,0,on)); 
    pixels.setPixelColor(19, pixels.Color(0,0,0)); 
    pixels.setPixelColor(20, pixels.Color(0,0,on)); 
    pixels.setPixelColor(21, pixels.Color(0,0,on)); 
    pixels.setPixelColor(22, pixels.Color(0,0,0)); 
    pixels.setPixelColor(23, pixels.Color(0,0,on)); 
    pixels.setPixelColor(24, pixels.Color(0,0,on)); 
    pixels.setPixelColor(25, pixels.Color(0,0,on)); 
    pixels.setPixelColor(26, pixels.Color(0,0,on)); 
    pixels.setPixelColor(27, pixels.Color(0,0,on)); 
} else if (zahl2 == "1"){
    pixels.setPixelColor(14, pixels.Color(0,0,0)); 
    pixels.setPixelColor(15, pixels.Color(0,0,0)); 
    pixels.setPixelColor(16, pixels.Color(0,0,0)); 
    pixels.setPixelColor(17, pixels.Color(0,0,0)); 
    pixels.setPixelColor(18, pixels.Color(0,0,0)); 
    pixels.setPixelColor(19, pixels.Color(0,0,0)); 
    pixels.setPixelColor(20, pixels.Color(0,0,0)); 
    pixels.setPixelColor(21, pixels.Color(0,0,0)); 
    pixels.setPixelColor(22, pixels.Color(0,0,0)); 
    pixels.setPixelColor(23, pixels.Color(0,0,0)); 
    pixels.setPixelColor(24, pixels.Color(0,0,on)); 
    pixels.setPixelColor(25, pixels.Color(0,0,on)); 
    pixels.setPixelColor(26, pixels.Color(0,0,on)); 
    pixels.setPixelColor(27, pixels.Color(0,0,on)); 
} else if (zahl2 == "2"){
    pixels.setPixelColor(14, pixels.Color(0,0,0)); 
    pixels.setPixelColor(15, pixels.Color(0,0,0)); 
    pixels.setPixelColor(16, pixels.Color(0,0,on)); 
    pixels.setPixelColor(17, pixels.Color(0,0,on)); 
    pixels.setPixelColor(18, pixels.Color(0,0,on)); 
    pixels.setPixelColor(19, pixels.Color(0,0,on)); 
    pixels.setPixelColor(20, pixels.Color(0,0,on)); 
    pixels.setPixelColor(21, pixels.Color(0,0,on)); 
    pixels.setPixelColor(22, pixels.Color(0,0,on)); 
    pixels.setPixelColor(23, pixels.Color(0,0,on)); 
    pixels.setPixelColor(24, pixels.Color(0,0,0)); 
    pixels.setPixelColor(25, pixels.Color(0,0,0)); 
    pixels.setPixelColor(26, pixels.Color(0,0,on)); 
    pixels.setPixelColor(27, pixels.Color(0,0,on)); 
} else if (zahl2 == "3"){
    pixels.setPixelColor(14, pixels.Color(0,0,0)); 
    pixels.setPixelColor(15, pixels.Color(0,0,0)); 
    pixels.setPixelColor(16, pixels.Color(0,0,0)); 
    pixels.setPixelColor(17, pixels.Color(0,0,0)); 
    pixels.setPixelColor(18, pixels.Color(0,0,on)); 
    pixels.setPixelColor(19, pixels.Color(0,0,on)); 
    pixels.setPixelColor(20, pixels.Color(0,0,on)); 
    pixels.setPixelColor(21, pixels.Color(0,0,on)); 
    pixels.setPixelColor(22, pixels.Color(0,0,on)); 
    pixels.setPixelColor(23, pixels.Color(0,0,on)); 
    pixels.setPixelColor(24, pixels.Color(0,0,on)); 
    pixels.setPixelColor(25, pixels.Color(0,0,on)); 
    pixels.setPixelColor(26, pixels.Color(0,0,on)); 
    pixels.setPixelColor(27, pixels.Color(0,0,on)); 
} else if (zahl2 == "4"){
    pixels.setPixelColor(14, pixels.Color(0,0,on)); 
    pixels.setPixelColor(15, pixels.Color(0,0,on)); 
    pixels.setPixelColor(16, pixels.Color(0,0,0)); 
    pixels.setPixelColor(17, pixels.Color(0,0,0)); 
    pixels.setPixelColor(18, pixels.Color(0,0,0)); 
    pixels.setPixelColor(19, pixels.Color(0,0,on)); 
    pixels.setPixelColor(20, pixels.Color(0,0,0)); 
    pixels.setPixelColor(21, pixels.Color(0,0,0)); 
    pixels.setPixelColor(22, pixels.Color(0,0,on)); 
    pixels.setPixelColor(23, pixels.Color(0,0,0)); 
    pixels.setPixelColor(24, pixels.Color(0,0,on)); 
    pixels.setPixelColor(25, pixels.Color(0,0,on)); 
    pixels.setPixelColor(26, pixels.Color(0,0,on)); 
    pixels.setPixelColor(27, pixels.Color(0,0,on)); 
} else if (zahl2 == "5"){
    pixels.setPixelColor(14, pixels.Color(0,0,on)); 
    pixels.setPixelColor(15, pixels.Color(0,0,on)); 
    pixels.setPixelColor(16, pixels.Color(0,0,0)); 
    pixels.setPixelColor(17, pixels.Color(0,0,0)); 
    pixels.setPixelColor(18, pixels.Color(0,0,on)); 
    pixels.setPixelColor(19, pixels.Color(0,0,on)); 
    pixels.setPixelColor(20, pixels.Color(0,0,on)); 
    pixels.setPixelColor(21, pixels.Color(0,0,on)); 
    pixels.setPixelColor(22, pixels.Color(0,0,on)); 
    pixels.setPixelColor(23, pixels.Color(0,0,on)); 
    pixels.setPixelColor(24, pixels.Color(0,0,on)); 
    pixels.setPixelColor(25, pixels.Color(0,0,on)); 
    pixels.setPixelColor(26, pixels.Color(0,0,0)); 
    pixels.setPixelColor(27, pixels.Color(0,0,0)); 
} else if (zahl2 == "6"){
    pixels.setPixelColor(14, pixels.Color(0,0,on)); 
    pixels.setPixelColor(15, pixels.Color(0,0,on)); 
    pixels.setPixelColor(16, pixels.Color(0,0,on)); 
    pixels.setPixelColor(17, pixels.Color(0,0,on)); 
    pixels.setPixelColor(18, pixels.Color(0,0,on)); 
    pixels.setPixelColor(19, pixels.Color(0,0,on)); 
    pixels.setPixelColor(20, pixels.Color(0,0,on)); 
    pixels.setPixelColor(21, pixels.Color(0,0,on)); 
    pixels.setPixelColor(22, pixels.Color(0,0,on)); 
    pixels.setPixelColor(23, pixels.Color(0,0,on)); 
    pixels.setPixelColor(24, pixels.Color(0,0,on)); 
    pixels.setPixelColor(25, pixels.Color(0,0,on)); 
    pixels.setPixelColor(26, pixels.Color(0,0,0)); 
    pixels.setPixelColor(27, pixels.Color(0,0,0)); 
} else if (zahl2 == "7"){
    pixels.setPixelColor(14, pixels.Color(0,0,0)); 
    pixels.setPixelColor(15, pixels.Color(0,0,0)); 
    pixels.setPixelColor(16, pixels.Color(0,0,0)); 
    pixels.setPixelColor(17, pixels.Color(0,0,0)); 
    pixels.setPixelColor(18, pixels.Color(0,0,0)); 
    pixels.setPixelColor(19, pixels.Color(0,0,0)); 
    pixels.setPixelColor(20, pixels.Color(0,0,on)); 
    pixels.setPixelColor(21, pixels.Color(0,0,on)); 
    pixels.setPixelColor(22, pixels.Color(0,0,0)); 
    pixels.setPixelColor(23, pixels.Color(0,0,0)); 
    pixels.setPixelColor(24, pixels.Color(0,0,on)); 
    pixels.setPixelColor(25, pixels.Color(0,0,on)); 
    pixels.setPixelColor(26, pixels.Color(0,0,on)); 
    pixels.setPixelColor(27, pixels.Color(0,0,on)); 
} else if (zahl2 == "8"){
    pixels.setPixelColor(14, pixels.Color(0,0,on)); 
    pixels.setPixelColor(15, pixels.Color(0,0,on)); 
    pixels.setPixelColor(16, pixels.Color(0,0,on)); 
    pixels.setPixelColor(17, pixels.Color(0,0,on)); 
    pixels.setPixelColor(18, pixels.Color(0,0,on)); 
    pixels.setPixelColor(19, pixels.Color(0,0,on)); 
    pixels.setPixelColor(20, pixels.Color(0,0,on)); 
    pixels.setPixelColor(21, pixels.Color(0,0,on)); 
    pixels.setPixelColor(22, pixels.Color(0,0,on)); 
    pixels.setPixelColor(23, pixels.Color(0,0,on)); 
    pixels.setPixelColor(24, pixels.Color(0,0,on)); 
    pixels.setPixelColor(25, pixels.Color(0,0,on)); 
    pixels.setPixelColor(26, pixels.Color(0,0,on)); 
    pixels.setPixelColor(27, pixels.Color(0,0,on)); 
} else if (zahl2 == "9"){
    pixels.setPixelColor(14, pixels.Color(0,0,on)); 
    pixels.setPixelColor(15, pixels.Color(0,0,on)); 
    pixels.setPixelColor(16, pixels.Color(0,0,0)); 
    pixels.setPixelColor(17, pixels.Color(0,0,0)); 
    pixels.setPixelColor(18, pixels.Color(0,0,on)); 
    pixels.setPixelColor(19, pixels.Color(0,0,on)); 
    pixels.setPixelColor(20, pixels.Color(0,0,on)); 
    pixels.setPixelColor(21, pixels.Color(0,0,on)); 
    pixels.setPixelColor(22, pixels.Color(0,0,on)); 
    pixels.setPixelColor(23, pixels.Color(0,0,on)); 
    pixels.setPixelColor(24, pixels.Color(0,0,on)); 
    pixels.setPixelColor(25, pixels.Color(0,0,on)); 
    pixels.setPixelColor(26, pixels.Color(0,0,on)); 
    pixels.setPixelColor(27, pixels.Color(0,0,on)); 
}




if (zahl3 == "0"){
    pixels.setPixelColor(30, pixels.Color(0,on,0)); 
    pixels.setPixelColor(31, pixels.Color(0,on,0)); 
    pixels.setPixelColor(32, pixels.Color(0,on,0)); 
    pixels.setPixelColor(33, pixels.Color(0,on,0)); 
    pixels.setPixelColor(34, pixels.Color(0,on,0)); 
    pixels.setPixelColor(35, pixels.Color(0,0,0)); 
    pixels.setPixelColor(36, pixels.Color(0,on,0)); 
    pixels.setPixelColor(37, pixels.Color(0,on,0)); 
    pixels.setPixelColor(38, pixels.Color(0,0,0)); 
    pixels.setPixelColor(39, pixels.Color(0,on,0)); 
    pixels.setPixelColor(40, pixels.Color(0,on,0)); 
    pixels.setPixelColor(41, pixels.Color(0,on,0)); 
    pixels.setPixelColor(42, pixels.Color(0,on,0)); 
    pixels.setPixelColor(43, pixels.Color(0,on,0)); 
} else if (zahl3 == "1"){
    pixels.setPixelColor(30, pixels.Color(0,0,0)); 
    pixels.setPixelColor(31, pixels.Color(0,0,0)); 
    pixels.setPixelColor(32, pixels.Color(0,0,0)); 
    pixels.setPixelColor(33, pixels.Color(0,0,0)); 
    pixels.setPixelColor(34, pixels.Color(0,0,0)); 
    pixels.setPixelColor(35, pixels.Color(0,0,0)); 
    pixels.setPixelColor(36, pixels.Color(0,0,0)); 
    pixels.setPixelColor(37, pixels.Color(0,0,0)); 
    pixels.setPixelColor(38, pixels.Color(0,0,0)); 
    pixels.setPixelColor(39, pixels.Color(0,0,0)); 
    pixels.setPixelColor(40, pixels.Color(0,on,0)); 
    pixels.setPixelColor(41, pixels.Color(0,on,0)); 
    pixels.setPixelColor(42, pixels.Color(0,on,0)); 
    pixels.setPixelColor(43, pixels.Color(0,on,0)); 
} else if (zahl3 == "2"){
    pixels.setPixelColor(30, pixels.Color(0,on,0)); 
    pixels.setPixelColor(31, pixels.Color(0,on,0)); 
    pixels.setPixelColor(32, pixels.Color(0,0,0)); 
    pixels.setPixelColor(33, pixels.Color(0,0,0)); 
    pixels.setPixelColor(34, pixels.Color(0,on,0)); 
    pixels.setPixelColor(35, pixels.Color(0,on,0)); 
    pixels.setPixelColor(36, pixels.Color(0,on,0)); 
    pixels.setPixelColor(37, pixels.Color(0,on,0)); 
    pixels.setPixelColor(38, pixels.Color(0,on,0)); 
    pixels.setPixelColor(39, pixels.Color(0,on,0)); 
    pixels.setPixelColor(40, pixels.Color(0,on,0)); 
    pixels.setPixelColor(41, pixels.Color(0,on,0)); 
    pixels.setPixelColor(42, pixels.Color(0,0,0)); 
    pixels.setPixelColor(43, pixels.Color(0,0,0)); 
} else if (zahl3 == "3"){
    pixels.setPixelColor(30, pixels.Color(0,0,0)); 
    pixels.setPixelColor(31, pixels.Color(0,0,0)); 
    pixels.setPixelColor(32, pixels.Color(0,0,0)); 
    pixels.setPixelColor(33, pixels.Color(0,0,0)); 
    pixels.setPixelColor(34, pixels.Color(0,on,0)); 
    pixels.setPixelColor(35, pixels.Color(0,on,0)); 
    pixels.setPixelColor(36, pixels.Color(0,on,0)); 
    pixels.setPixelColor(37, pixels.Color(0,on,0)); 
    pixels.setPixelColor(38, pixels.Color(0,on,0)); 
    pixels.setPixelColor(39, pixels.Color(0,on,0)); 
    pixels.setPixelColor(40, pixels.Color(0,on,0)); 
    pixels.setPixelColor(41, pixels.Color(0,on,0)); 
    pixels.setPixelColor(42, pixels.Color(0,on,0)); 
    pixels.setPixelColor(43, pixels.Color(0,on,0)); 
} else if (zahl3 == "4"){
    pixels.setPixelColor(30, pixels.Color(0,0,0)); 
    pixels.setPixelColor(31, pixels.Color(0,0,0)); 
    pixels.setPixelColor(32, pixels.Color(0,on,0)); 
    pixels.setPixelColor(33, pixels.Color(0,on,0)); 
    pixels.setPixelColor(34, pixels.Color(0,0,0)); 
    pixels.setPixelColor(35, pixels.Color(0,on,0)); 
    pixels.setPixelColor(36, pixels.Color(0,0,0)); 
    pixels.setPixelColor(37, pixels.Color(0,0,0)); 
    pixels.setPixelColor(38, pixels.Color(0,on,0)); 
    pixels.setPixelColor(39, pixels.Color(0,0,0)); 
    pixels.setPixelColor(40, pixels.Color(0,on,0)); 
    pixels.setPixelColor(41, pixels.Color(0,on,0)); 
    pixels.setPixelColor(42, pixels.Color(0,on,0)); 
    pixels.setPixelColor(43, pixels.Color(0,on,0)); 
} else if (zahl3 == "5"){
    pixels.setPixelColor(30, pixels.Color(0,0,0)); 
    pixels.setPixelColor(31, pixels.Color(0,0,0)); 
    pixels.setPixelColor(32, pixels.Color(0,on,0)); 
    pixels.setPixelColor(33, pixels.Color(0,on,0)); 
    pixels.setPixelColor(34, pixels.Color(0,on,0)); 
    pixels.setPixelColor(35, pixels.Color(0,on,0)); 
    pixels.setPixelColor(36, pixels.Color(0,on,0)); 
    pixels.setPixelColor(37, pixels.Color(0,on,0)); 
    pixels.setPixelColor(38, pixels.Color(0,on,0)); 
    pixels.setPixelColor(39, pixels.Color(0,on,0)); 
    pixels.setPixelColor(40, pixels.Color(0,0,0)); 
    pixels.setPixelColor(41, pixels.Color(0,0,0)); 
    pixels.setPixelColor(42, pixels.Color(0,on,0)); 
    pixels.setPixelColor(43, pixels.Color(0,on,0)); 
} else if (zahl3 == "6"){
    pixels.setPixelColor(30, pixels.Color(0,on,0)); 
    pixels.setPixelColor(31, pixels.Color(0,on,0)); 
    pixels.setPixelColor(32, pixels.Color(0,on,0)); 
    pixels.setPixelColor(33, pixels.Color(0,on,0)); 
    pixels.setPixelColor(34, pixels.Color(0,on,0)); 
    pixels.setPixelColor(35, pixels.Color(0,on,0)); 
    pixels.setPixelColor(36, pixels.Color(0,on,0)); 
    pixels.setPixelColor(37, pixels.Color(0,on,0)); 
    pixels.setPixelColor(38, pixels.Color(0,on,0)); 
    pixels.setPixelColor(39, pixels.Color(0,on,0)); 
    pixels.setPixelColor(40, pixels.Color(0,0,0)); 
    pixels.setPixelColor(41, pixels.Color(0,0,0)); 
    pixels.setPixelColor(42, pixels.Color(0,on,0)); 
    pixels.setPixelColor(43, pixels.Color(0,on,0)); 
} else if (zahl3 == "7"){
    pixels.setPixelColor(30, pixels.Color(0,0,0)); 
    pixels.setPixelColor(31, pixels.Color(0,0,0)); 
    pixels.setPixelColor(32, pixels.Color(0,0,0)); 
    pixels.setPixelColor(33, pixels.Color(0,0,0)); 
    pixels.setPixelColor(34, pixels.Color(0,on,0)); 
    pixels.setPixelColor(35, pixels.Color(0,0,0)); 
    pixels.setPixelColor(36, pixels.Color(0,0,0)); 
    pixels.setPixelColor(37, pixels.Color(0,0,0)); 
    pixels.setPixelColor(38, pixels.Color(0,0,0)); 
    pixels.setPixelColor(39, pixels.Color(0,on,0)); 
    pixels.setPixelColor(40, pixels.Color(0,on,0)); 
    pixels.setPixelColor(41, pixels.Color(0,on,0)); 
    pixels.setPixelColor(42, pixels.Color(0,on,0)); 
    pixels.setPixelColor(43, pixels.Color(0,on,0)); 
} else if (zahl3 == "8"){
    pixels.setPixelColor(30, pixels.Color(0,on,0)); 
    pixels.setPixelColor(31, pixels.Color(0,on,0)); 
    pixels.setPixelColor(32, pixels.Color(0,on,0)); 
    pixels.setPixelColor(33, pixels.Color(0,on,0)); 
    pixels.setPixelColor(34, pixels.Color(0,on,0)); 
    pixels.setPixelColor(35, pixels.Color(0,on,0)); 
    pixels.setPixelColor(36, pixels.Color(0,on,0)); 
    pixels.setPixelColor(37, pixels.Color(0,on,0)); 
    pixels.setPixelColor(38, pixels.Color(0,on,0)); 
    pixels.setPixelColor(39, pixels.Color(0,on,0)); 
    pixels.setPixelColor(40, pixels.Color(0,on,0)); 
    pixels.setPixelColor(41, pixels.Color(0,on,0)); 
    pixels.setPixelColor(42, pixels.Color(0,on,0)); 
    pixels.setPixelColor(43, pixels.Color(0,on,0)); 
} else if (zahl3 == "9"){
    pixels.setPixelColor(30, pixels.Color(0,0,0)); 
    pixels.setPixelColor(31, pixels.Color(0,0,0)); 
    pixels.setPixelColor(32, pixels.Color(0,on,0)); 
    pixels.setPixelColor(33, pixels.Color(0,on,0)); 
    pixels.setPixelColor(34, pixels.Color(0,on,0)); 
    pixels.setPixelColor(35, pixels.Color(0,on,0)); 
    pixels.setPixelColor(36, pixels.Color(0,on,0)); 
    pixels.setPixelColor(37, pixels.Color(0,on,0)); 
    pixels.setPixelColor(38, pixels.Color(0,on,0)); 
    pixels.setPixelColor(39, pixels.Color(0,on,0)); 
    pixels.setPixelColor(40, pixels.Color(0,on,0)); 
    pixels.setPixelColor(41, pixels.Color(0,on,0)); 
    pixels.setPixelColor(42, pixels.Color(0,on,0)); 
    pixels.setPixelColor(43, pixels.Color(0,on,0)); 
}
if (zahl4 == "0"){
    pixels.setPixelColor(44, pixels.Color(0,on,0)); 
    pixels.setPixelColor(45, pixels.Color(0,on,0)); 
    pixels.setPixelColor(46, pixels.Color(0,on,0)); 
    pixels.setPixelColor(47, pixels.Color(0,on,0)); 
    pixels.setPixelColor(48, pixels.Color(0,on,0)); 
    pixels.setPixelColor(49, pixels.Color(0,0,0)); 
    pixels.setPixelColor(50, pixels.Color(0,on,0)); 
    pixels.setPixelColor(51, pixels.Color(0,on,0)); 
    pixels.setPixelColor(52, pixels.Color(0,0,0)); 
    pixels.setPixelColor(53, pixels.Color(0,on,0)); 
    pixels.setPixelColor(54, pixels.Color(0,on,0)); 
    pixels.setPixelColor(55, pixels.Color(0,on,0)); 
    pixels.setPixelColor(56, pixels.Color(0,on,0)); 
    pixels.setPixelColor(57, pixels.Color(0,on,0)); 
} else if (zahl4 == "1"){
    pixels.setPixelColor(44, pixels.Color(0,0,0)); 
    pixels.setPixelColor(45, pixels.Color(0,0,0)); 
    pixels.setPixelColor(46, pixels.Color(0,0,0)); 
    pixels.setPixelColor(47, pixels.Color(0,0,0)); 
    pixels.setPixelColor(48, pixels.Color(0,0,0)); 
    pixels.setPixelColor(49, pixels.Color(0,0,0)); 
    pixels.setPixelColor(50, pixels.Color(0,0,0)); 
    pixels.setPixelColor(51, pixels.Color(0,0,0)); 
    pixels.setPixelColor(52, pixels.Color(0,0,0)); 
    pixels.setPixelColor(53, pixels.Color(0,0,0)); 
    pixels.setPixelColor(54, pixels.Color(0,on,0)); 
    pixels.setPixelColor(55, pixels.Color(0,on,0)); 
    pixels.setPixelColor(56, pixels.Color(0,on,0)); 
    pixels.setPixelColor(57, pixels.Color(0,on,0)); 
} else if (zahl4 == "2"){
    pixels.setPixelColor(44, pixels.Color(0,on,0)); 
    pixels.setPixelColor(45, pixels.Color(0,on,0)); 
    pixels.setPixelColor(46, pixels.Color(0,0,0)); 
    pixels.setPixelColor(47, pixels.Color(0,0,0)); 
    pixels.setPixelColor(48, pixels.Color(0,on,0)); 
    pixels.setPixelColor(49, pixels.Color(0,on,0)); 
    pixels.setPixelColor(50, pixels.Color(0,on,0)); 
    pixels.setPixelColor(51, pixels.Color(0,on,0)); 
    pixels.setPixelColor(52, pixels.Color(0,on,0)); 
    pixels.setPixelColor(53, pixels.Color(0,on,0)); 
    pixels.setPixelColor(54, pixels.Color(0,on,0)); 
    pixels.setPixelColor(55, pixels.Color(0,on,0)); 
    pixels.setPixelColor(56, pixels.Color(0,0,0)); 
    pixels.setPixelColor(57, pixels.Color(0,0,0)); 
} else if (zahl4 == "3"){
    pixels.setPixelColor(44, pixels.Color(0,0,0)); 
    pixels.setPixelColor(45, pixels.Color(0,0,0)); 
    pixels.setPixelColor(46, pixels.Color(0,0,0)); 
    pixels.setPixelColor(47, pixels.Color(0,0,0)); 
    pixels.setPixelColor(48, pixels.Color(0,on,0)); 
    pixels.setPixelColor(49, pixels.Color(0,on,0)); 
    pixels.setPixelColor(50, pixels.Color(0,on,0)); 
    pixels.setPixelColor(51, pixels.Color(0,on,0)); 
    pixels.setPixelColor(52, pixels.Color(0,on,0)); 
    pixels.setPixelColor(53, pixels.Color(0,on,0)); 
    pixels.setPixelColor(54, pixels.Color(0,on,0)); 
    pixels.setPixelColor(55, pixels.Color(0,on,0)); 
    pixels.setPixelColor(56, pixels.Color(0,on,0)); 
    pixels.setPixelColor(57, pixels.Color(0,on,0)); 
} else if (zahl4 == "4"){
    pixels.setPixelColor(44, pixels.Color(0,0,0)); 
    pixels.setPixelColor(45, pixels.Color(0,0,0)); 
    pixels.setPixelColor(46, pixels.Color(0,on,0)); 
    pixels.setPixelColor(47, pixels.Color(0,on,0)); 
    pixels.setPixelColor(48, pixels.Color(0,0,0)); 
    pixels.setPixelColor(49, pixels.Color(0,on,0)); 
    pixels.setPixelColor(50, pixels.Color(0,0,0)); 
    pixels.setPixelColor(51, pixels.Color(0,0,0)); 
    pixels.setPixelColor(52, pixels.Color(0,on,0)); 
    pixels.setPixelColor(53, pixels.Color(0,0,0)); 
    pixels.setPixelColor(54, pixels.Color(0,on,0)); 
    pixels.setPixelColor(55, pixels.Color(0,on,0)); 
    pixels.setPixelColor(56, pixels.Color(0,on,0)); 
    pixels.setPixelColor(57, pixels.Color(0,on,0)); 
} else if (zahl4 == "5"){
    pixels.setPixelColor(44, pixels.Color(0,0,0)); 
    pixels.setPixelColor(45, pixels.Color(0,0,0)); 
    pixels.setPixelColor(46, pixels.Color(0,on,0)); 
    pixels.setPixelColor(47, pixels.Color(0,on,0)); 
    pixels.setPixelColor(48, pixels.Color(0,on,0)); 
    pixels.setPixelColor(49, pixels.Color(0,on,0)); 
    pixels.setPixelColor(50, pixels.Color(0,on,0)); 
    pixels.setPixelColor(51, pixels.Color(0,on,0)); 
    pixels.setPixelColor(52, pixels.Color(0,on,0)); 
    pixels.setPixelColor(53, pixels.Color(0,on,0)); 
    pixels.setPixelColor(54, pixels.Color(0,0,0)); 
    pixels.setPixelColor(55, pixels.Color(0,0,0)); 
    pixels.setPixelColor(56, pixels.Color(0,on,0)); 
    pixels.setPixelColor(57, pixels.Color(0,on,0)); 
} else if (zahl4 == "6"){
    pixels.setPixelColor(44, pixels.Color(0,on,0)); 
    pixels.setPixelColor(45, pixels.Color(0,on,0)); 
    pixels.setPixelColor(46, pixels.Color(0,on,0)); 
    pixels.setPixelColor(47, pixels.Color(0,on,0)); 
    pixels.setPixelColor(48, pixels.Color(0,on,0)); 
    pixels.setPixelColor(49, pixels.Color(0,on,0)); 
    pixels.setPixelColor(50, pixels.Color(0,on,0)); 
    pixels.setPixelColor(51, pixels.Color(0,on,0)); 
    pixels.setPixelColor(52, pixels.Color(0,on,0)); 
    pixels.setPixelColor(53, pixels.Color(0,on,0)); 
    pixels.setPixelColor(54, pixels.Color(0,0,0)); 
    pixels.setPixelColor(55, pixels.Color(0,0,0)); 
    pixels.setPixelColor(56, pixels.Color(0,on,0)); 
    pixels.setPixelColor(57, pixels.Color(0,on,0)); 
} else if (zahl4 == "7"){
    pixels.setPixelColor(44, pixels.Color(0,0,0)); 
    pixels.setPixelColor(45, pixels.Color(0,0,0)); 
    pixels.setPixelColor(46, pixels.Color(0,0,0)); 
    pixels.setPixelColor(47, pixels.Color(0,0,0)); 
    pixels.setPixelColor(48, pixels.Color(0,on,0)); 
    pixels.setPixelColor(49, pixels.Color(0,0,0)); 
    pixels.setPixelColor(50, pixels.Color(0,0,0)); 
    pixels.setPixelColor(51, pixels.Color(0,0,0)); 
    pixels.setPixelColor(52, pixels.Color(0,0,0)); 
    pixels.setPixelColor(53, pixels.Color(0,on,0)); 
    pixels.setPixelColor(54, pixels.Color(0,on,0)); 
    pixels.setPixelColor(55, pixels.Color(0,on,0)); 
    pixels.setPixelColor(56, pixels.Color(0,on,0)); 
    pixels.setPixelColor(57, pixels.Color(0,on,0)); 
} else if (zahl4 == "8"){
    pixels.setPixelColor(44, pixels.Color(0,on,0)); 
    pixels.setPixelColor(45, pixels.Color(0,on,0)); 
    pixels.setPixelColor(46, pixels.Color(0,on,0)); 
    pixels.setPixelColor(47, pixels.Color(0,on,0)); 
    pixels.setPixelColor(48, pixels.Color(0,on,0)); 
    pixels.setPixelColor(49, pixels.Color(0,on,0)); 
    pixels.setPixelColor(50, pixels.Color(0,on,0)); 
    pixels.setPixelColor(51, pixels.Color(0,on,0)); 
    pixels.setPixelColor(52, pixels.Color(0,on,0)); 
    pixels.setPixelColor(53, pixels.Color(0,on,0)); 
    pixels.setPixelColor(54, pixels.Color(0,on,0)); 
    pixels.setPixelColor(55, pixels.Color(0,on,0)); 
    pixels.setPixelColor(56, pixels.Color(0,on,0)); 
    pixels.setPixelColor(57, pixels.Color(0,on,0)); 
} else if (zahl4 == "9"){
    pixels.setPixelColor(44, pixels.Color(0,0,0)); 
    pixels.setPixelColor(45, pixels.Color(0,0,0)); 
    pixels.setPixelColor(46, pixels.Color(0,on,0)); 
    pixels.setPixelColor(47, pixels.Color(0,on,0)); 
    pixels.setPixelColor(48, pixels.Color(0,on,0)); 
    pixels.setPixelColor(49, pixels.Color(0,on,0)); 
    pixels.setPixelColor(50, pixels.Color(0,on,0)); 
    pixels.setPixelColor(51, pixels.Color(0,on,0)); 
    pixels.setPixelColor(52, pixels.Color(0,on,0)); 
    pixels.setPixelColor(53, pixels.Color(0,on,0)); 
    pixels.setPixelColor(54, pixels.Color(0,on,0)); 
    pixels.setPixelColor(55, pixels.Color(0,on,0)); 
    pixels.setPixelColor(56, pixels.Color(0,on,0)); 
    pixels.setPixelColor(57, pixels.Color(0,on,0)); 
}

}


void setup() 
{

  Serial.begin(115200);
//#include "wifi_sec.cpp"
const char *ssid     = "FRITZ!Box Fon WLAN 7270";
const char *password = "4813854476911701";

  WiFi.begin(ssid, password);
  DS18B20.begin();    // initialize the DS18B20 sensor

  pixels.begin();
   pinMode(IR_FEEDBACK_LED_PIN, OUTPUT);

  pinMode(RELAY_PIN, OUTPUT);
pinMode(BUTTON_PIN, INPUT);
 // irrecv.enableIRIn();
//  irrecv.blink13(true);
Serial.println("Winterzeit");
int ledState = LOW;   // ledState used to set the LED

Serial.print("verbinde zu Router");
  while (WiFi.status() != WL_CONNECTED) {
      // if the LED is off turn it on and vice-versa:
  ledState = (ledState == LOW) ? HIGH : LOW;

  // set the LED with the ledState of the variable:
  digitalWrite(IR_FEEDBACK_LED_PIN, ledState);
    delay(200);
    Serial.print(".");

  }
  Serial.println("verbunden!");
  IrReceiver.begin(IR_INPUT_PIN, ENABLE_LED_FEEDBACK); // Start the receiver

  timeClient.begin();
 
  digitalWrite(RELAY_PIN, HIGH);
Serial.print("NTP-Server Update alle ");
Serial.print(NTP_UPDATE_SEKUNDEN);
Serial.println(" Sekunden");

pixels.clear();
  pixels.show();            // Turn OFF all pixels ASAP
  pixels.setBrightness(bright); // Set BRIGHTNESS to about 1/5 (max = 255)

  zahlen(nightmode,"0","0","0","0");
  pixels.show();
  delay(200);
  zahlen(nightmode,"1","1","1","1");
  pixels.show();
  delay(200);
  zahlen(nightmode,"2","2","2","2");
  pixels.show();
  delay(200);
  zahlen(nightmode,"3","3","3","3");
  pixels.show();
  delay(200);
  zahlen(nightmode,"4","4","4","4");
  pixels.show();
  delay(200);
  zahlen(nightmode,"5","5","5","5");
  pixels.show();
  delay(200);
  zahlen(nightmode,"6","6","6","6");
  pixels.show();
  delay(200);
  zahlen(nightmode,"7","7","7","7");
  pixels.show();
  delay(200);
  zahlen(nightmode,"8","8","8","8");
  pixels.show();
  delay(200);
  zahlen(nightmode,"9","9","9","9");
  pixels.show();
  delay(200);
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

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait,String night="no") {
    int on1 = 0;
    if (night == "yes"){ on1 = nightmodeon*1;}
if (night == "no"){ on1 = daymodeon;}

  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    pixels.rainbow(firstPixelHue,1,255,on1,false);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
//        Serial.print("on1:");
//        Serial.println(on1);

    pixels.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
} 

String edata(int start, int ende, String daten){
  String edata_return = "";
  edata_return = daten.substring(start, ende);
  return edata_return;
}


void loop(void) 
{
pixels.clear();



  DS18B20.requestTemperatures();       // send the command to get temperatures
  tempC = round(DS18B20.getTempCByIndex(0));  // read temperature in °C
  //tempF = tempC * 9 / 5 + 32; // convert °C to °F
  //Serial.print("tempC");
  //Serial.println(tempC);
int temp=tempC;
data_epoch = timeClient.getEpochTime();


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
int update_NTP = NTP_UPDATE_SEKUNDEN - next_update;


        Serial.print("Nächstes Update in ");
        Serial.print(update_NTP);
        Serial.println(" Sekunden");
next_update ++;

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

    if(data_std_2 == 6 && data_min_2 == 30 && data_sec2 == 0){
        nightmode="no";
        Serial.println("it is 6:30  - switch to Daymode");
    }
    if(data_std_2 == 18 && data_min_2 == 0 && data_sec2 == 0){nightmode="yes";
        Serial.println("it is 18:30 - switch to Nightmode");
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
              Serial.print("dataremote:");
      Serial.println(dataremote);

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
    //pixels.setPixelColor(28, pixels.Color(on,0,0)); 
    pixels.setPixelColor(29, pixels.Color(on,0,0)); 

  pixels.show();
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
  pixels.show();
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
    pixels.setPixelColor(30, pixels.Color(0,0,0)); 
    pixels.setPixelColor(31, pixels.Color(0,0,0)); 
    pixels.setPixelColor(32, pixels.Color(0,on,0)); 
    pixels.setPixelColor(33, pixels.Color(0,on,0)); 
    pixels.setPixelColor(34, pixels.Color(0,on,0)); 
    pixels.setPixelColor(35, pixels.Color(0,on,0)); 
    pixels.setPixelColor(36, pixels.Color(0,0,0)); 
    pixels.setPixelColor(37, pixels.Color(0,0,0)); 
    pixels.setPixelColor(38, pixels.Color(0,on,0)); 
    pixels.setPixelColor(39, pixels.Color(0,on,0)); 
    pixels.setPixelColor(40, pixels.Color(0,on,0)); 
    pixels.setPixelColor(41, pixels.Color(0,on,0)); 
    pixels.setPixelColor(42, pixels.Color(0,0,0)); 
    pixels.setPixelColor(43, pixels.Color(0,0,0)); 



    pixels.setPixelColor(44, pixels.Color(0,on,0)); 
    pixels.setPixelColor(45, pixels.Color(0,on,0)); 
    pixels.setPixelColor(46, pixels.Color(0,on,0)); 
    pixels.setPixelColor(47, pixels.Color(0,on,0)); 
    pixels.setPixelColor(48, pixels.Color(0,on,0)); 
    pixels.setPixelColor(49, pixels.Color(0,0,0)); 
    pixels.setPixelColor(50, pixels.Color(0,on,0)); 
    pixels.setPixelColor(51, pixels.Color(0,on,0)); 
    pixels.setPixelColor(52, pixels.Color(0,0,0)); 
    pixels.setPixelColor(53, pixels.Color(0,on,0)); 
    pixels.setPixelColor(54, pixels.Color(0,0,0)); 
    pixels.setPixelColor(55, pixels.Color(0,0,0)); 
    pixels.setPixelColor(56, pixels.Color(0,0,0)); 
    pixels.setPixelColor(57, pixels.Color(0,0,0));
  pixels.show();
  delay(3000);

  }
if(dataremote == -167117056){
// remote button 4
    Serial.println("Remote used - Numbertest!");
  zahlen(nightmode,"0","0","0","0");
  pixels.show();
  delay(200);
  zahlen(nightmode,"1","1","1","1");
  pixels.show();
  delay(200);
  zahlen(nightmode,"2","2","2","2");
  pixels.show();
  delay(200);
  zahlen(nightmode,"3","3","3","3");
  pixels.show();
  delay(200);
  zahlen(nightmode,"4","4","4","4");
  pixels.show();
  delay(200);
  zahlen(nightmode,"5","5","5","5");
  pixels.show();
  delay(200);
  zahlen(nightmode,"6","6","6","6");
  pixels.show();
  delay(200);
  zahlen(nightmode,"7","7","7","7");
  pixels.show();
  delay(200);
  zahlen(nightmode,"8","8","8","8");
  pixels.show();
  delay(200);
  zahlen(nightmode,"9","9","9","9");
  pixels.show();
  delay(200);

  }
  if(dataremote == -384368896){
// remote button 5
  rainbow(1,nightmode);             // Flowing rainbow cycle along the whole strip
    Serial.println("Remote used - Rainbowtime!");

  }
  if(dataremote == -233963776){
// remote button 6
  rainbow(1,nightmode);             // Flowing rainbow cycle along the whole strip
    Serial.println("Remote used - Rainbowtime!");

  }
  if(dataremote == -217252096){
// remote button 7
  rainbow(1,nightmode);             // Flowing rainbow cycle along the whole strip
    Serial.println("Remote used - Rainbowtime!");

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
    pixels.setPixelColor(28, pixels.Color(on,0,0)); 
    pixels.setPixelColor(29, pixels.Color(on,0,0)); 
    blinker = 0;
    } else {
    pixels.setPixelColor(28, pixels.Color(0,0,0)); 
    pixels.setPixelColor(29, pixels.Color(0,0,0)); 
    blinker = 1;
    }
    pixels.setPixelColor(58, pixels.Color(on,on,on)); 
    pixels.setPixelColor(63, pixels.Color(on,on,on)); 
    pixels.setPixelColor(68, pixels.Color(on,on,on)); 
    pixels.setPixelColor(73, pixels.Color(on,on,on)); 
    pixels.setPixelColor(78, pixels.Color(on,on,on)); 
    pixels.setPixelColor(83, pixels.Color(on,on,on)); 
    pixels.setPixelColor(88, pixels.Color(on,on,on)); 
    pixels.setPixelColor(93, pixels.Color(on,on,on)); 
    pixels.setPixelColor(98, pixels.Color(on,on,on)); 
    pixels.setPixelColor(103, pixels.Color(on,on,on)); 
    pixels.setPixelColor(108, pixels.Color(on,on,on)); 
    pixels.setPixelColor(113, pixels.Color(on,on,on)); 

    pixels.setPixelColor(std_60, pixels.Color(0,0,on)); 
    pixels.setPixelColor(min_60, pixels.Color(0,on,0)); 
  pixels.setPixelColor(sekunde, pixels.Color(on,0,0)); 

 // Serial.print("std_60: ");
 // Serial.println(std_60);
 // Serial.print("min_60: ");
 // Serial.println(min_60);
 // Serial.print("sekunde: ");
 // Serial.println(sekunde);


  Serial.print(data_std_2);
  Serial.print(":");
  Serial.print(data_min_2);
  Serial.print(":");
  Serial.println(data_sec2);
   // Serial.print("nightmode: ");
//  Serial.println(nightmode);


    pixels.show();

delay(500);
//  for(int i=0; i<NUMPIXELS; i++) {

//    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
//    pixels.setPixelColor(28, pixels.Color(255,255,255)); 
//    pixels.setPixelColor(29, pixels.Color(255,255,255)); 
//    pixels.show();
//    delay(DELAYVAL);
//  rainbow(10);             // Flowing rainbow cycle along the whole strip

//  }

}

