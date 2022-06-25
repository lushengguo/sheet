#include "sheet.h"

namespace excel
{
size_t Sheet::index(size_t row, size_t col)
{
    if (!check(row, col))
        return invalid_index_;

    return (row << row_exp_offset_) + col;
}

bool Sheet::check(size_t row, size_t col)
{
    return row <= rc_limit_ && col <= rc_limit_;
}

bool Sheet::exist(size_t row, size_t col)
{
    return data_.count(index(row, col) == 1);
}

CellView Sheet::read(size_t row, size_t col)
{
    if (exist(row, col))
        return CellView(data_.at(index(row, col)));

    return Cell();
}

bool Sheet::assign(size_t row, size_t col, Cell &&cell)
{
    if (!check(row, col))
        return false;

    size_t idx = index(row, col);
    if (in_transaction_ && modified_data_.count(idx) == 0)
        modified_data_[idx] = std::move(data_[idx]);

    data_[idx] = std::move(cell);
    return true;
}

template <typename FuncSignature>
bool Sheet::transaction_exec(FuncSignature &&func)
{
    if (in_transaction_)
        return false;

    in_transaction_ = true;
    bool res = func();
    if (!res)
        rollback();
    in_transaction_ = false;
    return res;
}

void Sheet::rollback()
{
    if (!in_transaction_)
        return;

    for (auto &&pair : modified_data_)
        data_[pair.first] = pair.second;
}

} // namespace excel