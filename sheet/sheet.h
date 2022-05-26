#include "range.h"
#include <memory>

typedef std::pair<size_t, size_t> Position;

template <typename Cell> class Sheet
{
  public:
    Cell &read(const Position &position);

  private:
    Position real_position(const Position &);
    Position real_position(size_t row, size_t col);

  private:
    size_t index_;
};