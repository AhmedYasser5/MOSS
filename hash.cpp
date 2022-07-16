#include "hash.hpp"
#include <random>
#include <math.h>
#include <time.h>


/* TODO: extract math to a separate file. */
bool is_prime(uint64_t n) {
  for (size_t i = 0; i < sqrt(n) + 1; i++) {
    if (i * i == n) {
      return false;
    }
  }
  return true;
}

/* TODO: add min and max args to the random prime generator. */
uint64_t gen_prime() {
  uint64_t p;
  srand(time(NULL));
  while (!is_prime(p=rand()));
  return p;
}

/* TODO: impl(pow_mod). */
uint64_t pow_mod(uint64_t b, uint64_t p, uint64_t roll_mod) {
  
}

hasher::hasher(size_t roll_length)
    : S(NULL), roll_length(roll_length), roll_base(gen_prime()),
      roll_mod(gen_prime()),
      pop_const(pow_mod(roll_base, roll_length, roll_mod)), roll_val(0) {}


void hasher::feed(const string &S) {
  this->S = &S;
  /* reset the roll */
  roll_offset = 0;
  roll_length = 0;
  /* precalcualte first hash */
  for (size_t i = 0; i < roll_length; i++) {
    roll_val = (roll_val * roll_base) % roll_mod;
    roll_val += this->S->at(i);
  }
}

void hasher::pop() {
  char pop_char = S->at(roll_offset);
  uint64_t pop_val = (pop_char * pop_const) % roll_mod;
  roll_val -= pop_val;
  roll_offset += 1;
}

/* TODO: check what happens when you multiply 64bit vars. */
void hasher::append() {
  roll_val = (roll_val * roll_base) % roll_mod;
  roll_val += S->at(roll_offset + roll_length);
}

hash hasher::iter() {
  pop();
  append();
  return roll_val;
}

vector<hash> hasher::consume(hash_filter &f) {
  f.append(roll_val);
  for (size_t i = 0; i < S->size() - roll_length + 1; i++) {
    f.append(iter());
  }
  return f.into_vec();
}
