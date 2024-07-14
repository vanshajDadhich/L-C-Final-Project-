#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>
#include <sstream>

struct Serializable {
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string& data) = 0;
};


#endif
