#include <TroykaLedMatrix.h>
#define Xj A3
#define Yj A2
#define Zj 3

TroykaLedMatrix matrix;
List freeSpace;
List snake;

int feedX = 2;
int feedY = 4;

void genFreeSpace();
void right();
void left();
void down();
void up();



void setupSnake() {
  /*
  int X, Y;
  randomSeed(analogRead(0));
  X = random(8);
  Y = random(8);
  snake.push_back(X,Y);
  */
  snake.push_back(2, 7); 
  snake.push_back(3, 7); 
  snake.push_back(4, 7);
  snake.push_back(5, 7);
  freeSpace.remove(2, 7);
  freeSpace.remove(3, 7);
  freeSpace.remove(4, 7);
  freeSpace.remove(5, 7);

}


void drawSnake() {
  matrix.clear();
  Node* current = snake.head;
  while (current){
    int x = current->x;
    int y = current->y;
    current = current->next;
    matrix.drawPixel(x, y);
  }
}

void setup() {
  matrix.begin();
  Serial.begin(9600);
  setupSnake();
  drawSnake();
  genFreeSpace();
  matrix.drawPixel(feedX, feedY);
  freeSpace.remove(feedX, feedY);
}


void loop() { 
 // snake.print();
 //drawSnake();
 //Serial.println(memoryFree());
 Serial.println(freeSpace.notContains(2, 4));
 Serial.println(freeSpace.lenght);
  int x,y,z;
z = digitalRead(Zj);
x = analogRead(Xj);
y = analogRead(Yj);

//Serial.println(x);

if(x < 300){
  right();
}
else if(x > 700){
  left();
}
else if(y > 700){
  up();
}
else if(y < 300){
  down();
}
  delay(200);
  
}
 

 void genFreeSpace() {
  for(int y = 0; y < 8; y++){
      for(int x = 0; x < 8; x++){
        freeSpace.push_back(x, y);
      }
  }
}
void right() {
  int x = snake.getHeadX();
  int y = snake.getHeadY();
  if( x < 7 && snake.notContains(x + 1, y)) {
    freeSpace.remove(x + 1, y);
    snake.push_start(x + 1, y);
    matrix.drawPixel(x + 1, y);
    if (!( feedX == x + 1 && feedY == y )){
        matrix.clearPixel(snake.getLastX(), snake.getLastY ());
        snake.pop();
        freeSpace.push_back(snake.getLastX(), snake.getLastY ());
    }
    else{
      freeSpace.push_back(feedX, feedY);//возможно ошибка
      feedX = -1;
      feedY = -1;
    }
  }
  else{
  //matrix.clear();
  }
}

void left() {
  int x = snake.getHeadX();
  int y = snake.getHeadY();
  if( x > 0 && snake.notContains(x - 1, y)) {
    freeSpace.remove(x - 1, y);
    snake.push_start(x - 1, y);
    matrix.drawPixel(x - 1, y);
    if (!(feedX == x - 1 && feedY == y )){
        matrix.clearPixel(snake.getLastX(), snake.getLastY ());
        snake.pop();
        freeSpace.push_back(snake.getLastX(), snake.getLastY ());
    }
    else{
      freeSpace.push_back(feedX, feedY);//возможно ошибка
      feedX = -1;
      feedY = -1;
    }
  }
  else{
  //matrix.clear();
  }
}

void down() {
  int x = snake.getHeadX();
  int y = snake.getHeadY();
  if( y < 7 && snake.notContains(x, y + 1)) {
    freeSpace.remove(x, y + 1);
    snake.push_start(x, y + 1);
    matrix.drawPixel(x, y + 1);
    if (!( feedX == x && feedY == y + 1)){
        matrix.clearPixel(snake.getLastX(), snake.getLastY ());
        snake.pop();
        freeSpace.push_back(snake.getLastX(), snake.getLastY ());
    }
    else{
      freeSpace.push_back(feedX, feedY);//возможно ошибка
      feedX = -1;
      feedY = -1;
    }
  }
  else{
  //matrix.clear();
  }
}
 
void up() {
  int x = snake.getHeadX();
  int y = snake.getHeadY();
  if( y > 0 && snake.notContains(x, y - 1)) {
    freeSpace.remove(x, y - 1);
    snake.push_start(x, y - 1);
    matrix.drawPixel(x, y - 1);
    if (!( feedX == x && feedY == y - 1 )){
        matrix.clearPixel(snake.getLastX(), snake.getLastY ());
        snake.pop();
        freeSpace.push_back(snake.getLastX(), snake.getLastY ());
    }
    else{
      freeSpace.push_back(feedX, feedY);//возможно ошибка
      feedX = -1;
      feedY = -1;
    }
  }
  else{
  //matrix.clear();
  }
}

void spawnFeed() {
  int g = random(freeSpace.lenght);
  Node* point = freeSpace.getPoint(g);
  int x = point -> x;
  int y = point -> y;
  Serial.print(x);
  Serial.print("  ");
  Serial.println(y);
  feedX = x;
  feedY = y;
  matrix.drawPixel(x, y);
  
}


