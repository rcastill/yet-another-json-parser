#include "jsonarray.h"

JSONArray::JSONArray(Buffer &buffer, const IndexBuffer &ptokens, std::size_t offset) :
    buffer(buffer),
    tokens(ptokens),
    error("")
{
    if (tokens[offset].type != TOKEN_SQUARE_LEFT) {
        error = "Invalid JSONArray";
        return;
    }

    bool parsing_item  = true;

    for (std::size_t i = offset+1; i < tokens.size(); i++) {
        Index& index = tokens[i];

        if (index.type == TOKEN_COMMA) {
            if (parsing_item) {
                error = "Unexpected COMMA when parsing item.";
                return;

            } else if (i == 1) {
                error = "COMMA at beginning of array.";
                return;
            }

            parsing_item = true;
            continue;

        } else if (index.type == TOKEN_COLON) {
            error = "Unexpected COLON in array";
            return;

        } else if (index.type == TOKEN_SQUARE_RIGHT) {
            if (parsing_item && i != 1) {
                error = "SQUARE_RIGHT when parsing item.";
                return;
            }

            break;
        }

        if (parsing_item) {
            if (index.type == TOKEN_CURLY_LEFT) {
                item_data.add(i, 0, TYPE_OBJECT);

                if (!consume(tokens, TOKEN_CURLY_LEFT, TOKEN_CURLY_RIGHT, i)) {
                    error = "Unexpected ending when consuming object in array @EOF";
                    return;
                }

            } else if (index.type == TOKEN_SQUARE_LEFT) {
                item_data.add(i, 0, TYPE_ARRAY);

                if (!consume(tokens, TOKEN_SQUARE_LEFT, TOKEN_SQUARE_RIGHT, i)) {
                    error = "Unexpected ending when consuming array in array @EOF";
                    return;
                }

            } else if (index.type == TOKEN_DECIMAL) {
                item_data.add(i, 0, TYPE_DECIMAL);

            } else if (index.type == TOKEN_BOOLEAN) {
                item_data.add(i, 0, TYPE_BOOLEAN);

            } else if (index.type == TOKEN_STRING) {
                item_data.add(i, 0, TYPE_STRING);

            } else if (index.type == TOKEN_REAL) {
                item_data.add(i, 0, TYPE_REAL);

            } else if (index.type == TOKEN_NULL) {
                item_data.add(i, 0, TYPE_NULL);
            }

            parsing_item = false;
        }

    }

    items.resize(item_data.size());
}

bool JSONArray::is_array() const
{
    return true;
}

bool JSONArray::is_valid() const
{
    return error == "";
}

std::string JSONArray::get_error() const
{
    return error;
}

void JSONArray::parse(std::size_t i)
{
    if (items[i])
        return;

    items[i] = ::parse(buffer, tokens, item_data[i]);
}

std::size_t JSONArray::size() const
{
    return items.size();
}

JSONValue &JSONArray::operator[](std::size_t i)
{
    parse(i);
    return *items[i].get();
}

JSONValue &JSONArray::at(std::size_t i)
{
    parse(i);
    return *items[i].get();
}

std::shared_ptr<JSONValue> *JSONArray::begin()
{
    return &items.front();
}

std::shared_ptr<JSONValue> *JSONArray::end()
{
    return &items.back() + 1;
}

JSONArray& JSONArray::scast(JSONValue& jvalue)
{
    return static_cast<JSONArray&>(jvalue);
}

JSONArray& JSONArray::dcast(JSONValue& jvalue)
{
    return dynamic_cast<JSONArray&>(jvalue);
}



