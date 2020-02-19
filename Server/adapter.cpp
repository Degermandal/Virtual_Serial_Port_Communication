#include "adapter.h"
#include "iniconfig.hpp"

Adapter::Adapter()
{

}

Adapter::Adapter(std::string received)
{
    setTag(received);
    setLength(received);
    setVal(received);
}

void Adapter::setLength(std::string received){ 
    std::string len = "";
    len += received[2];
    len += received[3];

    length = len;
}

void Adapter::setVal(std::string received){
    std::string str = "";
    for(int i=4; i<received.length(); i++)
    {
        str += received[i];
    }

    value = str;
}

std::string Adapter::setData(std::vector< uint8_t > TLVData)
{
    std::string data = "";
    for(int i = 4; i<TLVData.size()-1; i++)
    {
        data += TLVData[i];
    }

    return data;
}

void Adapter::read_P_R_U()
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

/* std::string Adapter::methodDecider(char tag)
{
    if(tag < '\x11')
        return "GET";
    else if (tag < '\x27')
         return "POST";
    else {
        return "PATCH";
    }
}
 */
std::string Adapter::endpointDecider(char tag)
{
    printf("--%s--\n", __FUNCTION__);
    switch(tag){
        case '\x30':  /* POST - LOGIN */ 
            return "/api/login";
        case '\x00':  /* POST - LOGOUT */ //???
            return "/api/logout";
        case '\x01':  /* GET - INFO */ //???
            return "/api/info";
        case '\x42':  /* POST - STARTSALE */  
            return "/api/startssale";
        case '\x60':  /* POST - SETVAT */ 
            return "/api/vat";
        case '\x61':  /* GET - GETVATLIST */
            return "/api/vat";
        default:
            return nullptr;
    }
}

char Adapter::decideTheTag(std::string method, std::string endPoint)
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



/* char Adapter::tagDecider(std::string method, std::string endpoint)
{
    if(method=="GET")
    {
        if(endpoint=="/api/info")
            return '\x01';
    }
} */

std::string Adapter::serialize(web::http::http_request msg, std::string method)
{
    std::string message;
    Adapter adapter;
    message=message + '\x02';
    message=message + adapter.decideTheTag(method,msg.request_uri().path());
    message=message + (char) msg.extract_utf8string().get().length();
    message = message + msg.extract_utf8string().get();
    message = message + '\x03';
    return message;
}

/* std::string Adapter::getVal(std::string msg)
{
    std::string val;
    for(int i=3;i<msg.length();i++)
           val=val+msg[i];
    return val;

}

char Adapter::getTag(std::string msg)
{
    return msg[1];
}

char Adapter::getLength(std::string msg)
{
    return msg[2];
}
 */


