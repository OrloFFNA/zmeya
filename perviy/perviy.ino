#include <TroykaLedMatrix.h>
#define Yj A3
#define Xj A2
#define Zj 3
TroykaLedMatrix matrix;

int X, Y;

void setupSnake() {
  randomSeed(analogRead(0));
  X = random(8);
  Y = random(8);
  matrix.drawPixel(X, Y);
}

void right() {
  if(X < 8){
    matrix.clearPixel(X, Y);
    X++;
    matrix.drawPixel(X, Y);
  }
}

void left() {
  if(X > 1){
    matrix.clearPixel(X, Y);
    X--;
    matrix.drawPixel(X, Y);
  }
}

void down() {
  if(Y < 8){
    matrix.clearPixel(X, Y);
    Y++;
    matrix.drawPixel(X, Y);
  }
}

void up() {
  if(Y > 1){
    matrix.clearPixel(X, Y);
    Y--;
    matrix.drawPixel(X, Y);
  }
}
void setup() {
  matrix.begin();
  Serial.begin(9600);
  setupSnake();
  
}
void loop() {
int x,y,z;
z = digitalRead(Zj);
x = analogRead(Yj);
y = analogRead(Xj);
if(x < 600){
  right();
}
if(x > 400){
  left();
}
if(y > 600){
  up();
}
if(y < 400){
  down();
}
delay(100);
  /*for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      matrix.drawPixel(x, y);
      delay(300);
    }
  }
  matrix.clear();
*/
}
