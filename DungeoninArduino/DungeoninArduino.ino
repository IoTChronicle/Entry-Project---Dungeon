#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Pins of Arduino
const int continueButton = 7;
const int quitButton = 6;
const int life3Pin = 5;
const int life2Pin = 4;
const int life1Pin = 3;
const int gainScorePin = 2;

//Treasure: A = +1; B= +2; C= +3
//Trap: T = 0; Monster: M = -1
char array[] = "ABCTM";
char event;
int lives = 3;
int scores = 0;
int keep = LOW; //player choice
int quit = LOW;

void setup() {
  //Outputs
  pinMode(life3Pin, OUTPUT);
  pinMode(life2Pin, OUTPUT);
  pinMode(life1Pin, OUTPUT);
  pinMode(gainScorePin, OUTPUT);

  //Inputs
  pinMode(continueButton, INPUT);
  pinMode(quitButton, INPUT);

  //Set up baud rate for communication between Arduino and Serial Monitor
  Serial.begin(9600);

  //random seed
  srand(time(NULL));

  //Turn ON 3 life LED
  digitalWrite(life3Pin, HIGH);
  digitalWrite(life2Pin, HIGH);
  digitalWrite(life1Pin, HIGH);
}

void loop() {
    keep = digitalRead(continueButton);
    quit = digitalRead(quitButton);

    if(keep == HIGH){
        event = array[rand() % 5];

        if(event == 'A') {
            Serial.print("You found a treasure, your scores + 1. \n");
            scores += 1;
            digitalWrite(gainScorePin, HIGH);
        }
        else if (event == 'B') {
            Serial.print("You found a treasure, your scores + 2. \n");
            scores += 2;
            digitalWrite(gainScorePin, HIGH);
        }
        else if (event == 'C') {
            Serial.print("You found a treasure, your scores + 3. \n");
            scores += 3;
            digitalWrite(gainScorePin, HIGH);
        }
        else if (event == 'T') {
            Serial.print("It is a trap! But you avoid it with your skills. \n");
            digitalWrite(gainScorePin, LOW);
        }
        else {
            Serial.print("A monster appeared! You fight it and lose 1 life. \n");
            digitalWrite(gainScorePin, LOW);

            lives -= 1;
            if (lives == 2) digitalWrite(life3Pin, LOW);
            if (lives == 1) digitalWrite(life2Pin, LOW);
            if (lives == 0) digitalWrite(life1Pin, LOW);

            if(lives == 0){
                scores = 0;
                quit = HIGH;
            }
        }

        Serial.print("Your scores is ");
        Serial.print(scores);
        Serial.print(" .\n");
        delay(1000);
    }

    if(quit == HIGH){
      Serial.println("\n Your final score is \n");
      Serial.println(scores);
      scores = 0;

      //Restart the game
      //Turn ON 3 life LED
      digitalWrite(life3Pin, HIGH);
      digitalWrite(life2Pin, HIGH);
      digitalWrite(life1Pin, HIGH);

      digitalWrite(gainScorePin, LOW);
      lives = 3;

      delay(1000);
    }
}
