#include "TagDecider.h"
#include "iniconfig.hpp"

TagDecider::TagDecider()
{

}

std::string TagDecider::setData(std::vector< uint8_t > TLVData)
{
    data = "";
    for(int i = 4; i<TLVData.size()-1; i++)
    {
        data += TLVData[i];
    }

    return data;
}
std::string TagDecider::getData() {return data;}

uint8_t TagDecider::decideTheTag(std::string method, std::string endPoint)
{
    if(method == "POST")
    {
        if(endPoint == "/api/login") /*LOGIN */
        {
            return '\x30';
        }
            
        if(endPoint == "/api/logout") //?????????????????????
            return '\x00';
        if(endPoint == "/api/startssale") /* START SALE */
            return '\x42';
        if(endPoint == "/api/vat") /* SET VAT */
            return '\x60';

    }

    if(method == "GET")
    {
        if(endPoint == "/api/info") //???
            return '\x00';
        if(endPoint == "/api/vat") /* GET VAT LIST */
            return '\x61';
    }
}

void TagDecider::read_P_R_U()
{

    std::string port = ""; /* "/dev/pts/18";//new char[15]; */
    std::string rate = ""; /* "115200";//new char[15]; */
    std::string url = ""; /* "http://172.20.2.22:6502";//new char[30]; */

    IniConfig config;
    auto rv = config.load();
    if(rv != 0)
    {
        std::cerr << "loading config failed with rv:" << rv << ", using defaults" << std::endl;
    }
    else
    {
        rv = config.get("port", port);
        rv = config.get("rate", rate);
        rv = config.get("url", url);
    }

    setPort(port);
    setRate(rate);
    setUrl(url);   
}