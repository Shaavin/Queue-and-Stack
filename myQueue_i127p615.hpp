#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <algorithm>
#include <stdexcept>

template<typename Object>
class myQueue {
  private:
    int m_front, m_back, m_size;
    Object* m_array;

    bool full() const {
      return ((m_back+1) % m_size == m_front);
    }

  public:
    myQueue(void) : m_front(-1), m_back(-1), m_size(10) {
      m_array = new Object[10];
    }

    myQueue(myQueue&& rhs) : m_front(rhs.m_front), m_back(rhs.m_back),
      m_size(rhs.m_size), m_array(rhs.m_array) {
        m_array = new Object[rhs.m_size];
        rhs.m_front = -1;
        rhs.m_back = -1;
        rhs.m_size = 10;
        rhs.m_array = nullptr;
    }

    myQueue& operator=(myQueue&& rhs) {
      std::swap(m_front, rhs.m_front);
      std::swap(m_back, rhs.m_back);
      std::swap(m_size, rhs.m_size);
      std::swap(m_array, rhs.m_array);
      return *this;
    }

    myQueue(const myQueue<Object>& rhs) : m_front(rhs.m_front),
      m_back(rhs.m_back), m_size(rhs.m_back) {
        m_array = new Object[rhs.m_size];
        for(int i = 0; i < rhs.m_size; i++) {
          m_array[i] = rhs.m_array[i];
        }
    }

    myQueue& operator=(const myQueue& rhs) {
      myQueue copy = rhs;
      std::swap(*this, copy);
      return *this;
    }

    ~myQueue() {
      clear();
      delete[] m_array;
    }

    void enqueue(const Object& obj) {
      if( full() ) {
          int newSize = m_size*2;
          Object* newArr = new Object[newSize];
          int itr = m_front;
          for(int i = 0; i < m_size; i++) {
            newArr[i] = m_array[itr];
            itr = (itr+1) % m_size;
          }
          delete[] m_array;
          m_array = newArr;
          m_front = 0;
          m_back = m_size;
          m_size = newSize;
      } else if( empty() ) {
          m_front = m_back = 0;
      } else {
          m_back = (m_back+1) % m_size;
      }

      m_array[m_back] = obj;
    }

    Object dequeue() {
      if( empty() ) {
          throw std::runtime_error("Cannot dequeue from an empty queue");
      } else if( m_front == m_back ) {
          Object answer = m_array[m_front];
          m_front = m_back = -1;
          return answer;
      } else {
          Object answer = m_array[m_front];
          if(m_front+1 >= m_size) {
              m_front = 0;
          } else {
              m_front = (m_front+1) % m_size;
          }
          return answer;
      }
    }

    Object front() {
      if( empty() ) {
        throw std::runtime_error("Cannot peek front of an empty queue");
      }

      return m_array[m_front];
    }

    bool empty() {
      return (m_front == -1) && (m_back == -1);
    }

    void clear() {
      m_front = m_back = -1;
    }
};

#endif
