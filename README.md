# ESP Weather Station

![IMG_20230115_155913_1](https://user-images.githubusercontent.com/105538405/212566195-31139a7d-e5f9-481c-8577-69b2f22defe8.jpg)

## TOC
* [Introduction](#introduction)
* [Setup](#setup)
* [Run the code](#in-order-to-run-this-code)
* [Step by step explanation](#step-by-step-explanation)
* [Features](#features)
* [Troubleshooting](#troubleshooting)

## Introduction

This project displays forcasted and current weather. Data is obtained via [openwathermap](https://openweathermap.org/) API. The forcasted weather is displayed in 12 hour and next 4 days format. 

## Setup
*Warning: this project uses EEPROM, it might delete some of the data stored there.*
To run this project you will need some essential parts and libraries.

  **Needed parts:**

> * **ESP 32 WROOM-32**
> * **TFT display 240x320 with ILI9341 driver**

*Note: You can use other ESP versions, although it has to have WiFi module and minimum size of flash memory 4MB (project uses ~990 kB of flash memory). Other displays may be used as well but they must operate with TFT_eSPI library and have touch functionality, nevertheless some icons might look wierd with different resolutions.*

**Needed external libraries:**
> * **TFT_eSPI**
> * **ArduinoJson**

### In order to run this code:
> 1. Create an account on [openwathermap](https://openweathermap.org/) and generate your API key
> 1. Download this code anywhere you want (or git clone)
> 1. Unzip it
> 1. Go to folder 'ESP-Weather-Station-master'
> 1. Rename 'main.ino' to 'ESP-Weather-Station-master.ino' *(You can rename it however you want, but folder's name has to be the same as .ino file)*
>    1. If you dont have already installed Arduino IDE,
[download it](https://www.arduino.cc/en/software).
>    1. Follow [this tutorial](https://youtu.be/CD8VJl27n94) to setup Arduino IDE for ESP 32
>    1. If you have any trouble **connecting the display** to ESP or **downloading the library** check [this tutorial](https://youtu.be/rq5yPJbX_uk).
> 1. Open the 'ESP-Weather-Station-master.ino' file with Arduino IDE
> 1. Go to file: `src/weather_client/WeatherClient.h`
> 1. Change: `#define APPID "YOUR API KEY"`
> 1. Connect your ESP  to PC, pick COM port in Arduino IDE and upload the code

*First upload of the code might result in esp system abort, see [this](#esp-restarts-immediately-after-uploading-the-code) how to fix it.*


## Step by step explanation
The first screen on the display you will encounter, if the code was uploaded successfuly, is the WiFi setup sceen. You will see up to 6 nearest networks.


![wifi_list](https://user-images.githubusercontent.com/105538405/212466454-dd5ad657-6b39-4cf0-aaae-0a8937f14cf4.jpg)


By picking any of them the screen will change to the one with keyboard.
By clicking on the side buttons the keyboard layout will change, all keyboards have red delete button `"<<"` and 2 of them have cyan capslock button `"^"`. In the upper part of this screen, there is an input field, to its left green upload button `"+"`, which will try to establish a connection with desired wifi. In the left corner of the screen there is red `"X"` button which will return you to the previous screen. If you successfuly connect to wifi, this wifi's ssid and password will be saved to eeprom, so after reseting the ESP you won't have to type in password for the saved WiFi.

![keyboard_qwerty](https://user-images.githubusercontent.com/105538405/212467582-f848e80f-9ab1-4fac-8fc0-808f602952c7.jpg)


![keyboard_123](https://user-images.githubusercontent.com/105538405/212467603-5dc8e03d-f016-4fa4-8a71-63c17641e651.jpg)


![keyboard_sp](https://user-images.githubusercontent.com/105538405/212467608-4e71c476-52c1-47e2-acfa-aa8bd53c0ddc.jpg)


After successfully establishing a connection with WiFi, you should see the screen displaying current weather data. In this part of the program, you gained access to 3 screens displaying different information about current and forecasted weather data. The first one is on the display by default, the second one is 12 hour forecast, and last one 4 next days. To move between these screens just touch left or right side of the screen.


![curr_w](https://user-images.githubusercontent.com/105538405/212566214-04356cb4-5c64-4cd3-8bde-1f114c00ff1f.jpg)


![12_for](https://user-images.githubusercontent.com/105538405/212566216-54f9b155-5386-4fdd-ab0c-d20eeee62e1f.jpg)


![4_days](https://user-images.githubusercontent.com/105538405/212566224-2cdfbbbd-c670-481d-a65b-75f84f80bc1e.jpg)


## Features
1. Saving WiFi data
> If your wifi's ssid is shorter than `MAX_SSID_LENGHT` *(By default 26, so up to 25 of characters is accepted)*, and password shorter than `MAX_PASSWORD_LENGHT` *(by default 31)* your wifi's data will be saved to EEPROM. You can change default values in the file ".../ESP-Weather-Station/src/output/screens/WiFiScreen.h", nevertheless the bigger these values get the less networks could be saved as the EEPROM has access to only 512 bytes of memory. By default maximum number of saved networks is: 8 *( x = (512 - 10) / (31+26) ~= 8.8 , 512-10 -> addresses below 10 aren't used)*.

2. WiFi reconnection
> If the ESP loses connection to previously saved WiFi, it will try to reconnect to that WiFi. Note that in weather screens you cannot change networks.

3. Weather data update
> Weather data is updated every 15 minutes, just like the time *(although the time object will try in different time: every time when the hour hits: XX:00, XX:15, XX:30, XX:45)*, but if the device loses the connection to WiFi when trying to update the weather data, it won't cause any exceptions or crash, displayed data will be just stay the same and the program will try to update data again in next 15 minutes.

4. Saving locations
> This feature lets you save up to 2 (by default) locations to get infromation about, provided that location character lenght is shorter than `MAX_CITY_LEN` (22). 
It also lets you override saved locations.

5. Screensaver
> It will activate after 1 minute of no activity

## Troubleshooting
While I did my best making sure everything is working fine, there are possible situations in which ESP might crash. Make sure to post them in the Issuses.

 * [Esp restarts immediately after uploading the code](#esp-restarts-after-connecting-to-wifi)
 * [Esp restarts after connecting to wifi](#esp-restarts-after-connecting-to-wifi)
 * [Reset saved wifis](#reset-saved-wifis)

### Esp restarts immediately after uploading the code
This situation might happen on first upload. The root of this problem is most likely that some data is written on addresses 10 *(starting address for writing saved wifi data)* and 487 *(`CITY_NAME_IDX`)*. They are used to control number of data saved in EEPROM, so conflicting data will cause an undefined behaviour and as a result ESP abort.
To fix it, you have to simply clear those addresses:

```
...

void setup()
{
  tft.init();
  tft.setRotation(3);
  
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.write(CITY_NAME_IDX, 0);
  EEPROM.write(10, 0);
  EEPROM.commit();


  reset_tft();
  load_saved_wifis();
  int8_t number_of_networks; 
  wifi_screens[0]->init();

  ...
}
```

Make sure to delete it after resolving the issue to use WiFi and city location saving feature.

### Esp restarts after connecting to wifi
Most errors will occur when after successfully connecting to WiFi, the program initializes weather data objects, requesting information from API. When some error happens make sure to:
  * try clearing the wifi data from eeprom ([see this](#esp-restarts-after-connecting-to-wifi))
  * check your wifi connetion on other wireless devices, do they have access to the internet
  * try resetarting ESP
  * try restarting router


### Reset saved wifis
To reset all saved wifis data, put this code at the beggining of the void setup() in main.ino *(ESP-Weather-Station-master.ino, or however you named .ino file)*:
```
...

void setup()
{
    EEPROM.begin(EEPROM_SIZE);
    eeprom_earse(10, 487); 
    EEPROM.end();
    
    tft.init();
    tft.setRotation(3);

    reset_tft();
    load_saved_wifis();
    int8_t number_of_networks; 
    wifi_screens[0]->init();
    ...
}
```
The number 487 isn't obligatory you can calculate on you own how many cells need to be earased. This formula might help you:


` End-address = 11 + number-of-saved-networks * (MAX_SSID_LENGHT + MAX_PASSWORD_LENGHT)`
