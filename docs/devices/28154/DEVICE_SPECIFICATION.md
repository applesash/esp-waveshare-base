# Waveshare ESP32-S3-Touch-LCD-4

SKU: 28154

This board is the 4-inch 480x480 RGB LCD variant. It must be identified by the exact official wiki page and V4.0 hardware reference, not by generic ESP32-S3 catalog search results that may omit the SKU or return similar family pages.

The display controller family is ST7701 with 16-bit RGB565 timing/data signals and serial control. R0-R4 and B0-B4 are active; R5 and B5 are unused. The official reference records hsync polarity 1/front 10/pulse 8/back 50 and vsync polarity 1/front 10/pulse 8/back 20. Display reset and backlight control are mediated by the CH32V003 helper controller; exact ST7701 initialization commands remain an implementation gate.

All hardware facts are initially UNVERIFIED. Populate only from approved exact-SKU sources.
