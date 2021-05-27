#include <TroykaLedMatrix.h>
#define Y A3
#define X A2
#define Z 3
TroykaLedMatrix matrix;

void setup() {
  matrix.begin();
  Serial.begin(9600);
  
}
void loop() {
int x,y,z;
z = digitalRead(Z);
x = analogRead(X);
y = analogRead(Y);

  /*for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      matrix.drawPixel(x, y);
      delay(300);
     
    }
   
  }
  matrix.clear();
*/
}
