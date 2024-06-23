#ifndef VECTORSERIALIZER_H
#define VECTORSERIALIZER_H

#include<vector>
#include<string>


class VectorSerializer {
public:
    std::string static serialize(std::vector<std::string> data);
    std::vector<std::string> static deserialize(const std::string& data);
};

#endif
