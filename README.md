# 3D Printable Laptop Cooling Pad

This is an open source laptop cooling pad designed to force air into the laptop like the Ilano V10 Cooling Pad. It uses 2 Arctic P12 Pro fans set in back portion of the cooling pad instead of th emiddle as most laptops have ducts at the back and not in the middle. It also uses a custom RP2040 based board to control the fan speed on the basis of the temperature of the CPU if in automatic mode or to set the fans to a constant speed if in manual mode. It requires a seperate 12v Power Input to run it without increasing load on the laptop by using the laptop to supply power to it. If it is to be  used in automatic mode then it should be connected to the laptop by a seperate cable so that the laptop can provide it with the CPU temperatures.

## Instructons for Using and Assembly

1. Attach the PCB to the area enclosed by 3 thin walls in between the fan. The PCB should slip in and sit snugly in the enclosure as it has been built to the exact dimensions for the pcb.

2. If you plan on using only manual mode then connect the 6 pin usb c receptacle to an external 12V Power Supply. The 6 pin USB C receptacle is the one on the right of the RP2040 chip.

3. If you wish to use automatic mode as well then attach a cable from any port of the computer to the 14 pin usb c receptacle present straight ahead of the RP2040 chip.

4. The OLED scrren will show current mode, fan speed and if any fan is facing any errors. If it is in automatic mode then it will also show the CPU temperature which will be updated once every 5 seconds.

5. You can use the Increase/ Decrease Buttons to increase or decrease the RPM of the fan by 500 in Manual Mode.

6. You can use the Mode Button to toggle the Mode of the Cooling Pad.

## Schematic

![image](./Assets/Schematic.png)

## PCB

![image](./Assets/PCB.png)
![image](./Assets/3D-PCB.png)

## 3D-Design

![image](./Assets/Cooling-Pad1.png)
![image](./Assets/Cooling-Pad2.png)
![image](./Assets/Cooling-Pad3.png)

## External Circuit

![image](./Assets/External_Circuit.png)

