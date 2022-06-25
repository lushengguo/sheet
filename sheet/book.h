#include "sheet.h"

namespace excel
{

template <class Cell> class Book
{
  public:
    bool write(const Position &position, size_t sheet_index, Cell &&value);
    bool write(const Position &position, size_t sheet_index, const Cell &value);
};
} // namespace excel