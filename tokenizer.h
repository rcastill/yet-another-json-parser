#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "buffer.h"
#include "indexbuffer.h"
#include "types.h"

class Tokenizer
{
private:
    Buffer&     buffer;
    IndexBuffer index;

    std::string error;

public:
    Tokenizer(Buffer& buffer);

    bool tokenize();

    std::string get_error() const;

    IndexBuffer get_ibuffer() const;
};

#endif // TOKENIZER_H
