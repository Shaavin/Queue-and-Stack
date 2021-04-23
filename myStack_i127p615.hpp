#ifndef MYSTACK_HPP
#define MYSTACK_HPP

#include <algorithm>
#include <stdexcept>

template<typename Object>
class myStack {
  private:
    int m_top, m_size;
    Object* m_array;

    bool full() const {
      return m_top == m_size-1;
    }

  public:
    myStack(void) : m_top(-1), m_size(10) {
      m_array = new Object[m_size];
    }

    myStack(myStack&& rhs) : m_top(rhs.m_top), m_size(rhs.m_size),
      m_array(rhs.m_array) {
        m_array = new Object[rhs.m_size];
        rhs.m_top = -1;
        rhs.m_size = 10;
        rhs.m_array = nullptr;
      }

    myStack& operator=(myStack&& rhs) {
      std::swap(m_top, rhs.m_top);
      std::swap(m_size, rhs.m_size);
      std::swap(m_array, rhs.m_array);
      return *this;
    }

    myStack(const myStack<Object>& rhs) : m_top(rhs.m_top) {
        m_array = new Object[rhs.m_size];
        for(int i = 0; i < rhs.m_size; i++) {
          m_array[i] = rhs.m_array[i];
        }
    }

    myStack & operator=(const myStack & rhs) {
      myStack copy = rhs;
      std::swap(*this, copy);
      return *this;
    }

    ~myStack() {
      clear();
      delete[] m_array;
    }

    void push(const Object& obj) {
      if( full() ) {
        int newSize = m_size*2;
        Object* newArr = new Object[newSize];
        for(int i = 0; i < m_size; i++) {
          newArr[i] = m_array[i];
        }
        delete[] m_array;
        m_array = newArr;
        m_size = newSize;
      }

      m_array[++m_top] = obj;
    }

    Object pop() {
      if( empty() ) {
        throw std::runtime_error("Cannot pop from an empty stack");
      }

      Object answer = m_array[m_top];
      m_top--;
      return answer;
    }

    Object top() {
      if( empty() ) {
        throw std::runtime_error("Cannot peek top of an empty stack");
      }

      return m_array[m_top];
    }

    bool empty() {
      return m_top == -1;
    }

    void clear() {
      while( !empty() ) {
        pop();
      }
    }
};

#endif
