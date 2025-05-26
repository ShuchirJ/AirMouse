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
