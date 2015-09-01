#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <unordered_map>

#include "tokenizer.h"
#include "indexbuffer.h"
#include "types.h"
#include "jsonvalue.h"
#include "parser_util.h"

#include <sstream>
#include <iostream>

typedef std::unordered_map<std::string, std::shared_ptr<JSONValue>> CacheMap;
typedef std::vector<std::string>                                    StrVector;
typedef std::int64_t                                                decimal;
typedef std::double_t                                               real;

class JSONObject : public JSONValue
{
private:
    Buffer&     buffer;
    IndexBuffer token_ibuffer;
    IndexBuffer key_data;
    StrVector   keys;
    CacheMap    cache;
    std::string error;

    bool cache_has(std::string key) const;

public:
    JSONObject(Buffer& buffer, const IndexBuffer& tokens, std::size_t offset = 0);
    ~JSONObject();

    bool is_object() const;

    bool        is_valid()  const;
    std::string get_error() const;

    bool        has(std::string key);
    JSONValue&  operator[](std::string key);
    JSONValue&  get(std::string key);
    void        parse(std::string key);

    static JSONObject& scast(JSONValue& jvalue);
    static JSONObject& dcast(JSONValue& jvalue);
};

#endif // JSONOBJECT_H
