#include <string>
#include <fstream>

#include "iniconfig.hpp"

std::string readAllString(std::string filename){
    std::ifstream ifs(filename);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    return content;
}

std::vector<std::string> split_string(const std::string& str,
                                      const std::string& delimiter){
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;
}

int IniConfig::get(const std::string key, std::string &outValue){

    for(auto kvp : keyValueMap){
        if(kvp.key == key){
            outValue = kvp.value;
            return 0;
        }
    }

    return 1;
}

int IniConfig::load(){

    std::string rawContents = readAllString("config.txt");
    auto rv = parse(rawContents);

    if(rv != 0){
        return rv;
    }

    return 0;
}

int IniConfig::parse(const std::string raw){

    auto items = split_string(raw, "\n");

    for(auto item : items){
        IniConfig::KeyValuePair kvp;
        auto splittedItem = split_string(item, "=");
        kvp.key = splittedItem.at(0);
        kvp.value = splittedItem.at(1);

        keyValueMap.push_back(kvp);
    }

    return 0;
}