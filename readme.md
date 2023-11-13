# EEZYbotARM MK2 Robot Control with ESP32

EEZYbotARM MK2 :https://www.thingiverse.com/thing:1454048
EEZYbotARM MK3 :https://www.thingiverse.com/thing:2838859

This repository contains the code and information to control the EEZYbotARM MK2 robot arm using an ESP32 microcontroller. The EEZYbotARM MK2 and MK3 are open-source 3D-printable robot arms that can be found on Thingiverse.

## Introduction

The EEZYbotARM MK2 is a versatile and affordable robot arm that you can build using 3D-printed parts. It can be controlled via an ESP32 microcontroller, which serves as a web server for sending commands to the robot arm. The control interface is provided through the included `index.html` app.

## Video

https://youtu.be/PwJwjXMDmXA
https://youtu.be/KiZO1xTcmOE

## Features

- Control the EEZYbotARM MK2 using an ESP32 microcontroller.
- A web-based interface for sending commands to the robot arm.
- Basic functionality for controlling the robot arm's movements.
- Teaching capability for recording and playing back sequences of movements.

## Getting Started

To get started with this project, you will need the following:

- EEZYbotARM MK2 or MK3 (3D-printed parts available on Thingiverse).
- An ESP32 microcontroller.
- The `index.html` app for controlling the robot arm.
- Basic knowledge of Arduino programming and web development.

## Installation

1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/your-username/eezybotarm-mk2-esp32-control.git
   ```
2. Upload the Arduino code (main.ino) to your ESP32 microcontroller using the Arduino IDE.
3. open the index.html app directly in a web browser.
4. Connect to the ESP32's Wi-Fi network and access the control interface via the provided IP address.
