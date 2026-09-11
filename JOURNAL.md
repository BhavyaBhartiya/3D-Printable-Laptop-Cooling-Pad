---
title: "3D-Printable-Laptop-Cooling-Pas"
author: "Enigma_124"
description: "This is a 3D printable Laptop Cooling Pad using Fan controlled by a custom RP2040 based devboard"
created_at: "2026-09-12"
---

So I had no idea that I had to both write devlogs and lapse. I thought it was one or the other, so here is a condensed form of the devlogs. 

# 2026-08-18 to 2026-08-19
 I was building the voltage protection circuit, which would allow the fans to receive a stable current at 12v and prevent reverse polarity. Then I created a step down convertor cicuit for 12v to 3.3.

 **Total time spent: 1.4 hours**

# 2026-08-20 to 2026-08-21
 I focused on creating the circuit for the RP2040 microcontroller and connected the required pins to the 4-pin headers for the fans and the OLED screen. I also connected the 3 2-pin headers for connecting various buttons. A separate USB-C port was added, which would receive CPU temperatures from the laptop.

 **Total time spent: 1.8 hours**

# 2026-08-23 to 2026-08-26
 I worked on assigning the various footprints and placing components in the PCB editor. Here KaiPereira's guide was very useful in deciding footprints of various components.

 **Total time spent: 3 hours**

# 2026-08-26 to 2026-08-27
 I worked on the traces. At first, I made the board a 4-layer board as I thought the routing would require the extra space, but I was able to route it in 2 layers. While routing the differential pair on the USB-C port for supplying data, it felt as if it didn't want to route to the RP2040.

 **Total time spent: 1 hours**

# 2026-09-03 to 2026-09-10
 I worked on the 3D Structure of the laptop Cooling Pad. This was my second time using Fusion, so the work was slow. Nothing much to say here. Also Worked on Readme.

 **Total time spent: 5.5 hours**

# 2026-09-11 to 2026-09-12
 I worked on the code for the RP2040. The imports in the code kept throwing errors even after reinstalling CMake and all the C compilers. The errors were fixed when I opened the folder separately and reran the build instead of opening the parent folder in VS Code. Also completed the Journal.md.

 **Total time spent: 1.4 hours**