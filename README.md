# ESP Weather Station

## TOE
* [Introduction](#introduction)
* [Setup](#setup)

## Introduction

This project displays forcasted and current weather. Data is obtained via [openwathermap](https://openweathermap.org/) API.

## Setup
To run this project you will need some essential parts and libraries.

  **Needed parts:**

> * **ESP 32 WROOM-32**
> * **TFT display 240x320 with ILI9341 driver**

_Note: You can use other ESP versions, although it has to have WiFi module and minimum size of flash memory 4MB (project uses ~990 kB of flash memory). Other displays may be used as well but they must operate with ILI9341 dirver and have touch functionality, nevertheless some icons might look wierd with different resolutions._

**Needed external libraries:**
> * **TFT_eSPI**

### In order to run this code:
> 1. Create an account on [openwathermap](https://openweathermap.org/) and generate your API key
> 1. Download this code anywhere you want
> 1. Unzip it
> 1. Go to folder 'ESP-Weather-Station-master'
> 1. Rename 'main.ino' to 'ESP-Weather-Station-master.ino'
>  1. If you dont have already installed Arduino IDE,
[download it](https://www.arduino.cc/en/software).
>  1. Follow [this tutorial](https://youtu.be/CD8VJl27n94) to setup Arduino IDE for ESP 32
>  1. If you have any trouble **connecting the display** to ESP or **downloading the library** check [this tutorial](https://youtu.be/rq5yPJbX_uk).
> 1. Open the 'ESP-Weather-Station-master.ino' file with Arduino IDE
> 1. Change:  `#define CITY_NAME "YOUR CITY NAME"`
> 1. Go to file: `src/weather_client/WeatherClient.h`
> 1. Change: `#define APPID "YOUR API KEY"`
> 1. Connect your ESP  to PC, pick COM port in Arduino IDE and upload the code
