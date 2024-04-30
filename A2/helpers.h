#ifndef HELPERS_H
#define HELPERS_H

#include <Wire.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIDTH 128 // OLED display width
#define HEIGHT 64 // OLED display height

#define PLAYER_RADIUS 3       // Player radius
#define OBSTACLE_THICKNESS 3  // Obstacle thickness

#define BUTTON 5  // Button pin
#define VIBRATE 6 // Vibration motor pin
#define BUZZER 9  // Buzzer pin

#define LED1 A0 // LED 1 pin
#define LED2 A1 // LED 2 pin
#define LED3 A2 // LED 3 pin
#define LED4 A3 // LED 4 pin

#define OLED_RESET     4    // Reset pin
#define SCREEN_ADDRESS 0x3D // I2C address

void drawThickLine(Adafruit_SSD1306 &display, int x, int y, int x1, int y1, int thickness, int color);
void startDisplay(Adafruit_SSD1306 &display);
bool checkObstacleCollision(int playerX, int playerY, int x, int y, int x1, int y1, int thickness);
bool checkRocketCollision(int playerX, int playerY, int rectX, int rectY, int rectWidth, int rectHeight);
void setLEDs(int playerY);

#endif