---
title: "The Wand"
author: "shuchir"
description: "Wave the wand and see magic appear on your screen!"
created_at: "2025-05-26"
---

## 5-26 00:00: Planning
It's planning day today! I want to research a litle and figure out the best way to do things. The design: have a mouse controlled entirely by accelerometers and gyroscopes. I'm aware it's worse than an optical mouse this way, but I would really like a way to write on something like excalidraw as if i was writing with an normal pen- so the mouse should be small enough to fit in my palm. 
The 3 main things that come to my mind today: the MCU, accelerometer/gyroscope, and battery. MCU should ideally support BLE because it's way nicer than having a wire coming out your palm (also my goal is to use this on a projector so I'd need a really long wire). 

Small MCUs: the XIAO ESP32C3 (supports BLE!!), Tiny 2350, teensy (too big for my palm), QT Py

The xiao esp32c3 also has battery charging support so that's what I'm leaning towards.

For battery: again need something small; maybe [this](https://www.adafruit.com/product/1578)? it has decent charge for probably a few hours, and it's a small 3.5 x 3.5 cm square ish bat.

accelerometer + gyroscope: [this](https://www.adafruit.com/product/4503) looks cheap and good enough for what I need!

## 5-27 19:00: Wiring
Took a look at how everything should go together and came up with this wiring diagram:

<img src="https://github.com/user-attachments/assets/4648ec2f-9944-428a-95e8-c025d3546ca0" height="200">

seems fairly simple??

## 5-27 21:00: I forgot the buttons.
I don't want to use the buttons onboard the esp because I want to position them along the outside of the mouse, so they'll need to be a little flexible. Now I'm not 100% confident but I think [the ESP should have internal pull ups](https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf), so I wont need resistors. 4 wires going to a single ground pin makes me a little uneasy though. Tomorrow I'll start designing the case, and hopefully in a few days I'll have written the code and finish the case.

![the_wand_wiring](https://github.com/user-attachments/assets/8c27124e-c10e-4aa7-a27c-d65dd706ca22)

## 5-28 09:00: Code
Decided to do the code first; Started simulating on wokwi: https://wokwi.com/projects/432109492341468161

Got the accelerator/gyroscope working and printing actual values, but I just realized the ESP32C3 doesn't support HID- stay tuned !!

**Time taken: 30min**

## 5-28 18:00: Code Part 2
Did a little more research and it seems like the ESP32S3 is really similar and does support HID- so that's what I'll be using instead. Replaced the MCU on wokwi. Noticed one thing though: the MPU6050 (similar to what I plan to use: the ST LSM6DS3TR-C) doesn't let you "zero" the sensor to a new position; I think it'll be more worthwhile to remove the calibrate button then. Removing the calibrate button, and adding a power switch because I forgot that the first time around;
![image](https://github.com/user-attachments/assets/e6ebb205-4455-4358-8faf-32a9c5a41aeb)

Back to the code; I think I can use https://github.com/T-vK/ESP32-BLE-Mouse to act as the BLE mouse controller

wokwi needs you to pay to upload a library...we're going to continue blind then 🤩
I'll do as much as I can before adding mouse support then add that later.

Added some basic logic to handle angles, and added skeleton logic for mouse events!

**Time taken: 1 hour**
