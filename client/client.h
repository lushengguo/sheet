#pragma once
#include "server/server.h"

template <typename ValueType> class Client
{
  public:
  
  public:
    void begin_transaction();
    void end_transaction();

    std::pair<HasValue, const ValueType *> read(size_t x, size_t y);
    void write(size_t x, size_t y, ValueType &&value);

  private:
    RPC &server;
};