#pragma once

#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

using std::string;
using std::ostream;
using std::vector;

typedef uint64_t hash;

class hash_filter {
  public:
    virtual void append(const hash &) = 0;
    virtual vector<hash> into_vec() = 0;
};

class hasher {
  private:
    /* reference string */
    const string *S;

    /* roll attributes */
    size_t roll_offset;
    size_t roll_length;

    size_t roll_base;
    uint64_t roll_mod;
    uint64_t roll_val;

    const uint64_t pop_const;
    void pop();

    void append();

    hash iter();

  public:
    hasher(size_t length);
    ~hasher();
    void feed(const string &);
    vector<hash> consume(hash_filter &);
};
