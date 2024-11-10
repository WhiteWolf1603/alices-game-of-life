#include "Arduino_LED_Matrix.h"

/* Dimensions of the Matrix or the Grid.
 * Represents the LED Grid on the Arduino Microcontroller */
const uint8_t GRIDY = 8;
const uint8_t GRIDX = 12;

/* States of a cell within the grid. */
const uint8_t LIVE = 1;
const uint8_t DEAD = 0;

/* Object used to display the current generation to the 
 * the LED Grid on the Arduino. */
ArduinoLEDMatrix matrix;

/* Current state of the generation. Dimensions of the 
 * grid are GRIDY and GRIDX. */
uint8_t state[GRIDY][GRIDX]={
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };

/* The following grid will store the neighbors of the 
 * current generation. The number of neighbors will be
 * used as input for the logical circuit, which determine
 * the future state of the cell. */
uint8_t neighbors[8][12]={
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };

/* The inPin is the result produced by the logical circuit.
 * The result will determine wether a cell stays/becomes ALIVE
 * or DEAD. A low output means the cell will be DEAD, whereas,
 * a high output means that the cell will remain ALIVE. */
const int inPin = 13;

/* Initialize the output and the input pins. Begin the Serial 
 * to log the output and matrix to start the LED Grid.*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  matrix.begin();
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(13,INPUT);
  matrix.renderBitmap(state,8,12);
}

void loop() {
  uint8_t i;
  uint8_t j;
  uint8_t input;

  // put your main code here, to run repeatedly:
  while (true) {
    Serial.println("***");
    for(i = 0; i < GRIDY; i++) {
      for(j = 0; j < GRIDX; j++) {
        neighbors[i][j] = calculateNeighbors(i, j);
      }
    }

    for(i = 0; i < GRIDY; i++){
      for(j = 0; j < GRIDX; j++){
        // According to the rules we do not change the state
        // of the cell if we have 2 neighbors
        if(neighbors[i][j] == 2) {
          continue;
        }
        
        // Set the pins as the binary representation of the 
        // number of neighbors.
        setPins(neighbors[i][j] , state[i][j]);
        
        delay(1);
        input = digitalRead(inPin);
        if(input != LOW) {
          state[i][j] = LIVE;
        }
        else {
          state[i][j] = DEAD;
        }

        delay(10);

        // Set all pins to LOW
        unset();
      }
    }

    // Print the next generation to the LED Grid.
    matrix.renderBitmap(state,8,12); 
  }
}

int calculateNeighbors(int i, int j) {
  int ctr=0;
  int r, c;

  for(r = i - 1; r < i + 2 && r < GRIDY; r++){
    if(r < 0) {
      continue;
    }
    
    for(c = j - 1; c < j + 2 && c < GRIDX; c++){
      if(c < 0) {continue;}
            
      if(r == i && j == c) {continue;}
      
      if(state[r][c] == LIVE) {ctr++;}
    }
  } 
  return ctr;
}

/* This function sets the pins to binary representation of 
 * the number of neighbors. It also sets the current state
 * of the cell to the corresponding PIN. */
void setPins(int n, int s){
  if(bitRead(n, 2) == 0) {
    digitalWrite(2, HIGH);
  } 
  if(bitRead(n, 1) == 1) {
    digitalWrite(4, HIGH);
  }
  if(bitRead(n, 0) == 1) {
    digitalWrite(7, HIGH);
  }
  if(s == LIVE){
    digitalWrite(8, HIGH);
  }
  return;
}

void unset(){
  digitalWrite(2,LOW);
  digitalWrite(4,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}
