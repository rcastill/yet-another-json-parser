#ifndef PARSER_UTIL
#define PARSER_UTIL

#include <cstdint>
#include <memory>

#include "types.h"
#include "indexbuffer.h"
#include "jsonvalue.h"
#include "buffer.h"
#include "jsonobject.h"
#include "jsonarray.h"

bool consume(IndexBuffer& tokens, JSONToken inct, JSONToken dect, std::size_t& i);
std::shared_ptr<JSONValue> parse(Buffer& buffer, IndexBuffer& tokens, Index& data_index);

#endif // PARSER_UTIL

