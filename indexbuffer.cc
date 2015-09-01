#include "indexbuffer.h"

Index::Index(std::size_t position, std::size_t length, int type) :
    position(position), length(length), type(type)
{
}

IndexBuffer::IndexBuffer()
{

}

IndexBuffer::IndexBuffer(const IndexBuffer &other) :
    indexes(other.indexes)
{
}

void IndexBuffer::add(std::size_t position, std::size_t length, int type)
{
    indexes.push_back(Index(position, length, type));
}

Index& IndexBuffer::operator [](std::size_t i)
{
    return indexes[i];
}

Index& IndexBuffer::at(std::size_t i)
{
    return indexes[i];
}

std::size_t IndexBuffer::size() const
{
    return indexes.size();
}

Index* IndexBuffer::begin()
{
    return &indexes.front();
}

Index* IndexBuffer::end()
{
    return &indexes.back() + 1;
}

void IndexBuffer::debug()
{
    for (Index &index : indexes) {
        switch (index.type) {
        case TOKEN_CURLY_LEFT:
            std::cout << "CURLY_LEFT ";
            break;

        case TOKEN_CURLY_RIGHT:
            std::cout << "CURLY_RIGHT";
            break;

        case TOKEN_COMMA:
            std::cout << "COMMA ";
            break;

        case TOKEN_SQUARE_LEFT:
            std::cout << "SQUARE_LEFT ";
            break;

        case TOKEN_SQUARE_RIGHT:
            std::cout << "SQUARE_RIGHT ";
            break;

        case TOKEN_COLON:
            std::cout << "COLON ";
            break;

        case TOKEN_STRING:
            std::cout << "STRING ";
            break;

        case TOKEN_BOOLEAN:
            std::cout << "BOOLEAN ";
            break;
        }

        std::cout << "(" << index.type << ") "
                  << "@ "
                  << index.position
                  << " with length "
                  << index.length <<
                     std::endl;
    }
}
