#include <TroykaLedMatrix.h>
#define Yj A3
#define Xj A2
#define Zj 3


//неважно

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

class List{
  public:
  Node* head;

  List(){
    head = NULL;
  }
//неважно
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
      Serial.println();
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
  bool notContains(int x, int y){
    Node* current = head;
    while (current){
      if (x == current->x && y == current->y) return false;
      current = current->next;
    }
    return true;
  }
 

};


TroykaLedMatrix matrix;

List snake;


void setupSnake() {
  /*
  int X, Y;
  randomSeed(analogRead(0));
  X = random(8);
  Y = random(8);
  snake.push_back(X,Y);
  */
  snake.push_back(7 - 1,3);
  snake.push_back(7 - 1,2);
  snake.push_back(7 - 1,1);
  snake.push_back(7 - 1,0);
  
}

void drawSnake() {
  matrix.clear();
  Node* current = snake.head;
  while (current){
    int x = current->x;
    int y = current->y;
    current = current->next;
    matrix.drawPixel(y, x);
  }
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
  int x = snake.getHeadX();
  int y = snake.getHeadY();
  if( x > 0 && snake.notContains(x - 1, y)) {
    snake.push_start(x - 1, y);
    snake.pop();
  }
}

void realLeft() {
  int x = snake.getHeadX();
  int y = snake.getHeadY();
  if( x < 7 && snake.notContains(x + 1, y)) {
    snake.push_start(x + 1, y);
    snake.pop();
  }
}
/*
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
*/

void setup() {
  matrix.begin();
  Serial.begin(9600);
  setupSnake();
  
}

List a;

void loop() { 
  snake.print();
  drawSnake();
  realLeft();
  delay(500);
  /*
 a.push_back(3,5);
 a.print();
int bitMap[8][8] = {
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