## BOM
| Designator                                            | Footprint                                       | Quantity | Value                         | LCSC Part # | Unit Price USD | Design Qty Cost USD | Link                                                                            |
|-------------------------------------------------------|-------------------------------------------------|----------|-------------------------------|-------------|----------------|---------------------|---------------------------------------------------------------------------------|
| C1, C19, C20                                          | 603                                             | 3        | 10uF                          | C96446      | 0.0557         | 0.1671              | https://www.lcsc.com/product-detail/C96446.html                                 |
| C2                                                    | 603                                             | 1        | 22uF                          | C2762594    | 0.1021         | 0.1021              | https://www.lcsc.com/product-detail/C2762594.html                               |
| C21, C24                                              | 402                                             | 2        | 1uF                           | C52923      | 0.0122         | 0.0244              | https://www.lcsc.com/product-detail/C52923.html                                 |
| C22, C23, C25, C26, C27, C28, C29, C30, C31, C32, C35 | 402                                             | 11       | 0.1uF                         | C1525       | 0.0046         | 0.0506              | https://www.lcsc.com/product-detail/C1525.html                                  |
| C33, C34                                              | 402                                             | 2        | 15pF                          | C86285      | 0.004          | 0.008               | https://www.lcsc.com/product-detail/C86285.html                                 |
| D1                                                    | D_SMB                                           | 1        | SMBJ15A                       | C83846      | 0.1183         | 0.1183              | https://www.lcsc.com/product-detail/C83846.html                                 |
| D2                                                    | D_SOD-123F                                      | 1        | BZT52H-A12                    | C7507853    | 0.1912         | 0.1912              | https://www.lcsc.com/product-detail/C7507853.html                               |
| D4                                                    | 603                                             | 1        | LED                           | C965804     | 0.0051         | 0.0051              | https://www.lcsc.com/product-detail/C965804.html                                |
| F1                                                    | 1812                                            | 1        | Littelfuse 1812L150/24MR      | C142805     | 0.0979         | 0.0979              | https://www.lcsc.com/product-detail/C142805.html                                |
| J1                                                    | TYPE-C-SMD_TYPE-C-6P-073                        | 1        | USB_C_Receptacle_PowerOnly_6P | C668623     | 0.0406         | 0.0406              | https://www.lcsc.com/product-detail/C668623.html                                |
| J10                                                   | PinHeader_1x02_P2.54mm_Vertical                 | 1        | DECREASE                      | C32713268   | 0.0154         | 0.0154              | https://www.lcsc.com/product-detail/C32713268.html                              |
| J11                                                   | USB_C_Receptacle_HRO_TYPE-C-31-M-12             | 1        | USB_C_Receptacle_USB2.0_14P   | C165948     | 0.1724         | 0.1724              | https://www.lcsc.com/product-detail/C165948.html                                |
| J13                                                   | PinHeader_1x03_P2.54mm_Vertical                 | 1        | Conn_01x03                    | C2937625    | 0.0198         | 0.0198              | https://www.lcsc.com/product-detail/C2937625.html                               |
| J5, J6                                                | PinHeader_1x04_P2.54mm_Vertical                 | 2        | Fan1_Connector                | C2691448    | 0.0275         | 0.055               | https://www.lcsc.com/product-detail/C2691448.html                               |
| J7                                                    | PinHeader_1x04_P2.54mm_Vertical                 | 1        | OLED                          | C2691448    | 0.0275         | 0.0275              | https://www.lcsc.com/product-detail/C2691448.html                               |
| J8                                                    | PinHeader_1x02_P2.54mm_Vertical                 | 1        | INCREASE                      | C32713268   | 0.0154         | 0.0154              | https://www.lcsc.com/product-detail/C32713268.html                              |
| J9                                                    | PinHeader_1x02_P2.54mm_Vertical                 | 1        | MODE                          | C32713268   | 0.0154         | 0.0154              | https://www.lcsc.com/product-detail/C32713268.html                              |
| L1                                                    | IND-SMD_L4.5-W4.1_SRP4020TA                     | 1        | SRP4020TA-2R2M                | C719179     | 0.6015         | 0.6015              | https://www.lcsc.com/product-detail/C719179.html                                |
| Q1                                                    | SOT-23                                          | 1        | DMP3099L                      | C2940610    | 0.0499         | 0.0499              | https://www.lcsc.com/product-detail/C2940610.html                               |
| Q2                                                    | SOT-23                                          | 1        | BSS138                        | C52895      | 0.0638         | 0.0638              | https://www.lcsc.com/product-detail/C52895.html                                 |
| R1, R12, R3                                           | 603                                             | 3        | 100K                          | C14675      | 0.0036         | 0.0108              | https://www.lcsc.com/product-detail/C14675.html                                 |
| R13, R16, R28, R34                                    | 402                                             | 4        | 10K                           | C60490      | 0.0033         | 0.0132              | https://www.lcsc.com/product-detail/C60490.html                                 |
| R14, R15, R20, R27, R29, R30, R33                     | 402                                             | 7        | 1k                            | C106235     | 0.0044         | 0.0308              | https://www.lcsc.com/product-detail/C106235.html                                |
| R21, R22, R23, R24                                    | 402                                             | 4        | 5.1K                          | C105872     | 0.003          | 0.012               | https://www.lcsc.com/product-detail/C105872.html                                |
| R25, R26                                              | 402                                             | 2        | 27                            | C138021     | 0.004          | 0.008               | https://www.lcsc.com/product-detail/C138021.html                                |
| R31, R32                                              | 402                                             | 2        | 4.7k                          | C105871     | 0.0038         | 0.0076              | https://www.lcsc.com/product-detail/C105871.html                                |
| SW1, SW2                                              | SW_Push_SPST_NO_Alps_SKRK                       | 2        | SW_Push                       | C720477     | 0.053          | 0.106               | https://www.lcsc.com/product-detail/C720477.html                                |
| U1                                                    | WSON-8-1EP_2x2mm_P0.5mm_EP0.9x1.6mm_ThermalVias | 1        | TPS62162DSG                   | C2863597    | 1.5159         | 1.5159              | https://www.lcsc.com/product-detail/C2863597.html                               |
| U2                                                    | SOT-23                                          | 1        | MCP1700x-330xxTT              | C39051      | 0.409          | 0.409               | https://www.lcsc.com/product-detail/C39051.html                                 |
| U5                                                    | Winbond_USON-8-1EP_3x2mm_P0.5mm_EP0.2x1.6mm     | 1        | W25Q16JVUXIQ TR               | C2843335    | 1.5882         | 1.5882              | https://www.lcsc.com/product-detail/C2843335.html                               |
| U6                                                    | QFN-56-1EP_7x7mm_P0.4mm_EP3.2x3.2mm             | 1        | RP2040                        | C2040       | 0.9968         | 0.9968              | https://www.lcsc.com/product-detail/C2040.html                                  |
| Y2                                                    | CRYSTAL-SMD_4P-L2.5-W2.0-BL-1                   | 1        | ABM8-272-T3                   | C20625731   | 0.62           | 0.62                | https://lcsc.com/product-detail/Crystals_Abracon-LLC-ABM8-272-T3_C20625731.html |
| Arctic P12 Pro                                        |                                                 | 2        |                               |             | 16.23          | 32.46               | https://www.arctic.de/en/P12-Pro/ACFAN00305A                                    |
| TOTAL                                                 |                                                 | 66       |                               |             |                | 39.6197             |                                                                                 |


### Credits - to KaiPereira for their excellent guide on [how to buid a custom devboard](https://github.com/KaiPereira/build-a-devboard)