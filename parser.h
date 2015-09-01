#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"
#include "indexbuffer.h"
#include "jsonobject.h"
#include "types.h"

class Parser
{
private:
    IndexBuffer token_ibuffer;

    JSONObject* root_object;


public:
    Parser(const Tokenizer &tokenizer);

    void parse();
};

#endif // PARSER_H
