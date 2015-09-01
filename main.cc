#include <iostream>
#include "buffer.h"
#include "tokenizer.h"
#include "parser.h"
#include "jsonobject.h"

int main()
{
    Buffer buffer = Buffer::from_file("res/test.json");

    if (buffer) {
        Tokenizer tokenizer(buffer);

        if (!tokenizer.tokenize()) {
            std::cout << tokenizer.get_error() << std::endl;
            return 1;
        }

        //tokenizer.get_ibuffer().debug();

        JSONArray root(buffer, tokenizer.get_ibuffer());

        if (!root.is_valid()) {
            std::cout << root.get_error() << std::endl;
            return 1;
        }

        for (std::size_t i = 0; i < root.size(); i++) {
            JSONObject& person  = JSONObject::scast(root[i]);
            std::string name    = person["name"].get_string();
            std::string gender  = person["gender"].get_string();
            decimal age         = person["age"].get_decimal();
            std::string address = person["address"].get_string();
            real latitude       = person["latitude"].get_real();
            real longitude      = person["longitude"].get_real();
            JSONArray& friends  = JSONArray::scast(person["friends"]);

            std::cout << name << " is " << age << " years old, lives in "
                      << address << " (" << latitude << ", " << longitude
                      << ") and ";

            if (gender == "male")
                std::cout << "his ";
            else
                std::cout << "her ";

            std::cout << "friends are: ";

            for (std::size_t j = 0; j < friends.size(); j++) {
                std::cout << JSONObject::scast(friends[j])["name"].get_string();
                if (j != friends.size() - 1)
                    std::cout << ", ";
            }

            std::cout << std::endl;
        }


    } else {
        std::cout << "Could not load file\n";
    }

    return 0;
}

