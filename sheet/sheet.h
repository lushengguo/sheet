#include "range.h"
#include <memory>
#include <unordered_map>

namespace excel
{

class Sheet
{
  public:
    CellView read(size_t row, size_t col);
    bool assign(size_t row, size_t col, Cell &&cell);

    template <typename FuncSignature>
    bool transaction_exec(FuncSignature &&func);

  private:
    size_t index(size_t row, size_t col);
    bool check(size_t row, size_t col);
    bool exist(size_t row, size_t col);

    void rollback();

  private:
    size_t index_;
    std::unordered_map<size_t, Cell> data_;

    static thread_local bool in_transaction_ = false;
    static thread_local std::unordered_map<size_t, Cell> modified_data_;

    static constexpr size_t row_exp_offset_ = sizeof(size_t) * 4;
    static constexpr size_t rc_limit_ = (2 << (sizeof(size_t) * 4)) - 2;
    static constexpr size_t invalid_index_ = (size_t)-1;
};

} // namespace excel