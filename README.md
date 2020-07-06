# HMI PRIMARY / SPEEDO

## Software Progress:
- [x] Add IWDG to HMI Secondary 
- [x] LCD on animation 
- [x] And add R to Drive mode, also handle the control 
- [x] Give blink animation on mode index change 
- [x] Set default LCD value when no CAN msg in 0.5 sec 
- [x] GUI Speedometer Text need more width 
- [x] Blink on Select, and Set 
- [x] Reset the Trip meter on 3sec press  
- [x] Change "KM/KW" to "KM/KWh" in HMI Primary 
- [x] Handle manual STemWin migration 
- [x] Migrate RTOSv1 to RTOSv2
- [x] ~~Change LTDC from RGB565 to RGB666~~
- [x] Fix battery indicator & percentage not shown up, and check other similar things.
- [ ] Handle GPIO for LCD Power Control
- [ ] Add bootloader 
- [ ] Handle bootloader's CAN for DFU mode
- [ ] Use CAN Filter to ignore un-related ID
- [ ] Simplify simcom library with pointer data

## Hardware Progress:
- [x] Add line from RGB565 to RGB666 
- [x] Add SMD Fuse 
- [x] Power is controlled by HUB 
- [x] Extend the connector of downloader to solder 
- [x] Add logo, module name, module version 
- [x] ~~Add raster bellow the STM32 chip~~
- [x] Remove all values, only labels 
- [ ] Add LCD Power Control using MOSFET/PNP 

