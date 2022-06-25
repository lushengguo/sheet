#pragma once
#include <string>
#include <string_view>

namespace excel
{
class CellView;
class Cell
{
  public:
    bool empty();

  private:
    friend class CellView;
    std::string value_;
};

class CellView
{
  public:
    CellView(Cell cell) : view_(cell.value_);

  private:
    std::string_view view_;
};

} // namespace excel