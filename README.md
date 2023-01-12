# ESP Weather Station

## TOE
* [Introduction](#introduction)
* [Launch](#launch)

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

If you have any trouble **connecting the display** to ESP or **downloading the library** check [this](https://youtu.be/rq5yPJbX_uk) tutorial. 

In order to run this programme use [Arduino IDE](https://www.arduino.cc/en/software).

