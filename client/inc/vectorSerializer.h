#include<vector>
#include<string>


class VectorSerializer {
public:
    std::string serialize(std::vector<std::string> data);
    std::vector<std::string> deserialize(const std::string& data);
};
