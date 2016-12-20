#ifndef BF_H_
#define BF_H_

#pragma once

#include <cstdint>
#include <string>
#include <sstream>


typedef std::basic_stringstream<uint8_t> bytestream;

class BF
{
 public:
  static const int MEM_SIZE = 30000;
  BF();
  bool interpret(const std::string &src, bytestream &is, bytestream &os);
  void reset();
  int ptr() const { return ptr_; }
 private:
  uint8_t mem_[MEM_SIZE];
  int ptr_;
};

#endif /* BF_H_ */
