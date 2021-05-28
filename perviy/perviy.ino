#include <TroykaLedMatrix.h>
#define Yj A3
#define Xj A2
#define Zj 3



class List{
  class Node{
    public:
    int x;
    int y;
    Node* next;
    Node(int x, int y){
      this->x = x;
      this->y = y;
      next = NULL;   
    }
  };

  public:
  Node* head;

  List(){
    head = NULL;
  }

  void push_back(int x, int y){
    if (head == NULL){
      head = new Node(x, y);
    }
    else{
      Node* current = head;
      while (current->next){
        current = current->next;
      }
      current->next = new Node(x, y);
    }
  }

   void print(){
    Node* current = head;
      while (current){
        Serial.print(current->x);
        Serial.print( " " );
        Serial.println(current->y);
        current = current->next;
        
      }
  }

  void pop(){
    Node* current = head;
      while (current->next->next){
        current = current->next;
      }
      current->next = NULL;
  }

  void push_start(int x, int y){
    Node* n = new Node(x, y);
    n->next = head;
    head = n;
  }

  int getHeadX(){
    return head->x;
  }

  int getHeadY(){
    return head->y;
  }

};


TroykaLedMatrix matrix;



int X, Y;


void setupSnake() {
  randomSeed(analogRead(0));
  X = random(8);
  Y = random(8);
  matrix.drawPixel(0, 0);
}
 
void drawBitMap(int bitMap[8][8]){
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
     if(bitMap[y][x] == 1){
      matrix.drawPixel(y, x);
     }
    }
  }
}

void realRight() {
  if(X < 7){
    matrix.clearPixel(X, Y);
    X++;
    matrix.drawPixel(X, Y);
  }
}

void realLeft() {
  if(X > 0){
    matrix.clearPixel(X, Y);
    X--;
    matrix.drawPixel(X, Y);
  }
}

void realDown() {
  if(Y < 7){
    matrix.clearPixel(X, Y);
    Y++;
    matrix.drawPixel(X, Y);
  }
}

void realUp() {
  if(Y > 0){
    matrix.clearPixel(X, Y);
    Y--;
    matrix.drawPixel(X, Y);
  }
}

void right() {
  realUp();
}

void left() {
  realDown();
}

void down() {
  realRight();
}

void up() {
  realLeft();
}


void setup() {
  matrix.begin();
  Serial.begin(9600);
  setupSnake();
  
}

List a;

void loop() { 
 a.push_back(3,5);
 a.print();
 /* int bitMap[8][8] = {
    {0,0,0,0,0,0,0,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,0},
    {0,1,1,0,0,1,1,0},
    {0,1,1,0,0,1,1,0},
    {0,0,0,0,0,0,0,0}
  };
  drawBitMap(bitMap);
  delay(1000);

int x,y,z;
z = digitalRead(Zj);
x = analogRead(Xj);
y = analogRead(Yj);

Serial.print("x = ");
Serial.println(x);
Serial.print("y = ");
Serial.println(y);

if(x > 700){
  right();
}
if(x < 300){
  left();
}
if(y > 700){
  up();
}
if(y < 300){
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
