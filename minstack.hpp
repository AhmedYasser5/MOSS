#pragma once

#include <stdint.h>
#include <vector>

using std::min;
using std::vector;
using std::size_t;

template <typename T> class minStack {
private:
  struct stElem {
    T &el_val;
    T &st_min;
  };
  vector<const stElem> st;

public:
  minStack(const size_t size);
  ~minStack();
  void push(const T &);
  T &pop();
  const T &top() const;
  const T &min() const;
  size_t size() const;
};
