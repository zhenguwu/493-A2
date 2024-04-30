#ifndef Rocket_h
#define Rocket_h

#include "helpers.h"

class Rocket {
public:
  int x, y;   // Position coordinates
  int firing = 0; // 0 = not firing, 1 = warning, 2 = firing
  int delay;
  int warningTime = 50;

  Rocket() {
    reset();
  }

  void reset() {
    delay = random(75, 125);
    x = WIDTH + 5;
    firing = 0;
  }

  void update(int playerY) {
    switch (firing) {
      case 0:
        delay--;
        if (delay < 0) {
          firing = 1;
          delay = warningTime;
        }
        break;
      case 1:
        if (delay == warningTime) {
          tone(BUZZER, 500, 300);
        } else if (delay == warningTime / 2) {
          tone(BUZZER, 500, 300);
        }
        setLEDs(playerY);
        delay--;
        if (delay < 0) {
          firing = 2;
          tone(BUZZER, 1000, 2000);
          y = playerY;
          setLEDs(-1);
        }
        break;
      case 2:
        x -= 3;
        if (x < -5) {
          reset();
        }
    }
  }

};

#endif