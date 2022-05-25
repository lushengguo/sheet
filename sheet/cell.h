#pragma once

template <typename Tp> class CELL
{
  public:
    bool empty();

    const Tp &value();
    Tp &value();

    void set(const Tp &);
    void set(Tp &&);

  private:
    Tp value_;
    bool hasValue_;
};