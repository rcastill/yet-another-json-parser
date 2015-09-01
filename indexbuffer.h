#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <cstdlib>
#include <vector>

#include <iostream>
#include "types.h"

struct Index {
    std::size_t position;
    std::size_t length;
    int         type;

    Index(std::size_t position, std::size_t length, int type);
};

class IndexBuffer
{
private:
    std::vector<Index> indexes;

public:
    IndexBuffer();
    IndexBuffer(const IndexBuffer& other);

    std::size_t size() const;
    void        add(std::size_t position, std::size_t length, int type);
    Index&      operator[](std::size_t i);
    Index&      at(std::size_t i);

    Index* begin();
    Index* end();

    void debug();
};

#endif // INDEXBUFFER_H
