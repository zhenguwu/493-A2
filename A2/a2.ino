#include "helpers.h"
#include "Player.h"
#include "Obstacle.h"
#include "Rocket.h"

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);

// Initialize player
Player player;

// Initialize array of obstacles
Obstacle lasers[3];

// Initialize rocket
Rocket rocket;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(VIBRATE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  startDisplay(display);
  display.setTextSize(1);
}

int highscore = 0;
int score = 0;
void endGame() {
  analogWrite(VIBRATE, 255);
  tone(BUZZER, 1500, 800);
  delay(800);
  analogWrite(VIBRATE, 0);
  display.clearDisplay();
  display.setCursor(WIDTH / 3, HEIGHT / 3);
  display.print("Game Over");
  display.display();
  if (score > highscore) {
    highscore = score;
  }
  delay(2000);
}

int nextBullet = 0;
void gameLoop() {

  // Reset the game state
  score = 0;
  lasers[0] = Obstacle(0);
  lasers[1] = Obstacle(1);
  lasers[2] = Obstacle(2);
  rocket.reset();
  player = Player();

  // Game loop
  while (true) {
    display.clearDisplay();
    display.setCursor((WIDTH / 5) * 2, 0);
    display.print(score);

    // Update and draw the player
    player.update();
    display.fillCircle(player.x, player.y, PLAYER_RADIUS, WHITE);
    
    // Update and draw all obstacles
    for (int i = 0; i < sizeof(lasers) / sizeof(lasers[0]); i++) {
      lasers[i].update();

      // Check collisions with player if in range
      if(lasers[i].x < player.x + PLAYER_RADIUS && checkObstacleCollision(player.x, player.y, lasers[i].x, lasers[i].y, lasers[i].x1, lasers[i].y1, OBSTACLE_THICKNESS)) {
        endGame();
        return;
      }
      drawThickLine(display, lasers[i].x, lasers[i].y, lasers[i].x1, lasers[i].y1, OBSTACLE_THICKNESS, WHITE);
    }

    // Update and draw the rocket
    rocket.update(player.y);
    display.drawTriangle(rocket.x, rocket.y, rocket.x + 5, rocket.y - 3, rocket.x + 5, rocket.y + 3, WHITE);
    // Check collisions with player if in range
    if (rocket.x < player.x + PLAYER_RADIUS && checkRocketCollision(player.x, player.y, rocket.x, rocket.y - 3, 5, 6)) {
      endGame();
      return;
    }
    
    display.display();
    score++;
  }
}

void loop() {
  display.clearDisplay();
  if (highscore != 0) {
    display.setCursor(10, HEIGHT / 3);
    display.print("Highscore: ");
    display.println(highscore);
    display.setCursor(10, display.getCursorY());
    display.print("Your score: ");
    display.println(score);
  }
  display.setCursor(0, 0);
  display.print("Press Button to Start");
  display.display();

  // Wait for button press
  while (digitalRead(BUTTON)) {}
  delay(200);
  gameLoop();
}