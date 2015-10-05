// Cserich David
/*
 Készítsd el STL tárolók használata nélkül a körkörös puffer /FIFO tároló, körbeforduló írással, olvasással/ osztály sablont (CircularBuffer), amely tetszőleges típusú elemeket képes tárolni! A puffer mérete min. 1, max. 1000, amelyet a konstruktor paramétereként lehet megadni. Ha nincs megadva, vagy nincs az előbb megadott tartományban, akkor alapértelmezett mérete 10. A remove művelet kiveszi a legelső (legkorábban betett) elemet a pufferből, az insert művelet pedig a következő üres helyre teszi a paraméterként átadott elemet, amennyiben ez lehetséges (nincs felülírás!). Az isEmpty és isFull bool visszatérési típusú fv. információt ad a puffer állapotáról értelemszerűen (üres, megtelt). Üres pufferből történő kivételkor, illetve teli pufferbe történő íráskor keletkezzen kivételes esemény (std::exception osztályból leszámaztatott saját hiba osztály)! 
 */

#include <iostream>

template <class T>
class CircularBuffer {
  T* buffer;
  int head;
  int tail;
  int size;
public:
  CircularBuffer(int s = 10) {
    if (( s > 0 ) && ( s <= 1000 )) {
      buffer = new T[s+1];
      size = s+1;
    } else {
      buffer = new T[11];
      size = 11;
    }
    tail = 0;
    head = 0;
  }
  
  bool isEmpty() {
    if (head == tail) {
      return true;
    } else {
      return false;
    }
  }
  
  bool isFull() {
    if (head == ( (tail + 1) % size )) {
      return true;
    } else {
      return false;
    }
  }
  
  void insert(T element) {
    if (!isFull()) {
      buffer[(tail++) % size] = element;
    }
  }
  
  T remove() {
    if (!isEmpty()) {
      return buffer[(head++) % size];
    } else {
      return NULL;
    }
  }
  
};