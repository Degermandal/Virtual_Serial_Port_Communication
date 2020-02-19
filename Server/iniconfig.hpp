#ifndef __INICONFIG_H__
#define __INICONFIG_H__

#include <vector>

class IniConfig{

    public:
        struct KeyValuePair{
            std::string key;
            std::string value;
        };

    public:
        int load();
        int get(const std::string key, std::string &outValue);

    private: /* member fields */
        std::vector<KeyValuePair> keyValueMap;

    private: /* member functions */
        int parse(const std::string raw);

}; /* class IniConfig */

#endif /* __INICONFIG_H__ */