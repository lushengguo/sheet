#pragma once
#include "cell.h"

namespace excel
{

struct RANGE
{
    size_t row_from_;
    size_t col_from_;
    size_t row_to_;
    size_t col_to_;
};

} // namespace excel