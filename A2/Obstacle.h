#ifndef Obstacle_h
#define Obstacle_h

#include "helpers.h"

class Obstacle {
public:
  int x, y, x1, y1;   // Position coordinates

  Obstacle(int i) {
    x = 0;
    x1 = 0;
    reset();
    switch (i) {
      case 0:
        x -= WIDTH / 2;
        x1 -= WIDTH / 2;
        break;
      case 2:
        x += WIDTH / 2;
        x1 += WIDTH / 2;
        break;
    }
  }

  // Default constructor
  Obstacle() {}

  void update() {
    // Move the obstacle to the left
    x -= 1;
    x1 -= 1;

    if (x1 < 0) {
      reset();
    }
  }

private:
  int length = 25;    // Length of the obstacle

  void reset(int adjAngle = -1) {
    // Reset the obstacle to a random position and angle
    int angle;
    if (adjAngle == -1) {
      // First call, generate random y and angle
      y = random(5, HEIGHT - 5);
      angle = random(-90, 91);
      // Need to compensate for the obstacle's width (x1-x0) when resetting 
      //  as we call reset after x1 < 0 rather than x < 0 to ensure equal spacing
      x = ((3 * WIDTH) / 2) - (x1 - x);
    } else {
      // Subsequent call, only adjust angle
      angle = adjAngle;
    }

    // Calculate the end point of the obstacle
    x1 = x + length * cos(radians(angle));
    y1 = y + length * sin(radians(angle));

    // Fix angle and recalculate end point if the obstacle is out of bounds
    if (y1 < 0) {
      reset(angle + 90);
    } else if (y1 > HEIGHT) {
      reset(angle - 90);
    }
  }
};

#endif