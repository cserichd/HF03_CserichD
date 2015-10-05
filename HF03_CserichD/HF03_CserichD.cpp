// Cserich David

#include <iostream>

using namespace std;

class Kivetel: public exception {
  int id;
public:
  Kivetel(int i) : id(i) {}
  const char* what() const throw()
  {
    switch(id) {
      default: return "Unexpected exception!\n";               break;
      case 1:  return "Exception occured: Buffer is full!\n";  break;
      case 2:  return "Exception occured: Buffer is empty!\n"; break;
    }
  }
};

template <class T>
class CircularBuffer {
  T* buffer;
  int head;
  int tail;
  int size;
public:
  explicit CircularBuffer(int s = 10) {
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

  
  int getSize() const { return size;}
  
  bool isEmpty() const {
    if (head == tail) {
      return true;
    } else {
      return false;
    }
  }
  
  bool isFull() const {
    if (head == ( (tail + 1) % size )) {
      return true;
    } else {
      return false;
    }
  }
  
  void insert(const T element) {
    if (!isFull()) {
      buffer[tail] = element;
      tail = (tail + 1) % size;
    } else {
      throw Kivetel(1);
    }
  }
  
  T remove() {
    if (!isEmpty()) {
      T result = buffer[head];
      head = (head + 1) % size;
      return result;
    } else {
      throw Kivetel(2);
      return NULL;
    }
  }
  
  friend ostream& operator<<(ostream& os, const CircularBuffer& cb) {
    for (int i = cb.head; i != cb.tail; i = (i + 1) % cb.size) {
      os << cb.buffer[i] << " ";
    }
    return os;
  }
};

template <class U>
U getMax(U a, U b) {
  return ((a > b) ? a : b);
}

template<class T>
CircularBuffer<T> getMax(CircularBuffer<T> a, CircularBuffer<T> b) {
  return ((a.getSize() > b.getSize()) ? a : b);
}


int main() {
  CircularBuffer<double> dcb(2);
  try {
    dcb.insert(3.3);
    dcb.insert(4.4);
    cout << "cb= " << dcb << endl;
    double r = dcb.remove();
    cout << "r= " << r << endl;
    cout << "cb= " << dcb << endl;
    dcb.insert(5.5);
    cout << "cb= " << dcb << endl;
    dcb.insert(6.6);
  }
  catch (std::exception& e)
  {
    cerr << e.what() << endl;
  }
  
  float f1=1.23, f2=3.21;
  cout << getMax(f1,f2) << endl;
  
  CircularBuffer<int> icb1(1200);
  CircularBuffer<int> icb2 = icb1;
  try {
    icb1.insert(5);
    cout <<  getMax(icb2,icb1) << endl;
    icb1.remove();
    icb1.remove();
  }
  catch (std::exception& e)
  {
    cerr << e.what() << endl;
  }

}





