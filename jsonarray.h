#ifndef JSONARRAY_H
#define JSONARRAY_H

#include "buffer.h"
#include "tokenizer.h"
#include "jsonvalue.h"
#include "parser_util.h"
#include "jsonobject.h"

#include <vector>
#include <string>

typedef std::vector<std::shared_ptr<JSONValue>> ValVector;

class JSONArray : public JSONValue
{
private:
    Buffer&     buffer;
    IndexBuffer tokens;
    IndexBuffer item_data;
    ValVector   items;

    std::string error;

public:
    JSONArray(Buffer& buffer, const IndexBuffer& tokens, std::size_t offset = 0);

    bool is_array() const;
    bool is_valid() const;

    std::string get_error() const;

    void parse(std::size_t i);

    std::size_t size() const;
    JSONValue&  operator[](std::size_t i);
    JSONValue&  at(std::size_t i);

    std::shared_ptr<JSONValue>* begin();
    std::shared_ptr<JSONValue>* end();

    static JSONArray& scast(JSONValue& jvalue);
    static JSONArray& dcast(JSONValue& jvalue);
};

#endif // JSONARRAY_H
