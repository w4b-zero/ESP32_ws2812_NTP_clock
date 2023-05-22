# ESP32-ws2812-NTP-Clock<br>
Internet Time Clock (Ring 60Leds + Clock 58Leds) for <a href="https://platformio.org/?utm_source=platformio&utm_medium=piohome" target="_blank">PlatformIO</a><br>
<br>
***Used Libraries***<br>
	adafruit/Adafuit NeoPixel@^1.10.6<br>
	https://github.com/taranais/NTPClient<br>
	https://github.com/Arduino-IRremote/Arduino-IRremote<br>
	paulstoffregen/OneWire @ ^2.3.7<br>
	milesburton/DallasTemperature @ ^3.11.0<br>
	https://github.com/Juerd/ESP-WiFiSettings<br>
	<br>
On first launch, an unsecured Wifi Access Point will be created!<br>
When connecting to this you will be redirected to your browser to the web configuration panel. (192.168.4.1)<br>
Please select your router there and enter your password.<br>
Selectable languages are German, English and Dutch.<br>
With the help of a checkbox you can protect the web control panel with a password, which you can enter in the text field below.<br>
*The password already contained therein was automatically generated at the first start.*<br>
Finally, all you have to do is click on save - if everything went well, `##**##**##**` should appear in the wifi password text field.<br>
Now you can click Reboot device to connect to your router.<br>
<br>
To call up the web configuration panel again, you have to press the "Start Config Button" for about 3 seconds when restarting/switching on. <br>
<br> 
<br>
<img src="/images/ESP32_WS2812b_Uhr.jpg" width="400px"><br>
<br>
Custom ESP Board<br>
<img src="/images/board.jpg" width="400px"><br>
<br>
Start Config Button   = GPIO 27<br>
LEDs WS2812b          = GPIO 16<br>
Button                = GPIO 17 (Nightmode / Daymode)<br>
IR TSOP38238          = GPIO 21<br>
Relay SRD-05VDC-SL-A  = GPIO 22<br>
Temp DS18B20          = GPIO 18<br>
<br>
arrangement of LEDs<br>
<img src="/images/LED_order.jpg" width="400px"><br>
<br>
ESP Dev Module<br>
<img src="/images/ESP32_d1_mini.jpg" width="200px"><br>
<br>
IR Remote<br>
<img src="/images/IR_Remote.jpg" width="200px"><br>
ON / OFF All Led Off used Relay<br>
1 = Date<br>
2 = Year<br>
3 = Temp<br>
4 = Test Numbers<br>
5 = Rainbow <br>
6 = Rainbow<br>
7 = Rainbow<br>
8 = Nightmode / Daymode<br>

