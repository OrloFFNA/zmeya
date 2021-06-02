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