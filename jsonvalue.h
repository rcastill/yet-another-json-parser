#ifndef JSONVALUE_H
#define JSONVALUE_H

#include <memory>
#include <string>

typedef std::int64_t    decimal;
typedef double          real;

#define PRIMFLAG_STRING     1
#define PRIMFLAG_DECIMAL    2
#define PRIMFLAG_REAL       4
#define PRIMFLAG_BOOL       8
#define PRIMFLAG_NULL       16

union Primitive
{
    Primitive(std::string* s);
    Primitive(decimal d);
    Primitive(real r);
    Primitive(bool b);
    Primitive();

    ~Primitive();

    std::string*    s;
    decimal         d;
    real            r;
    bool            b;
};

class JSONValue
{
private:
    unsigned char   prim_flag;
    Primitive       primitive;

public:
    JSONValue(std::string s);
    JSONValue(decimal d);
    JSONValue(real r);
    JSONValue(bool b);
    JSONValue(void* n);
    JSONValue();

    virtual ~JSONValue();

    JSONValue& operator=(const JSONValue& other);

    virtual bool is_object()    const;
    virtual bool is_array()     const;

    bool is_string()    const;
    bool is_decimal()   const;
    bool is_real()      const;
    bool is_boolean()   const;
    bool is_null()      const;

    std::string&    get_string();
    decimal&        get_decimal();
    real&           get_real();
    bool&           get_boolean();
};

#endif // JSONVALUE_H
