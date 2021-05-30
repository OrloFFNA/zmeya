#include <TroykaLedMatrix.h>
#define Yj A3
#define Xj A2
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

  void remove(int x, int y){
    Node* current = head;
        
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
 

};


TroykaLedMatrix matrix;

List snake;
int feedX = 7 - 2;
int feedY = 2;
List freeSpace;

void genFreeSpace() {
  for(int y = 0; y < 8; y++){
      for(int x = 0; x < 8; x++){
        freeSpace.push_back(7 - x, y);
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
  snake.push_back(7 - 0, 0);
  snake.push_back(7 - 0, 1); 
  snake.push_back(7 - 0, 2); 
  snake.push_back(7 - 0, 3);
  snake.push_back(7 - 0, 4);
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
    matrix.drawPixel(y, x - 1);
    if (!( feedX == x - 1 && feedY == y )){
        matrix.clearPixel(snake.getLastY(), snake.getLastX ());
    snake.pop();
    }
  }
  else{
  matrix.clear();
  }
}

void realLeft() {
  int x = snake.getHeadX();
  int y = snake.getHeadY();
  if( x < 7 && snake.notContains(x + 1, y)) {
    snake.push_start(x + 1, y);
    matrix.drawPixel(y, x + 1);
    if (!(feedX == x + 1 && feedY == y )){
        matrix.clearPixel(snake.getLastY(), snake.getLastX ());
    snake.pop();
    }
  }
  else{
  matrix.clear();
  }
}

void realDown() {
   int x = snake.getHeadX();
  int y = snake.getHeadY();
  if( y < 7 && snake.notContains(x, y + 1)) {
    snake.push_start(x, y + 1);
    matrix.drawPixel(y + 1, x);
    if (!( feedX == x && feedY == y + 1)){
        matrix.clearPixel(snake.getLastY(), snake.getLastX ());
    snake.pop();
    }
  }
  else{
  matrix.clear();
  }
}
 
void realUp() {
  int x = snake.getHeadX();
  int y = snake.getHeadY();
  if( y > 0 && snake.notContains(x, y - 1)) {
    snake.push_start(x, y - 1);
    matrix.drawPixel(y - 1, x);
    if (!( feedX == x && feedY == y - 1 )){
        matrix.clearPixel(snake.getLastY(), snake.getLastX ());
    snake.pop();
    }
  }
  else{
  matrix.clear();
  }
}

/*void spawnFeed() {
  int x = random(8);
  int y = random(8);
  while (snake.)
}
*/
void setup() {
  matrix.begin();
  //Serial.begin(9600);
  setupSnake();
  drawSnake();
  matrix.drawPixel(feedY, feedX);
}

List a;

void loop() { 
 // snake.print();
 //drawSnake();
 //Serial.println(memoryFree());
  int x,y,z;
z = digitalRead(Zj);
x = analogRead(Xj);
y = analogRead(Yj);

if(x > 700){
  realRight();
}
else if(x < 300){
  realLeft();
}
else if(y > 700){
  realUp();
}
else if(y < 300){
  realDown();
}
  delay(500);
  
  
}
