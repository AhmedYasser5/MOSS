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
    const string &S;
    size_t s_offset;

    /* roll value */
    /* TODO: check what happend when you multiply 64bit vars*/
    size_t base;
    uint64_t mod;
    uint64_t pop_const;
    uint64_t roll;
    size_t length;

    void pop();
    void append(char16_t c);
    hash iter();

  public:
    hasher(size_t length, const string &S);
    ~hasher();
    vector<hash> consume(hash_filter &);
};
