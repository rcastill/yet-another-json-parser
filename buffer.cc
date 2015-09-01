#include "buffer.h"

Buffer::Buffer(char *buffer, std::size_t size) :
    buffer(buffer), buffsize(size)
{
}

Buffer::Buffer(const Buffer &buffer) :
    buffer(new char[buffer.buffsize]),
    buffsize(buffer.buffsize)
{
    std::copy(buffer.buffer, buffer.buffer + buffsize, this->buffer);
}

Buffer::Buffer(Buffer &&buffer) :
    buffer(buffer.buffer), buffsize(buffer.size())
{
    buffer.buffer = NULL;
}

Buffer::~Buffer()
{
    if (buffer != NULL)
        delete[] buffer;
}

std::size_t Buffer::get_fsize(std::ifstream &ifs)
{
    ifs.seekg(0, ifs.end);
    std::size_t size = ifs.tellg();
    ifs.seekg(0, ifs.beg);
    return size;
}

Buffer_ Buffer::from_string(std::string string)
{
    std::size_t size = string.length();

    char *buffer = new char[size];
    std::memcpy(buffer, string.c_str(), size);

    return std::make_shared<Buffer>(buffer, size);
}

Buffer Buffer::from_file(std::string filename)
{
    std::ifstream ifs(filename);

    if (!ifs.is_open())
        return Buffer(NULL, 0);

    std::size_t fsize = get_fsize(ifs);

    char *buffer = new char[fsize];
    ifs.read(buffer, fsize);
    ifs.close();

    return Buffer(buffer, fsize);
}

char &Buffer::operator[] (std::size_t i)
{
    return buffer[i % buffsize];
}

char &Buffer::at(std::size_t i)
{
    return buffer[i % buffsize];
}

std::size_t Buffer::size() const
{
    return buffsize;
}

char *Buffer::begin()
{
    return &buffer[0];
}

char *Buffer::end()
{
    return &buffer[buffsize];
}

Buffer::operator bool() const
{
    return buffer != NULL;
}
