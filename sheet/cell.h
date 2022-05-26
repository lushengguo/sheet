#pragma once
#include <assert.h>
#include <memory>
#include <string.h>
#include <string>

typedef bool HasValue;

class Variant
{
  public:
    enum class Type
    {
        Str,
        Integer,
        Float
    };

  private:
    union {
        char *str_;
        long long integer_;
        long double float_;
    };

    Type type_;

  public:
    bool equal(const Variant &v) const
    {
        if (v.type_ != type_)
            return false;

        switch (v.type_)
        {
        case Type::Str:
            return equal(v.str_);
        case Type::Integer:
            return equal(v.integer_);
        case Type::Float:
            return equal(v.float_);
        default:
            return false;
        }
        return false;
    }

    bool equal(const char *s) const
    {
        if (type_ != Type::Str)
            return false;
        return strcmp(s, str_) == 0;
    }

    bool equal(long long i) const
    {
        if (type_ != Type::Integer)
            return false;
        return float_ == i;
    }

    bool equal(long double f) const
    {
        if (type_ != Type::Float)
            return false;
        return float_ == f;
    }

    bool is_number() const
    {
        return type_ == Type::Float || type_ == Type::Integer;
    }

    void set(int i)
    {
        integer_ = i;
        type_ = Type::Integer;
    }

    void set(long double f)
    {
        float_ = f;
        type_ = Type::Float;
    }

    void set(const char *str, size_t len)
    {
        str_ = (char *)malloc(len + 1);
        if (!str_)
            assert(false);

        memcpy(str_, str, len);
        str_[len] = 0;
        type_ = Type::Str;
    }
};

class CELL
{
  public:
    bool empty();

    const Variant &value() const;
    Variant &value();

    void set(const Variant &);
    void set(Variant &&);

  private:
    Variant value_;
    bool has_value_;
};