#ifndef Player_h
#define Player_h

#include "helpers.h"

class Player {
public:
  int y;
  int x = 10;
  float velocity = 0;
  float gravityAccel = 0.5; // Acceleration due to gravity
  float gravityVelMax = 2.5;  // Maximum downawrd velocity due to gravity
  float jetpackAccel = -0.5; // Acceleration due to jetpack
  float jetpackVelMax = -3;  // Maximum upward velocity due to jetpack

  Player() {
    y = HEIGHT / 2;
  }

  void update() {
    if (digitalRead(BUTTON)) {
      // Stop vibrating the motor
      digitalWrite(VIBRATE, LOW);

      // Apply gravity
      if (velocity < gravityVelMax) {
        velocity += gravityAccel;
      }
    } else {
      // Start vibrating the motor at random to simulate jetpack
      analogWrite(VIBRATE, random(120, 220));

      // Overcome gravity quicker to make the character feel a little more responsive
      if (velocity > 2) {
        velocity = 2;
      }
      if (velocity > jetpackVelMax) {
        velocity += jetpackAccel;
      }
    }
    y += velocity;

    // Keep the player within the screen
    if (y < PLAYER_RADIUS + 1) {
      y = PLAYER_RADIUS + 1;
    } else if (y > HEIGHT - PLAYER_RADIUS) {
      y = HEIGHT - PLAYER_RADIUS;
    }
  }

};

#endif