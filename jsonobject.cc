#include "jsonobject.h"

bool JSONObject::cache_has(std::string key) const
{
    return cache.find(key) != cache.end();
}

JSONObject::JSONObject(Buffer& buffer, const IndexBuffer& tokens, std::size_t offset) :
    buffer(buffer),
    token_ibuffer(tokens),
    error("")
{
    if (token_ibuffer[offset].type != TOKEN_CURLY_LEFT) {
        error = "Invalid object";
        return;
    }

    bool parsing_key = true;

    for (std::size_t i = offset+1; i < token_ibuffer.size(); i++) {
        Index& index = token_ibuffer[i];

        if (index.type == TOKEN_COLON) {
            if (!parsing_key) {
                error = "Unexpected COLON when not parsing key.";
                return;

            } else if (i == 1) {
                error = "COLON at beginning of object.";
                return;
            }

            parsing_key = false;
            continue;

        } else if (index.type == TOKEN_COMMA) {
            if (parsing_key) {
                error = "Unexpected COMMA when parsing key.";
                return;

            } else if (i == 1) {
                error = "COMMA at beginning of object.";
                return;
            }

            parsing_key = true;
            continue;

        } else if (index.type == TOKEN_CURLY_RIGHT) {
            if (parsing_key && i != 1) {
                error = "CURLY_RIGHT when parsing key.";
                return;
            }

            break;
        }

        if (parsing_key) {
            if (index.type != TOKEN_STRING) {
                error = "JSON keys can only be strings. @"+std::to_string(index.position);
                return;
            }

            std::string key(&buffer[index.position+1], index.length-2);
            keys.push_back(key);

        } else {
            if (index.type == TOKEN_SQUARE_LEFT) {
                key_data.add(i, 0, TYPE_ARRAY);

                if (!consume(token_ibuffer, TOKEN_SQUARE_LEFT, TOKEN_SQUARE_RIGHT, i)) {
                    error = "Incomplete array @EOF";
                    return;
                }

            } else if (index.type == TOKEN_CURLY_LEFT) {
                key_data.add(i, 0, TYPE_OBJECT);

                if (!consume(token_ibuffer, TOKEN_CURLY_LEFT, TOKEN_CURLY_RIGHT, i)) {
                    error = "Incomplete object @EOF";
                    return;
                }

            } else if (index.type == TOKEN_STRING) {
                key_data.add(i, 0, TYPE_STRING);

            } else if (index.type == TOKEN_DECIMAL) {
                key_data.add(i, 0, TYPE_DECIMAL);

            } else if (index.type == TOKEN_REAL) {
                key_data.add(i, 0, TYPE_REAL);

            } else if (index.type == TOKEN_BOOLEAN) {
                key_data.add(i, 0, TYPE_BOOLEAN);

            } else if (index.type == TOKEN_NULL) {
                key_data.add(i, 0, TYPE_NULL);
            }
        }
    }

    if (keys.size() != key_data.size())
        error = "Object is not a pair set.";
}

JSONObject::~JSONObject()
{
}

bool JSONObject::is_object() const
{
    return true;
}

bool JSONObject::is_valid() const
{
    return error == "";
}

std::string JSONObject::get_error() const
{
    return error;
}

bool JSONObject::has(std::string key)
{
    if (cache_has(key))
        return true;

    for (auto& k : keys)
        if (k == key) return true;

    return false;
}

JSONValue &JSONObject::operator[](std::string key)
{
    parse(key);
    return *cache[key].get();
}

void JSONObject::parse(std::string key)
{
    if (cache_has(key))
        return;

    std::size_t i;
    for (i = 0; i < keys.size(); i++) {
        if (keys[i] == key) {
            cache[key] = ::parse(buffer, token_ibuffer, key_data[i]);
            break;
        }
    }
}

JSONObject &JSONObject::scast(JSONValue &jvalue)
{
    return static_cast<JSONObject&>(jvalue);
}

JSONObject &JSONObject::dcast(JSONValue &jvalue)
{
    return dynamic_cast<JSONObject&>(jvalue);
}

