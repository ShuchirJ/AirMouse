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

## 5-29 18:30: Code part 3
Okay I was approaching my code wrong- I was trying to take absolute positional degree/x/y/z movements, finding their speeds, then reapplying that to the mouse movement. ??? I realized I can pass the accel/gyro speeds to the mouse directly, so I rewrote the code to do that. Also realized I was moving mouse on gyro movementsi instead of accel. movements, so I fixed that by making the gyro the scroll and the accel. the mouse movements. I think that's pretty much done, I need to implement button presses now but that should be very simple- just reading the value of a button and calling mouse.press when it happens.

**Time taken: 30 min**

## 6-7 7:30 PM: Finishing the code, BOM
Finished the code! I added the button presses, and now it works as a mouse. Before I start designing the case, I need to figure out the BOM so I know what parts to design for. I know I'll be using the XIAO ESP32S3 and [this](https://www.adafruit.com/product/4237) battery, I just need to finalize the accelerometer/gyroscope and the exact buttons now. For the accelerometer i think I was thinking of something before, but I'll go with [LSM6DSOX](https://www.adafruit.com/product/4438) because it seems like it has very low noise - lower than the MPU6050. The code will change a little; Let me change that now

Ok, done and uploaded- [mouse.ino](mouse.ino)

BOM time!! these [soft buttons](https://www.adafruit.com/product/3101) look nice, and I'll go with a typical [rocker switch](https://www.robotshop.com/products/sfe-on-off-rocker-switch?gQT=1) for the power. That should be all!

BOM: [BOM.csv](BOM.csv)

while thinking of this ive now run into another problem: i need a 3 way splitter for the ground pin on the esp, but i can't find any

it's fine i'll just strip the wires and solder them together and make my own splitter

summary for today: writing more code, part sourcing, thinking 🥺
**Time taken: 2 hrs**


## 6-11 9:30 PM: More part sourcing, Start CAD
Ok, I did some more part sourcing to buy more things from mouser so its cheaper. I've added screws and wires to the BOM, I'll upload it soon. I think the only thing left is the elastic band i wanted to add. I've also started cadding:
![image](https://github.com/user-attachments/assets/3976370a-b997-408e-b06b-18d34ff6ee76)
The design thought here is this:

3 layers; bottom is accelerometer screwed in for accuracy, and the two left/right buttons accessible from the bottom (easier to click while holding in the hand i think). Middle layer is the ESP; one of the walls will have a cutout for the XIAO's USB port so I can charge the device without needing to open the whole thing up. Third and final layer will be the battery. Still not sure how I'm going to design the lid, because I want it to be ome sort of snapfit so it's easy to open but I also don't really know how to design snap fits so uhh we'll see I guess. One of the walls will also have a cutout for the power switch. 

**Time Taken: 1.5 hrs**

## 6-12 8:45 PM: CAD
I've started dropping the cad models for my actual components in so I can design around them. So far, I've rethought where Iw ant the buttons to be. I also think 3 layers will be too thick, so I'll sacrifice an extra 5mm width for a thinner device. The XIAO is laying next to the accelerometer, but I'm not sure how to secure it in especially since there are no mounting holes. here's where I'm at now:
![image](https://github.com/user-attachments/assets/dbd57f68-b891-40fb-a7dd-4b4eb375fecf)

Thought about it for a quick second and I'll put small walls around the xiao so it doesn't move hopefully that's enough 😭 I'm thinking of putting a screwable panel on top of both the boards anyways to separate the battery, so maybe that'll all hold the ESP in. Made a cutout for the usb port, and stuck my button in.
![image](https://github.com/user-attachments/assets/176a38f6-c2b1-4a85-a316-7c186ccdf6ae) ![image](https://github.com/user-attachments/assets/36dc6012-ae49-4ca9-a31a-f41776359fb5)

what's left: the other button, tolerances for the buttons, power switch, separation panel (?), battery (?), and lid. I think lid will be the hardest considering I have like no experience but we'll see. 

**Time taken: 2.5 hrs**

## 6-13 11:00 PM: Rocker Switch
Spent a few min adding a cutout for the rocker switch...how in the world is it so big
![image](https://github.com/user-attachments/assets/25ad6c11-e2c9-46e8-a1b3-77f9a4218fc2)
I need to rethink this, potentially findding a smaller rocker switch because this leaves like no space for the battery.

**Time taken: 20 min**
