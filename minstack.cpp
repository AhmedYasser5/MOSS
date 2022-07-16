#include "minstack.hpp"

template <typename T> minStack<T>::minStack(const size_t size): st(size) {}
template <typename T> minStack<T>::~minStack() {}

template <typename T> size_t minStack<T>::size() const { return st.size(); }

template <typename T> const T &minStack<T>::min() const {
  return st.back().st_min;
}

template <typename T> const T &minStack<T>::top() const {
  return st.back().el_val;
}

template <typename T> T &minStack<T>::pop() {
  T &last = st.back().el_val;
  st.pop();
  return last;
}

template <typename T> void minStack<T>::push(const T &item) {
  T &st_current_min = st.min();
  T &st_new_min = min(st_current_min, item);
  st.push_back({.el_val = item, .st_min = st_new_min});
}
