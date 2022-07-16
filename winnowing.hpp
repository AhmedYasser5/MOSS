#pragma once

/* TODO: find a way to automate generating error codes */

#define EXIT_WINNOWING_UNDEFINED_STATE 1

#include "hash.hpp"
#include "minstack.hpp"

#include <stdint.h>
#include <stdio.h>

using std::cout;
using std::endl;

class winnowingFilter : hash_filter {
private:
  /* window size */
  size_t window_length;

  /* it uses two stacks for constant time operations */
  minStack<hash> window_stack_in;
  minStack<hash> window_stack_out;
  enum windowStat { WINDOW_INITIAL_FILLING, WINDOW_OUTPUTING };
  windowStat window_stat;

  /* filtered hashes */
  vector<hash> filtered;

public:
  winnowingFilter(const size_t window_length);
  void append(const hash &);
  vector<hash> into_vec();
};
