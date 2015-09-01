#include "jsonvalue.h"


JSONValue::JSONValue(std::string s) :
    prim_flag(PRIMFLAG_STRING),
    primitive(new std::string(s))
{
}

JSONValue::JSONValue(decimal d) :
    prim_flag(PRIMFLAG_DECIMAL),
    primitive(d)
{
}

JSONValue::JSONValue(real r) :
    prim_flag(PRIMFLAG_REAL),
    primitive(r)
{
}

JSONValue::JSONValue(bool b) :
    prim_flag(PRIMFLAG_BOOL),
    primitive(b)
{
}

JSONValue::JSONValue(void *n) :
    prim_flag(PRIMFLAG_NULL)
{

}

JSONValue::JSONValue() :
    prim_flag(0)
{
}

JSONValue::~JSONValue()
{
    if (is_string())
        delete primitive.s;
}

JSONValue &JSONValue::operator=(const JSONValue &other)
{
    prim_flag = other.prim_flag;

    if (prim_flag != 0) {
        if (other.is_string())
            primitive.s = new std::string(*other.primitive.s);
        else if (other.is_decimal())
            primitive.d = other.primitive.d;
        else if (other.is_real())
            primitive.r = other.primitive.r;
        else if (other.is_boolean())
            primitive.b = other.primitive.b;
    }

    return *this;
}

bool JSONValue::is_object() const
{
    return false;
}

bool JSONValue::is_array() const
{
    return false;
}

bool JSONValue::is_string() const
{
    return (PRIMFLAG_STRING & prim_flag) != 0;
}

bool JSONValue::is_decimal() const
{
    return (PRIMFLAG_DECIMAL & prim_flag) != 0;
}

bool JSONValue::is_real() const
{
    return (PRIMFLAG_REAL & prim_flag) != 0;
}

bool JSONValue::is_boolean() const
{
    return (PRIMFLAG_BOOL & prim_flag) != 0;
}

bool JSONValue::is_null() const
{
    return (PRIMFLAG_NULL & prim_flag) != 0;
}

std::string& JSONValue::get_string()
{
    return *primitive.s;
}

decimal& JSONValue::get_decimal()
{
    return primitive.d;
}

real& JSONValue::get_real()
{
    return primitive.r;
}

bool& JSONValue::get_boolean()
{
    return primitive.b;
}

Primitive::Primitive(std::string* s) : s(s)
{
}

Primitive::Primitive(decimal d) : d(d)
{
}

Primitive::Primitive(real r) : r(r)
{
}

Primitive::Primitive(bool b) : b(b)
{
}

Primitive::Primitive()
{
}

Primitive::~Primitive()
{
}
