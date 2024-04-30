#include "helpers.h"

void startDisplay(Adafruit_SSD1306 &display) {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
}

// Source: https://github.com/G6EJD/GFX-Library-Any-Thickness-and-Angle-Line-Drawing
void drawThickLine(Adafruit_SSD1306 &display, int x, int y, int x1, int y1, int thickness, int color) {
  float dx = (thickness / 2.0) * (x - x1) / sqrt(sq(x - x1) + sq(y - y1));
  float dy = (thickness / 2.0) * (y - y1) / sqrt(sq(x - x1) + sq(y - y1));
  for (int i = 0; i < thickness; i++) {
    display.drawLine(x + i * dy, y - i * dx, x1 + i * dy, y1 - i * dx, color);
  }
}

bool checkObstacleCollision(int playerX, int playerY, int x, int y, int x1, int y1, int thickness) {
  // Vector from (x, y) to (x1, y1)
  int dx = x1 - x;
  int dy = y1 - y;

  // Vector from (x, y) to circle center
  int fx = playerX - x;
  int fy = playerY - y;

  // Project point onto line, finding the parameter t of the closest point
  float t = float(fx * dx + fy * dy) / (dx * dx + dy * dy);
  
  // Clamping t to the range [0,1] to restrict it to the segment
  t = max(0, min(1, t));

  // Finding the closest point on the line segment
  float nearestX = x + t * dx;
  float nearestY = y + t * dy;

  // Distance from circle center to this nearest point
  float distanceX = playerX - nearestX;
  float distanceY = playerY - nearestY;
  float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

  // Adjust distance to account for line thickness
  float collisionDistance = PLAYER_RADIUS + (thickness / 2.0);

  // Check if the distance is less than the collisionDistance
  return distance <= collisionDistance;
}

bool checkRocketCollision(int playerX, int playerY, int rectX, int rectY, int rectWidth, int rectHeight) {
  // Find the closest point on the rectangle to the circle
  int closestX = max(rectX, min(playerX, rectX + rectWidth));
  int closestY = max(rectY, min(playerY, rectY + rectHeight));

  // Calculate the distance between the circle's center and this closest point
  int distanceX = playerX - closestX;
  int distanceY = playerY - closestY;

  // If the distance is less than the radius, collision detected
  return (distanceX * distanceX + distanceY * distanceY) < (PLAYER_RADIUS * PLAYER_RADIUS);
}

void setLEDs(int playerY) {
  if (playerY < 0) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  } else if (playerY < HEIGHT/4) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    analogWrite(LED4, 150);
  } else if (playerY < HEIGHT/2) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    analogWrite(LED3, 150);
    digitalWrite(LED4, LOW);
  } else if (playerY < (3 * HEIGHT)/4) {
    digitalWrite(LED1, LOW);
    analogWrite(LED2, 150);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  } else {
    analogWrite(LED1, 150);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    
  }
}