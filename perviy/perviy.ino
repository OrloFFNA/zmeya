#include <TroykaLedMatrix.h>
#define Xj A3
#define Yj A2
#define Zj 3

extern int __bss_end;
extern void *__brkval;

int memoryFree()
{
   int freeValue;
   if((int)__brkval == 0)
      freeValue = ((int)&freeValue) - ((int)&__bss_end);
   else
      freeValue = ((int)&freeValue) - ((int)__brkval);
   return freeValue;
}

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
  Node* last;
  int lenght = 0;

  List(){
    head = NULL;
    last = NULL;
  }
//неважно
  void push_back(int x, int y){
    lenght++;
    if (head == NULL){
      head = new Node(x, y);
      last = head;
    }
    else{
      Node* current = head;
      while (current->next){
        current = current->next;
      }
      current->next = new Node(x, y);
      last = current->next;
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
    lenght--;
    Node* current = head;
      while (current->next->next){
        current = current->next;
      }
      delete current->next;
      current->next = NULL;
      last = current;
  }

  void push_start(int x, int y){
    lenght++;
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

  int getLastX(){
    return last->x;
  }

  int getLastY(){
    return last->y;
  }
  
  bool notContains(int x, int y){
    Node* current = head;
    while (current){
      if (x == current->x && y == current->y) return false;
      current = current->next;
    }
   
    return true;
  }


 void remove(int x, int y){
  Node* current = head;
  lenght--;
  if (current->x == x && current->y == y){
    Node* n = head->next;
    delete head;
    head = n;
  return;
  }
  while (current->next){
    if (current->next->x == x && current->next->y == y){
      Node* n = current->next->next;
      delete current->next;
      current->next = n;

    return;
    }
    current = current->next;
  }
}

 Node* getPoint(int i){
  Node* current = head;
  int k = 0;
  while (k < i){
    k++;
    current = current->next;
  }
  
  return current;
  }
};


TroykaLedMatrix matrix;

List snake;
int feedX = 2;
int feedY = 4;
List freeSpace;

void genFreeSpace() {
  for(int y = 0; y < 8; y++){
      for(int x = 0; x < 8; x++){
        freeSpace.push_back(x, y);
      }
  }
}

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

void realLeft() {
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

void realDown() {
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
 
void realUp() {
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

void setup() {
  matrix.begin();
  Serial.begin(9600);
  setupSnake();
  drawSnake();
  genFreeSpace();
  matrix.drawPixel(feedX, feedY);
  freeSpace.remove(feedX, feedY);
}

List a;

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
  realRight();
}
else if(x > 700){
  realLeft();
}
else if(y > 700){
  realUp();
}
else if(y < 300){
  realDown();
}
  delay(200);
  
  
}
