#ifndef BUFFER_H
#define BUFFER_H

#include <memory>
#include <fstream>
#include <string>
#include <cstring>

#include <iostream>

class Buffer;
typedef std::shared_ptr<Buffer> Buffer_;

class Buffer
{
private:
    char *buffer;
    std::size_t buffsize;

    static std::size_t get_fsize(std::ifstream& ifs);

public:
    Buffer(char *buffer, std::size_t buffsize);
    Buffer(const Buffer &buffer);
    Buffer(Buffer &&buffer);
    ~Buffer();

    static Buffer_ from_string(std::string string);
    static Buffer from_file(std::string filename);

    char &operator[] (std::size_t i);
    char &at(std::size_t i);
    std::size_t size() const;

    char *begin();
    char *end();

    operator bool() const;
};

#endif // BUFFER_H
