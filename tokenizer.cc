#include "tokenizer.h"

bool check_known(std::string known, Buffer &buffer, std::size_t i)
{
    std::size_t len = known.size();
    if (i + len >= buffer.size()) {
        std::cout << "Unexpected ending" << std::endl;
        return false;
    }

    return std::string(&buffer[i]) == known;
}

Tokenizer::Tokenizer(Buffer &buffer) :
    buffer(buffer),
    error("")
{
}

bool Tokenizer::tokenize()
{
    auto number = [](char c) {
        return c >= 48 && c < 58;
    };

    auto separator = [](char c) {
        return c == ' ' || c == '\n' || c == '\t' || c == ',';
    };

    auto other = [](char c) {
        return c == ']' || c == '}';
    };

    for (std::size_t i = 0; i < buffer.size(); i++) {
        if (buffer[i] == '{') {
            index.add(i, 1, TOKEN_CURLY_LEFT);

        } else if (buffer[i] == '}') {
            index.add(i, 1, TOKEN_CURLY_RIGHT);

        } else if (buffer[i] == '[') {
            index.add(i, 1, TOKEN_SQUARE_LEFT);

        } else if (buffer[i] == ']') {
            index.add(i, 1, TOKEN_SQUARE_RIGHT);

        } else if (number(buffer[i]) || buffer[i] == '-') {
            bool floating = false;
            std::size_t j;

            for (j = i + 1; j < buffer.size(); j++) {
                if (buffer[j] == '.') {
                    if (floating) {
                        error = "Bad real syntaxis (2+ dots) @" + std::to_string(j);
                        return false;

                    } else {
                        floating = true;
                    }

                } else if (buffer[j] == '-') {
                    error = "Bad negative syntaxis (- after beginning)" + std::to_string(j);
                    return false;

                } else if (separator(buffer[j]) || other(buffer[j])) {
                    break;

                } else if (!number(buffer[j])) {
                    error = "Unexpected token when parsing number @" + std::to_string(j);
                    return false;
                }
            }

            if (j == buffer.size()) {
                error = "Unexpected ending when parsing number @EOF";
                return false;
            }

            index.add(i, j - i, floating ? TOKEN_REAL : TOKEN_DECIMAL);
            i = j - 1; // separator.pos - 1 => next iteration i = separator.pos

        } else if (buffer[i] == 't') {
            if (buffer.size() - i < 4) {
                error = "Unexpected ending when parsing boolean @EOF";
                return false;

            } if (std::string(&buffer[i], 4) != "true") {
                error = "Unexpected token when parsing boolean @" + std::to_string(i);
                return false;
            }

            index.add(i, 4, TOKEN_BOOLEAN);
            i += 3;

        } else if (buffer[i] == 'f') {
            if (buffer.size() - i < 5) {
                error = "Unexpected ending when parsing boolean @EOF";
                return false;

            } if (std::string(&buffer[i], 5) != "false") {
                error = "Unexpected token when parsing boolean @" + std::to_string(i);
                return false;
            }

            index.add(i, 5, TOKEN_BOOLEAN);
            i += 4;

        } else if (buffer[i] == 'n') {
            if (buffer.size() - i < 4) {
                error = "Unexpected ending when parsing null @EOF";
                return false;

            } if (std::string(&buffer[i], 4) != "null") {
                error = "Unexpected token when parsing null @" + std::to_string(i);
                return false;
            }

            index.add(i, 4, TOKEN_NULL);
            i += 3;

        } else if (buffer[i] == '"') {
            bool escape = false;
            std::size_t j;

            for (j = i+1; j < buffer.size(); j++) {
                if (buffer[j] == '\\')
                    escape = !escape;
                else if (buffer[j] == '"' && !escape)
                    break;
            }

            if (j == buffer.size()) {
                error = "Unexpected ending when parsing string @EOF";
                return false;
            }

            index.add(i, j - i + 1, TOKEN_STRING);
            i = j;

        } else if (buffer[i] == ':') {
            index.add(i, 1, TOKEN_COLON);

        } else if (buffer[i] == ',') {
            index.add(i, 1, TOKEN_COMMA);

        } else if (!separator(buffer[i])) {
            error = "Unexpected token @" + std::to_string(i);
            return false;
        }
    }

    return true;
}

std::string Tokenizer::get_error() const
{
    return error;
}

IndexBuffer Tokenizer::get_ibuffer() const
{
    return index;
}

