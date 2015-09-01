#include "parser_util.h"

bool consume(IndexBuffer& tokens, JSONToken inct, JSONToken dect, std::size_t& i)
{
    std::size_t count = 0;
    std::size_t j;

    for (j = i; j < tokens.size(); j++) {
        if (tokens[j].type == inct) {
            count++;

        } else if (tokens[j].type == dect) {
            count--;

            if (count == 0)
                break;
        }
    }

    if (j == tokens.size())
        return false;

    i = j;
    return true;

}

std::shared_ptr<JSONValue> parse(Buffer& buffer, IndexBuffer& tokens, Index& data_index)
{
    Index& index = tokens[data_index.position];

    if (data_index.type == TYPE_OBJECT) {
        return std::make_shared<JSONObject>(buffer, tokens, data_index.position);

    } else if (data_index.type == TYPE_ARRAY) {
        return std::make_shared<JSONArray>(buffer, tokens, data_index.position);

    } else if (data_index.type == TYPE_STRING) {
        std::string s(&buffer[index.position+1], index.length-2);
        return std::make_shared<JSONValue>(s);

    } else if (data_index.type == TYPE_DECIMAL || data_index.type == TYPE_REAL) {
        std::string s(&buffer[index.position], index.length);
        std::stringstream ss(s);

        if (data_index.type == TYPE_DECIMAL) {
            decimal d; ss >> d;
            return std::make_shared<JSONValue>(d);

        } else {
            real r; ss >> r;
            return std::make_shared<JSONValue>(r);
        }

    } else if (data_index.type == TYPE_BOOLEAN) {
        return std::make_shared<JSONValue>(buffer[index.position] == 't');

    } else if (data_index.type == TYPE_NULL) {
        return std::make_shared<JSONValue>(NULL);

    } else {
        return nullptr;
    }
}

