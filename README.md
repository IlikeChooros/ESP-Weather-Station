# ESP Weather Station

## TOC
* [Introduction](#introduction)
* [Setup](#setup)
* [Run the code](#in-order-to-run-this-code)
* [Step by step explanation](#step-by-step-explanation)
* [Features](#features)
* [Troubleshooting](#troubleshooting)

## Introduction

![current_weather_epic](https://user-images.githubusercontent.com/105538405/212467629-f2da405b-54b6-440a-89d4-0aa28646bf5c.jpg)


This project displays forcasted and current weather. Data is obtained via [openwathermap](https://openweathermap.org/) API. The forcasted weather is displayed in 12 hour and next 4 days format.

## Setup
To run this project you will need some essential parts and libraries.

  **Needed parts:**

> * **ESP 32 WROOM-32**
> * **TFT display 240x320 with ILI9341 driver**

*Note: You can use other ESP versions, although it has to have WiFi module and minimum size of flash memory 4MB (project uses ~990 kB of flash memory). Other displays may be used as well but they must operate with TFT_eSPI library and have touch functionality, nevertheless some icons might look wierd with different resolutions.*

**Needed external libraries:**
> * **TFT_eSPI**

### In order to run this code:
> 1. Create an account on [openwathermap](https://openweathermap.org/) and generate your API key
> 1. Download this code anywhere you want
> 1. Unzip it
> 1. Go to folder 'ESP-Weather-Station-master'
> 1. Rename 'main.ino' to 'ESP-Weather-Station-master.ino' *(You can rename it howevery you want, but folder's name has to be the same as .ino file)*
>    1. If you dont have already installed Arduino IDE,
[download it](https://www.arduino.cc/en/software).
>    1. Follow [this tutorial](https://youtu.be/CD8VJl27n94) to setup Arduino IDE for ESP 32
>    1. If you have any trouble **connecting the display** to ESP or **downloading the library** check [this tutorial](https://youtu.be/rq5yPJbX_uk).
> 1. Open the 'ESP-Weather-Station-master.ino' file with Arduino IDE
> 1. Change:  `#define CITY_NAME "YOUR CITY NAME"`
> 1. Go to file: `src/weather_client/WeatherClient.h`
> 1. Change: `#define APPID "YOUR API KEY"`
> 1. Connect your ESP  to PC, pick COM port in Arduino IDE and upload the code

## Step by step explanation
The first screen on the display you will encounter, if the code was uploaded successfuly, is the WiFi setup sceen. You will see up to 6 nearest networks.


![wifi_list](https://user-images.githubusercontent.com/105538405/212466454-dd5ad657-6b39-4cf0-aaae-0a8937f14cf4.jpg)


By picking any of them the screen will change to the one with keyboard.
By clicking on the side buttons the keyboard layout will change, all keyboards have red delete button `"<<"` and 2 of them have cyan capslock button `"^"`. In the upper part of this screen, there is an input field, to its left green upload button `"+"`, which will try to establish a connection with desired wifi. In the left corner of the screen there is red `"X"` button which will return you to the previous screen. If you successfuly connect to wifi, this wifi's ssid and password will be saved to eeprom, so in after reseting the ESP you won't have to type in password for the saved WiFi.

![keyboard_qwerty](https://user-images.githubusercontent.com/105538405/212467582-f848e80f-9ab1-4fac-8fc0-808f602952c7.jpg)


![keyboard_123](https://user-images.githubusercontent.com/105538405/212467603-5dc8e03d-f016-4fa4-8a71-63c17641e651.jpg)


![keyboard_sp](https://user-images.githubusercontent.com/105538405/212467608-4e71c476-52c1-47e2-acfa-aa8bd53c0ddc.jpg)


After successfully establishing a connection with WiFi, you should see the screen displaying current weather data. In this part of the program, you gained access to 3 screens displaying different information about current and forcasted weather data. The first one is on the display by default, the second one is 12 hour forcast, and last one 4 next days. To move between these screens just touch left or right side of the screen *(Screen here is divided to 4 triangles).*

![current_weather_1](https://user-images.githubusercontent.com/105538405/212467656-d0ad6456-5909-45ae-9ec4-e7c52c17eece.jpg)


![12_hours](https://user-images.githubusercontent.com/105538405/212467667-8c485dde-8ef6-4340-b162-08b4aa65419e.jpg)


![4_days](https://user-images.githubusercontent.com/105538405/212467674-78a28e62-fbc7-4b57-984c-397aefbd344b.jpg)


## Features
1. Saving WiFi data
> If your wifi's ssid is shorter than `MAX_SSID_LENGHT` *(By default 26, so up to 25 of characters is accepted)*, and password shorter than `MAX_PASSWORD_LENGHT` *(by default 31)* your wifi's data will be saved to EEPROM. You can change default values in the file ".../ESP-Weather-Station/src/output/screens/WiFiScreen.h", nevertheless the bigger these values get the less networks could be saved as the EEPROM has access to only 512 bytes of memory. By default maximum number of saved networks is: 8 *( x = (512 - 10) / (31+26) ~= 8.8 , 512-10 -> addresses below 10 aren't used)*.

2. WiFi reconnection
> If the ESP loses connection to previously saved WiFi, it will try to reconnect to that WiFi. Note that in weather screens you cannot change networks.

3. Weather data update
> Weather data is updated every 15 minutes, just like the time *(although the time object will try in different time: every time when the hour hits: XX:00, XX:15, XX:30, XX:45)*, but if the device loses the connection to WiFi when trying to update the weather data, it won't cause any exceptions or crash, displayed data will be just stay the same and the program will try to update data again in next 15 minutes.

## Troubleshooting

 * [After connected to wifi](#after-connected-to-wifi)
 * [Reset saved wifis]()



### After connected to wifi
Most errors will occur when after successfully connecting to WiFi, the program initializes weather data objects, requesting information from API. When some error happens make sure to:
  * if connected via already saved wifi data, try clearing the wifi data from eeprom
  * check your wifi connetion on other wireless devices, do they have access to the internet
  * try resetarting ESP
  * try restarting router

### Reset saved wifis
To reset all saved wifis data, put this code at the beggining of the void setup() in main.ino *(ESP-Weather-Station-master.ino, or howevery you named .ino file)*:
```
...

void setup()
{
    EEPROM.begin(EEPROM_SIZE);
    eeprom_earse(10, 487); 
    EEPROM.end();
    
    Serial.begin(921600);
    tft.init();
    tft.setRotation(3);

    //******************************
    // Scanning for newtorks
    //
    reset_tft();
    load_saved_wifis();
    int8_t number_of_networks; 
    
    ...
}
```
The number 487 isn't obligatory you can calculate on you own how many cells need to be earased. This formula might help you:


` End-address = 11 + number-of-saved-networks * (MAX_SSID_LENGHT + MAX_PASSWORD_LENGHT)`
