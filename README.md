# ESP Weather Station

## TOC
* [Introduction](#introduction)
* [Setup](#setup)

## Introduction

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
> 1. Rename 'main.ino' to 'ESP-Weather-Station-master.ino'
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


![6325fd8f-5e84-4d8d-9abd-29f9547381c9](https://user-images.githubusercontent.com/105538405/212464475-03b5aa8c-2edd-44cf-9841-bf62ab713760.jpg)


By picking any of them the screen will change to the one with keyboard.
By clicking on the side buttons the keyboard layout will change, all keyboards have red delete button `"<<"` and 2 of them have cyan capslock button `"^"`. In the upper part of this screen, there is an input field, to its left green upload button `"+"`, which will try to establish a connection with desired wifi. In the left corner of the screen there is red `"X"` button which will return you to the previous screen. If you successfuly connect to wifi, this wifi's ssid and password will be saved to eeprom, so in after reseting the ESP you won't have to type in password for the saved WiFi.

img keyboards

img

img

After successfully establishing a connection with WiFi, you should see the screen displaying current weather data. In this part of the program, you gained access to 3 screens displaying different information about current and forcasted weather data. The first one is on the display by default, the second one is 12 hour forcast, and last one 4 next days. To move between these screens just touch left or right side of the screen *(Screen here is divided to 4 triangles).*

img current weather

img 12 h

img 4 ddays

## Features
1. Saving WiFi data
> If your wifi's ssid is shorter than `MAX_SSID_LENGHT` *(By default 26, so up to 25 of characters is accepted)*, and password shorter than `MAX_PASSWORD_LENGHT` *(by default 31)* your wifi's data will be saved to EEPROM. You can change default values in the file ".../ESP-Weather-Station/src/output/screens/WiFiScreen.h", nevertheless the bigger these values get the less networks could be saved as the EEPROM has access to only 512 bytes of memory. By default maximum number of saved networks is: 8 *( x = (512 - 10) / (31+26) ~= 8.8 , 512-10 -> addresses below 10 aren't used)*.

1. WiFi reconnection
> If the ESP loses connection to previously saved WiFi, it will try to reconnect to that WiFi. Note that in weather screens you cannot change networks.

## Troubleshooting
