#include "Arduino_LED_Matrix.h"
const int GRIDY=8;
const int GRIDX=12;
const uint8_t LIVE=1;
const uint8_t DEAD=0;
ArduinoLEDMatrix matrix;
uint8_t state[GRIDY][GRIDX]={
  {0,0,0,0,0,1,0,1,1,0,0,0},
  {0,0,0,0,1,0,0,0,0,0,0,1},
  {0,0,0,1,1,0,0,0,1,0,0,1},
  {1,1,0,1,0,0,0,0,0,1,1,0},
  {1,1,0,1,0,0,0,0,0,1,1,0},
  {0,0,0,1,1,0,0,0,1,0,0,1},
  {0,0,0,0,1,0,0,0,0,0,0,1},
  {0,0,0,0,0,1,0,1,1,0,0,0},
  };

const int inPin = 13;
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
  uint8_t neighbors[8][12]={
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  };

  // put your main code here, to run repeatedly:
  while (true) {
    uint8_t ctr=0;
    for(int i=0;i<GRIDY;i++){
      for(int j=0;j<GRIDX;j++){
        ctr=0;
        for(int r=i-1;r<i+2 && r < GRIDY;r++){
          if(r < 0) {
            continue;
          }
          for(int c=j-1;c<j+2 && c < GRIDX;c++){
            if(c < 0){continue;}
            if(r == i && j == c) {continue;}
            if(state[r][c]==LIVE){ctr++;}
          }
        } 
        neighbors[i][j]=ctr;
      }
    }

    for(int i=0;i<GRIDY;i++){
      for(int j=0;j<GRIDX;j++){
        if(neighbors[i][j]==2){continue;}
        setPins(neighbors[i][j],state[i][j]);
        delay(1);
        int current = digitalRead(inPin);
        if(current!=LOW){
          state[i][j]=LIVE;
        }
        else{
          state[i][j]=DEAD;
        }
        delay(1);
        unset();
      }
    }

    matrix.renderBitmap(state,8,12); 
  }
}

void setPins(int n,int l){
  if(bitRead(n,2)==0){digitalWrite(2,HIGH);} 
  if(bitRead(n,1)==1){digitalWrite(4,HIGH);}
  if(bitRead(n,0)==1){digitalWrite(7,HIGH);}
  if(l==LIVE){digitalWrite(8,HIGH);}
}

void unset(){
  digitalWrite(2,LOW);
  digitalWrite(4,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}
